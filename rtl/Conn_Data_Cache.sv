module Conn_Data_Cache (
    input logic cache_clk,
    input logic rstn_h,
    input logic dcache_en,
    input logic dcache_rw,
    input logic [1:0] data_mode,
    input logic [31:0] request_address,
    input logic [31:0] write_data,
    input logic [31:0] mem_response_data,
    input logic mem_busy,

    output logic [31:0] response_data,
    output logic wEn,
    output logic rEn,
    output logic isBurst,
    output logic [31:0] mem_address,
    output logic [31:0] mem_write_data
);

    // Internal connection wires
    logic write_enable, read_enable, mem_ready;
    logic mem_request, mem_write_enable;

    // Instantiate Data Cache Manager
    Data_Cache_Manager #(.WordSize(32)) manager (
        .dcache_en(dcache_en),
        .dcache_rw(dcache_rw),
        .mem_request(mem_request),
        .mem_write_enable(mem_write_enable),
        .mem_busy(mem_busy),
        .write_enable(write_enable),
        .read_enable(read_enable),
        .mem_ready(mem_ready),
        .wEn(wEn),
        .rEn(rEn),
        .isBurst(isBurst)
    );

    // Instantiate L1 Data Cache
    L1_Data_Cache cache (
        .clk(cache_clk),
        .rstn(rstn_h),
        .write_enable(write_enable),
        .read_enable(read_enable),
        .request_address(request_address),
        .write_data(write_data),
        .data_mode(data_mode),
        .response_data(response_data),
        .mem_request(mem_request),
        .mem_write_enable(mem_write_enable),
        .mem_address(mem_address),
        .mem_write_data(mem_write_data),
        .mem_response_data(mem_response_data),
        .mem_ready(mem_ready),
        .c_state() // optional for debug
    );

endmodule
