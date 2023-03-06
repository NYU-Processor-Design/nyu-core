
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
    input [WordSize - 1:0] operand_a, operand_b,
    input [3:0] op_code_1,
    input op_code_2,
    output logic [WordSize - 1:0] out,
    logic[4:0] op_code,
    logic[WordSize - 1:0] adder_result,
    logic do_sub, carry
);

assign op_code = {op_code_2, op_code_1};

assign do_sub = op_code_2 | (op_code == SSLT) | (op_code == USLT);

assign {carry, adder_result} = {1'b0, operand_a} + {1'b0, ((operand_b^({WordSize{do_sub}})) + {{WordSize - 1{1'b0}}, do_sub})};

always_comb begin 
    case(op_code)
    ADD: out = adder_result;
    SUB: out = adder_result;
    XOR: out = operand_a ^ operand_b;
    OR: out = operand_a | operand_b;
    AND: out = operand_a & operand_b;
    LLS: out = operand_a << operand_b[4:0];
    LRS: out = operand_a >> operand_b[4:0];
    ARS: out = operand_a >>> operand_b[4:0];
    SSLT: out = (operand_a[WordSize - 1] & !(operand_b[WordSize - 1])) ? 1 : (!(operand_a[WordSize - 1]) & operand_b[WordSize - 1]) ? 0 : {{WordSize - 1{1'b0}}, carry^(!operand_b[WordSize - 1])};
    USLT: out = {{WordSize - 1{1'b0}}, !carry};
    default: out = 0;
    endcase


end


endmodule