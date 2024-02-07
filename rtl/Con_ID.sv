module Con_ID #(
    WordSize = 32
) (
    input clk,
    input cache_clk,
    input rstn,
    input wbe,
    input addr_mode,
    input branch_taken,
    input [2:0] immode,
    input [4:0] rdn_in,
    input [WordSize - 1:0] ins,
    input [WordSize - 1:0] pc_in,
    input [WordSize - 1:0] rdd,
    output logic [4:0] rdn,
    output logic [WordSize - 1:0] imm,
    output logic [WordSize - 1:0] pc,
    output logic [WordSize - 1:0] rs1d,
    output logic [WordSize - 1:0] rs2d,
    output logic [WordSize - 1:0] npc,
    output logic [WordSize - 1:0] branch_addr
);

  logic [4:0] rs1n, rs2n;

  IFID if_id_latch (
      .clk(clk),
      .rstn(rstn),
      .immode(immode),
      .ins(ins),
      .pc_in(pc_in),
      .rdn(rdn),
      .rs1n(rs1n),
      .rs2n(rs2n),
      .imm(imm),
      .pc(pc)
  );

  GPR registers (
      .clk (cache_clk),
      .rstn(rstn),
      .wbe (wbe),
      .rs1n(rs1n),
      .rs2n(rs2n),
      .rdn (rdn_in),
      .rdd (rdd),
      .rs1d(rs1d),
      .rs2d(rs2d)
  );

  Branch_Addr_Calc branch_address (
      .addr_mode(addr_mode),
      .branch_taken(branch_taken),
      .imm(imm),
      .rs1d(rs1d),
      .pc_in(pc),
      .branch_addr(branch_addr),
      .npc(npc)
  );

endmodule
