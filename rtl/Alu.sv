
//ALU opcode definitions
parameter ADD = 6'h00;
parameter SUB = 6'h20;
parameter XOR = 6'h04;
parameter OR = 6'h06;
parameter AND = 6'h07;
parameter LLS = 6'h01;
parameter LRS = 6'h05;
parameter ARS = 6'h25;
parameter SSLT = 6'h02;
parameter USLT = 6'h03;


module Alu #(
    WordSize = 32
) (
    input [WordSize - 1:0] a,
    input [WordSize - 1:0] b,
    input [5:0] alu_mode,
    output logic [WordSize - 1:0] alu_out
);
  always_comb begin
    case (alu_mode)
      ADD: alu_out = a + b;
      SUB: alu_out = a - b;
      XOR: alu_out = a ^ b;
      OR: alu_out = a | b;
      AND: alu_out = a & b;
      LLS: alu_out = a << b[4:0];
      LRS: alu_out = a >> b[4:0];
      ARS: alu_out = $signed(a) >>> b[4:0];
      SSLT: alu_out = WordSize'($signed(a) < $signed(b));
      USLT: alu_out = WordSize'(a < b);
      default: alu_out = 0;
    endcase
  end
endmodule
