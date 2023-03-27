
//Branch condition definitions
parameter NE = 2'h0; //Non branching instruction
parameter ALU = 2'h1; //Branch condition is < or !=
parameter NALU = 2'h02; //Branch condition is >= or =
parameter AL = 2'h03; //Jump instruction



module Branch_Eval #(
  WordSize = 32
)(
    input [WordSize - 1:0] ALU_Out,
    input [3:0] Cond,
    output logic Branch_Taken
);

always_comb begin 
    case(Cond)
    NE: Branch_Taken = 0;  
    ALU: Branch_Taken = |ALU_Out
    NALU: Branch_Taken = ~(|ALU_Out)
    AL: Branch_Taken = 1;
    default: Branch_Taken = 0;
    endcase
end


endmodule