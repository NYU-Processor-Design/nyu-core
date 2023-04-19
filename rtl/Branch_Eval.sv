
//Branch condition definitions
parameter NE = 2'h0; //Non branching instruction
parameter ALU = 2'h1; //Branch condition is < or !=
parameter NALU = 2'h2; //Branch condition is >= or =
parameter AL = 2'h3; //Jump instruction



module Branch_Eval #(
  WordSize = 32
)(
    input [WordSize - 1:0] alu_out,
    input [1:0] branch_cond,
    output logic branch_taken
);

always_comb begin 
    case(branch_cond)
        NE: branch_taken = 0;  
        ALU: branch_taken = |alu_out;
        NALU: branch_taken = ~(|alu_out);
        AL: branch_taken = 1;
        default: branch_taken = 0;
    endcase
end


endmodule