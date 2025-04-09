module Con_MEM (
    input logic clk,
    input logic rstn,
    input logic rstn_h,
    input logic cache_clk,

    // From EX stage
    input logic [4:0] rdn_in,
    input logic [31:0] alu_out_in,
    input logic [31:0] rs2d,

    // Cache control signals
    input logic dcache_en,
    input logic dcache_rw,
    input logic [1:0] data_mode,
    input logic [31:0] mem_response_data,
    input logic mem_busy,

    // Outputs 
    output logic [4:0] rdn,
    output logic [31:0] alu_out,
    output logic [31:0] response_data,
    output logic wEn,
    output logic rEn,
    output logic isBurst,
    output logic [31:0] mem_address,
    output logic [31:0] mem_write_data
);

  // Intermediate wire between EXMEM and Data Cache
  logic [31:0] mem_data;

  // === Instantiate EX/MEM Latch === //
  EXMEM exmem_inst (
    .clk(clk),
    .rstn(rstn),
    .rdn_in(rdn_in),
    .alu_out_in(alu_out_in),
    .rs2d(rs2d),
    .rdn(rdn),
    .alu_out(alu_out),
    .mem_data(mem_data)
  );

  // === Instantiate Data Cache === //
  Conn_Data_Cache data_cache_inst (
    .cache_clk(cache_clk),
    .rstn_h(rstn_h),
    .dcache_en(dcache_en),
    .dcache_rw(dcache_rw),
    .data_mode(data_mode),
    .request_address(alu_out),
    .write_data(mem_data),
    .mem_response_data(mem_response_data),
    .mem_busy(mem_busy),

    .response_data(response_data),
    .wEn(wEn),
    .rEn(rEn),
    .isBurst(isBurst),
    .mem_address(mem_address),
    .mem_write_data(mem_write_data)
  );

endmodule
