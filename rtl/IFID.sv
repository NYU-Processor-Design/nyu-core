module IFID #(
  WordSize = 32
)(
  input clk, rstn,
  input[2:0] immode,
  input[31:0] ins,
  input[WordSize - 1:0] pc_in,
  output logic [4:0] rdn, rs1n, rs2n,
  output logic [31:0] imm,
  output logic [WordSize - 1:0] pc
);
  
  always @ (posedge clk or negedge rstn) begin
    if (!rstn) begin
      rdn <= 0;
      rs1n <= 0;
      rs2n <= 0;
      pc <= 0;
      imm = 0;
    end
    else begin
      pc <= pc_in;
      rdn <= ins[11:7];
      rs1n <= ins[19:15];
      rs2n <= ins[24:20];
      case(immode)
        1: imm = {{20{ins[31]}}, ins[31:20]};
        2: imm = {{20{ins[31]}}, ins[31:25], ins[11:7]};
        3: imm = {{19{ins[31]}}, ins[31], ins[7], ins[30:25], ins[11:8], 1'b0};
        4: imm = {ins[31:12], 12'b0};
        5: imm = {11'b0, ins[31], ins[19:12], ins[20], ins[30:21], 1'b0};
      default imm = 0;
      endcase
    end
      
  end
  
endmodule
