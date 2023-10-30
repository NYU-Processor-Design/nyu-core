//Branch Address Conditions
parameter PC = 0;   //Case when branch_addr = pc + imm
parameter RD = 1;   //Case when branch_addr = imm + rs1d

module Branch_Addr_Calc # (
    WordSize = 32
)(
    input addr_mode, branch_taken,
    input [WordSize - 1:0] imm, rs1d, pc_in,
    output logic [WordSize - 1:0] branch_addr, npc
);

always_comb begin
    case(addr_mode)
        PC:
            case (branch_taken)
                1'b0: begin
                    branch_addr = pc_in + imm;
                    npc = pc_in;
                end
                1'b1: begin
                    branch_addr = pc_in + imm;
                    npc = branch_addr; 
                end 
            endcase
        RD:
            case (branch_taken)
                1'b0: begin
                    branch_addr = imm + rs1d;
                    npc = pc_in;
                end
                1'b1: begin
                    branch_addr = imm + rs1d;
                    npc = branch_addr;
                end
            endcase
        default: begin
            branch_addr = pc_in + imm;
            npc = pc_in;
        end
    endcase
end

endmodule