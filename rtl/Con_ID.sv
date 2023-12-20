module Con_ID #(
  WordSize = 32
)(
  input clk, cache_clk, rstn, wbe, addr_mode, branch_taken,
  input [2:0] immode,
  input [4:0] rdn_in;
  input[WordSize - 1:0] ins, pc_in, rdd,
  output logic [4:0] rdn,
  output logic [WordSize - 1:0] imm, pc, rs1d, rs2d, npc, branch_addr
);
  
logic [4:0] rs1n, rs2n;

IFID if_id_latch(.clk(clk), .rstn(rstn), .immode(immode), .ins(ins), .pc_in(pc_in), .rdn(rdn), .rs1n(rs1n), .rs2n(rs2n), .imm(imm), .pc(pc));

GPR registers(.clk(cache_clk), .rstn(rstn), .wbe(wbe), .rs1n(rs1n), .rs2n(rs2n), .rdn(rdn_in), .rdd(rdd), .rs1d(rs1d), .rs2d(rs2d));

Branch_Addr_Calc branch_address(.addr_mode(addr_mode), .branch_taken(branch_taken), .imm(imm), .rs1d(rs1d), .pc_in(pc), .branch_addr(branch_addr), .npc(npc));

endmodule