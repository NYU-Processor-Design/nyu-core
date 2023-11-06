module IDEX #(
  WordSize = 32
)(
  input clk, rstn, branch_taken_in,
  input[1:0] a_sel, b_sel,
  input[31:0] ins,
  input[WordSize - 1:0] pc_in, imm, rs1d, rs2d_in, branch_addr_in,
  input[4:0] rdn_in,
  output logic branch_taken,
  output logic [4:0] rdn,
  output logic [WordSize - 1:0] pc, branch_addr, a, b, rs2d
);
  
  always @ (posedge clk or negedge rstn) begin
    if (!rstn) begin
      rdn <= 0;
      a <= 0;
      b <= 0;
      branch_addr <= 0;
      pc <= 0;
      rs2d <= 0;
      branch_taken <= 0;
    end
    else begin
      rdn <= rdn_in;
      branch_taken <= branch_taken_in;
      rs2d <= rs2d_in;
      branch_addr <= branch_addr_in;
      pc <= pc_in;
      case(a_sel)
        0: a <= rs1d;
        1: a <= pc_in;
        3: a <= 0;
      default a <= 0;
      endcase
      case(b_sel)
        0: b <= rs2d_in;
        1: b <= imm;
        2: b <= 4;
        3: b <= imm << 12;
      default b <= 0;
      endcase
    end
  end
endmodule
