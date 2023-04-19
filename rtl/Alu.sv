
//ALU opcode definitions
parameter ADD = 5'h00;
parameter SUB = 5'h10;
parameter XOR = 5'h04;
parameter OR = 5'h06;
parameter AND = 5'h07;
parameter LLS = 5'h01;
parameter LRS = 5'h05;
parameter ARS = 5'h15;
parameter SSLT = 5'h02;
parameter USLT = 5'h03;


module Alu #(
  WordSize = 32
)(
    input [WordSize - 1:0] a, b,
    input [4:0] alu_mode,
    output logic [WordSize - 1:0] alu_out,
    logic[WordSize - 1:0] adder_result,
    logic do_sub, carry
);

assign do_sub = alu_mode[4] | (alu_mode == SSLT) | (alu_mode == USLT);

assign {carry, adder_result} = {1'b0, a} + {1'b0, ((B^({WordSize{do_sub}})) + {{WordSize - 1{1'b0}}, do_sub})};

always_comb begin 
    case(alu_mode)
    ADD: alu_out = adder_result;
    SUB: alu_out = adder_result;
    XOR: alu_out = a ^ b;
    OR: alu_out = a | b;
    AND: alu_out = a & b;
    LLS: alu_out = a << b[4:0];
    LRS: alu_out = a >> b[4:0];
    ARS: alu_out = a >>> b[4:0];
    SSLT: alu_out = (a[WordSize - 1] & !(b[WordSize - 1])) ? 1 : (!(a[WordSize - 1]) & b[WordSize - 1]) ? 0 : {{WordSize - 1{1'b0}}, carry^(!b[WordSize - 1])};
    USLT: alu_out = {{WordSize - 1{1'b0}}, !carry};
    default: alu_out = 0;
    endcase


end


endmodule