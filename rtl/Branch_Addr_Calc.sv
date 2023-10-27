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
        PC: begin
            branch_addr = pc + imm;
            if (branch_taken): begin
                npc = branch_addr;
            end
            else begin
                npc = pc;
            end
        end
        RD: begin
            branch_addr = imm + rs1d;
            if (branch_taken): begin
                npc = branch_addr;
            end
            else begin
                npc = pc;
            end
        end
        default: begin
            branch_addr = pc + imm;
            npc = pc;
        end
    endcase
end

endmodule