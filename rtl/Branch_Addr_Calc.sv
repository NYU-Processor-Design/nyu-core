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
        PC: begin
            branch_addr = pc_in + imm;
            case (branch_taken)
                2'b00: npc = pc_in;
                2'b01: npc = branch_addr;
        end
        RD: begin
            branch_addr = imm + rs1d;
            case (branch_taken)
                2'b00: npc = pc_in;
                2'b01: npc = branch_addr;
        end
        default: begin
            branch_addr = pc_in + imm;
            npc = pc_in;
        end
    endcase
end

endmodule