//Branch Address Conditions
parameter PC = 0;   //Case when branch_addr = pc + imm
parameter RD = 1;   //Case when branch_addr = imm + rs1d
parameter BNT = 0;  //Case when branch is taken
parameter BT = 1;  //Case when branch is NOT taken

module Branch_Addr_Calc # (
    WordSize = 32
)(
    input addr_mode, branch_taken,
    input [WordSize - 1:0] imm, rs1d,
    output logic [WordSize - 1:0] branch_addr, npc
);

always_comb begin
    case(addr_mode)
        PC:
            branch_addr = pc + imm;
            case(branch_taken)
                BNT: 
                    npc = pc;
                BT:
                    npc = branch_addr;
            endcase
        RD:
            branch_addr = imm + rs1d;
            case(branch_taken)
                BNT: 
                    npc = pc;
                BT:
                    npc = branch_addr;
            endcase
        default: 
            branch_addr = pc + imm;
            npc = pc;
    endcase
end

endmodule