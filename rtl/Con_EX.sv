module Con_EX #(
    WordSize = 32
) (
    input clk,
    input rstn,
    input branch_taken_in,
    input [1:0] a_sel,
    input [1:0] b_sel,
    input [WordSize - 1:0] imm,
    input [WordSize - 1:0] pc_in,
    input [WordSize - 1:0] rs1d,
    input [WordSize - 1:0] rs2d_in,
    input [WordSize - 1:0] branch_addr_in,
    input [4:0] rdn_in,
    input [5:0] alu_mode,
    output logic branch_taken,
    output logic [4:0] rdn,
    output logic [WordSize - 1:0] pc,
    output logic [WordSize - 1:0] branch_addr,
    output logic [WordSize - 1:0] rs2d,
    output logic [WordSize - 1:0] alu_out
);

  logic [WordSize - 1:0] a, b;

  IDEX #(WordSize) id_ex_latch (
      .clk(clk),
      .rstn(rstn),
      .branch_taken_in(branch_taken_in),
      .a_sel(a_sel),
      .b_sel(b_sel),
      .imm(imm),
      .pc_in(pc_in),
      .rs1d(rs1d),
      .rs2d_in(rs2d_in),
      .branch_addr_in(branch_addr_in),
      .rdn_in(rdn_in),
      .branch_taken(branch_taken),
      .rdn(rdn),
      .pc(pc),
      .branch_addr(branch_addr),
      .rs2d(rs2d),
      .a(a),
      .b(b)
  );

  Alu #(WordSize) alu_modulemake (
      .a(a),
      .b(b),
      .alu_mode(alu_mode),
      .alu_out(alu_out)
  );

endmodule
