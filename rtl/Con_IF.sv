module Con_IF (
    input logic clk,
    input logic cache_clk,
    input logic rstn,
    input logic rstn_h,
    input logic pc_en,
    input logic [31:0] npc,

    // Memory 
    input logic [31:0] mem_response_data, 
    input logic mem_busy,                 

    output logic [31:0] pc,
    output logic [31:0] ins
);

    logic [31:0] mem_address;
    logic rEn;
    logic isBurst;

    PC pc_module (
        .clk(clk),
        .rstn(rstn),
        .pc_en(pc_en),
        .npc(npc),
        .pc(pc)
    );

    Instruction_Cache icache (
        .cache_clk(cache_clk),
        .rstn_h(rstn_h),
        .mem_response_data(mem_response_data),
        .mem_busy(mem_busy),
        .pc(pc),           
        .ins(ins),          
        .rEn(rEn),         
        .isBurst(isBurst), 
        .mem_address(mem_address) 
    );

endmodule
