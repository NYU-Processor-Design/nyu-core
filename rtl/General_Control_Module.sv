module GENERAL_CONTROL_MODULE(
    input clk,
    input rstn,
    input ins [31:0],

    output pc_en,
    output immode[2:0],
    output wbe,
    output branch_occr[1:0],
    output a_sel[1:0],
    output b_sel[1:0],
    output alu_mode[5:0],
    output branch_cond[1:0],
    output data_mode[1:0],
    output dcache_rw,
    output dcache_en,
    output wbs[2:0]
);

logic ID_ins[31:0], EX_ins[31:0], MEN_ins[31:0], WB_ins[31:0], hazard;

parameter
    R = 7'b0110011, 
    I_1 = 7'b0010011,
    I_2 = 7'b0000011, 
    I_3 = 7'b1100111,
    S = 7'b0100011, 
    B = 7'b1100011,
    U1 = 7'b0110111, 
    U2 = 7'b0010111,
    J = 7'b1101111, 
    NOP1 = 7'b0000000, 
    NOP2 = 7'b0001111, 
    NOP3 = 7'b1110011;





endmodule