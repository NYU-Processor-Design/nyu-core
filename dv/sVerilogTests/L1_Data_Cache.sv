`timescale 1ns / 1ps

module tb_L1_Data_Cache;
    parameter CLOCK_PERIOD   = 10;    
    reg clk;
    reg reset;
    reg write_enable;
    reg read_enable;
    reg [31:0] request_address;
    reg [31:0] write_data;
    wire [31:0] response_data;
    wire [1:0] c_state;

    // RAM
    reg [31:0] mem_response_data;
    reg mem_ready;
    reg mem_request;
    reg mem_write_enable;
    wire [31:0] mem_address;
    wire [31:0] mem_write_data;
    
    // Hardcoded parameters for the RAM
    localparam MEM_SIZE    = 16 * 1024;   // RAM size: 4 KB
    localparam MEM_UNIT_SIZE   = 32;
                  

    L1_Data_Cache dut (
        .clk(clk),
        .reset(reset),
        .write_enable(write_enable),
        .read_enable(read_enable),
        .request_address(request_address),
        .write_data(write_data),
        .response_data(response_data),
        .c_state(c_state),
        
        .mem_response_data(mem_response_data),
        .mem_ready(mem_ready),
        .mem_request(mem_request),
        .mem_write_enable(mem_write_enable),
        .mem_address(mem_address),
        .mem_write_data(mem_write_data)      
    );
    
    initial begin

       mem_data [512] <= 32'hAAAAAAAA;
        
       mem_data [524] <= 32'hEEEEEEEE;
       
       mem_data [1023] <= 32'h11111111;
       
    end

    initial begin
        clk = 0;
        forever #(CLOCK_PERIOD/2) clk = ~clk;
    end

    initial begin
        reset_signals();
        edge_cases_testing();
        sequential_consecutive_testing();
        $finish;
    end
    
    task edge_cases_testing();
        begin
            // =================     L1 SET 0 test, MEM addr 512      ================= 
            test_cache_read_miss(32'h00000802, 32'hAAAAAAAA);
            test_cache_read_miss(32'hABCDE802, 32'hBBBBBBBB);
            test_cache_read_miss(32'hAAAAA802, 32'hCCCCCCCC); 
            test_cache_read_miss(32'hFFFFF802, 32'hDDDDDDDD);  
            
            test_cache_read_hit (32'hAAAAA802, 32'hCCCCCCCC);
            test_cache_read_hit (32'hFFFFF802, 32'hDDDDDDDD);  
            
            test_cache_read_miss(32'h00000802, 32'hAAAAAAAA);
            test_cache_read_miss(32'hABCDE802, 32'hBBBBBBBB);
                   
            test_cache_read_hit (32'h00000802, 32'hAAAAAAAA);
            test_cache_read_hit (32'hABCDE802, 32'hBBBBBBBB);
            
            // =================    L1 SET 511 test, MEM addr 1023    =================
            test_cache_read_miss(32'h00000FFF, 32'h11111111);
            test_cache_read_miss(32'hABCDEFFF, 32'h22222222);
            test_cache_read_miss(32'hAAAAAFFF, 32'h33333333); 
            test_cache_read_miss(32'hFFFFFFFF, 32'h44444444);  
            
            test_cache_read_hit (32'hAAAAAFFF, 32'h33333333);
            test_cache_read_hit (32'hFFFFFFFF, 32'h44444444);  
            
            test_cache_read_miss(32'h00000FFF, 32'h11111111);
            test_cache_read_miss(32'hABCDEFFF, 32'h22222222);
                   
            test_cache_read_hit (32'h00000FFF, 32'h11111111);
            test_cache_read_hit (32'hABCDEFFF, 32'h22222222);
        end
    endtask
    
    task sequential_consecutive_testing;
        begin
        // =================    SEQUENTIAL TESTING      ================= 
        read_enable =1;  
        request_address = 32'h00000832;
        #51 read_enable = 0; #9;  // fill and read 
        // lru counter 0: 1 && lru counter 1: 0 - 32'h00000832
        
        #10 read_enable = 1;  
        request_address = 32'hABCDE832;
        #51 read_enable = 0; #9;
        // lru counter 0: 0 - 32'hABCDE832 && lru counter 1: 1 - 32'h00000832

        test_cache_read_hit (32'h00000832, 32'hEEEEEEEE); 
        // lru counter 0: 1 - 32'hABCDE832 && lru counter 1: 0 - 32'h00000832

        test_cache_read_hit (32'hABCDE832, 32'hFFFFFFFF);
        // lru counter 0: 0 - 32'hABCDE832 && lru counter 1: 1 - 32'h00000832

        test_cache_read_miss(32'hAAAAA832, 32'hABCDEFAB); 
        // lru counter 0: 1 - 32'hABCDE832 && lru counter 1: 0 - 32'hAAAAA832

        test_cache_read_hit (32'hABCDE832, 32'hFFFFFFFF);
        // lru counter 0: 0 - 32'hABCDE832 && lru counter 1: 1 - 32'hAAAAA832

        test_cache_read_miss(32'h00000832, 32'hEEEEEEEE); 
        // lru counter 0: 1 - 32'hABCDE832 && lru counter 1: 0 - 32'h00000832

        test_cache_write_hit(32'hABCDE832, 32'hBEEF_DEAD);
        // dirty 1 for 32'hABCDE832 with beef_dead
        // lru counter 0: 0 - 32'hABCDE832 && lru counter 1: 1 - 32'h00000832

        test_cache_read_miss(32'hAAAAA832, 32'hABCDEFAB);
        // lru counter 0: 1 - 32'hABCDE832 && lru counter 1: 0 - 32'hAAAAA832

        test_cache_read_writeback_miss(32'hFFFFF832, 32'hFEDCBAFE);
        // lru counter 0: 0 - 32'hFFFFF832 && lru counter 1: 1 - 32'hAAAAA832
        
        test_cache_read_hit(32'hAAAAA832, 32'hABCDEFAB);
        test_cache_read_hit(32'hFFFFF832, 32'hFEDCBAFE);
        test_cache_read_miss(32'h00000832, 32'hEEEEEEEE);
        test_cache_read_miss(32'hABCDE832, 32'hFFFFFFFF);
        end
    endtask
    
    task reset_signals;
        begin
            reset = 1;
            write_enable = 0;
            read_enable = 0;
            mem_ready = 1;
            mem_request = 0;
            mem_write_enable = 0;
            write_data = 0;
            mem_response_data = 0;
            
            #15 reset = 0; 
        end
    endtask

    task test_cache_read_hit(input [MEM_UNIT_SIZE-1:0] addr, input [31:0] expected_data);
        begin
            #10 read_enable = 1;
            request_address = addr;

            #21 read_enable = 0;
            assert(response_data == expected_data) else $display("Read Hit Test Failed for address %h", addr);
            #9;
        end
    endtask
    
    task test_cache_read_writeback_miss(input[MEM_UNIT_SIZE-1:0] addr, input [31:0] expected_data);
        begin
            #10 read_enable = 1;
            request_address = addr;
            
            #81 read_enable = 0;
            assert(response_data == expected_data) else $display("Read Miss Test Failed for address %h", addr);
            #9;
        end
    endtask

    task test_cache_write_hit(input [MEM_UNIT_SIZE-1:0] addr, input [31:0] data);
        begin
            #10 write_enable = 1;
            request_address = addr;
            write_data = data;         
            #31 write_enable = 0; #9;         
        end
    endtask

    task test_cache_read_miss(input [MEM_UNIT_SIZE-1:0] addr, input [31:0] expected_data);
        begin
            #10 read_enable = 1;
            request_address = addr;
            #51; 
            read_enable = 0;
            assert(response_data == expected_data) else $display("Read Miss Test Failed for address %h", addr);
            #9;
        end
    endtask

    task test_cache_write_miss(input [MEM_UNIT_SIZE-1:0] addr, input [31:0] data);
        begin
            write_enable = 1;
            request_address = addr;
            write_data = data;
            #41; 
            write_enable = 0;
        end
    endtask
       
    // RAM Simulation Logic
    always @(posedge clk) begin
        if (mem_ready) begin
            if (mem_request) begin
                if (mem_write_enable) mem_data[mem_address] = mem_write_data;
                else mem_response_data = mem_data[mem_address];
            end 
            end
    end
        
endmodule


