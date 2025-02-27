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

logic ID_ins[31:0], EX_ins[31:0], MEM_ins[31:0], WB_ins[31:0];
logic hazard;

//Opcodes
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


always_comb //immmode selection
begin
    case (ins[6:0])
        R: immode = 3'd0;
        I_1, I_2, I_3: immode = 3'd1;
        S: immode = 3'd2;
        B: immode = 3'd3;
        U1, U2: immode = 3'd4;
        J: immode = 3'd5;
        NOP1, NOP2, NOP3: immode = 3'd0;
        default: immode = 3'd0;
    endcase
end

always_ff @(posedge clk or negedge rstn) 
begin
    if (!rstn) begin //asych active low reset
        ID_ins <= 32'd0;
        EX_ins <= 32'd0;
        MEM_ins <= 32'd0;
        WB_ins <= 32'd0;
        hazard <= 1'b0; // Initialize hazard to 0 on reset
    end

    else if (hazard) begin
        ID_ins <= 32'd0; // NOP
    end

    else begin
        ID_ins <= ins;
        EX_ins <= ID_ins;
        MEM_ins <= EX_ins;
        WB_ins <= MEM_ins;
    end
end

// Hazard detection
always_comb 
begin
    pc_en = !hazard;

    if ((ins[6:0] == I_3 || ins[6:0] == B || ins[6:0] == J) && !hazard) 
    begin
        hazard = 1;
    end

    else if (ins[6:0] == R || ins[6:0] == I_1 || ins[6:0] == I_2 || ins[6:0]== I_3 || ins[6:0] == S || ins[6:0] == B || ins[6:0] == U1|| ins[6:0] == U2 || ins[6:0] == J) 
    begin
        if ((ID_ins[6:0] == R || ID_ins[6:0] == I_1 || ID_ins[6:0] == I_2 || ID_ins[6:0] == I_3 || ID_ins[6:0] == U1 || ID_ins[6:0] == U2 || ID_ins[6:0] == J) &&
            ((ID_ins[11:7] == ins[11:7]) || (ID_ins[11:7] == ins[24:20]) || (ID_ins[11:7] == ins[19:15])) && (ID_ins[11:7] != 0)) 
        begin
            hazard = 1;
        end
        if ((EX_ins[6:0] == R ||EX_ins[6:0] == I_1 || EX_ins[6:0] == I_2 || EX_ins[6:0] == I_3 || EX_ins[6:0] == U1 || EX_ins[6:0] == U2 || EX_ins[6:0] == J) &&
            ((EX_ins[11:7] == ins[11:7]) || (EX_ins[11:7] == ins[24:20]) || (EX_ins[11:7] == ins[19:15])) && (EX_ins[11:7] != 0)) 
        begin
            hazard = 1;
        end
        if ((MEM_ins[6:0] == R || MEM_ins[6:0] == I_1 ||MEM_ins[6:0] == I_2 || MEM_ins[6:0] == I_3 || MEM_ins[6:0] == U1 || MEM_ins[6:0] == U2 || MEM_ins[6:0] == J) &&
            ((MEM_ins[11:7] == ins[11:7]) || (MEM_ins[11:7] == ins[24:20]) || (MEM_ins[11:7] == ins[19:15])) && (MEM_ins[11:7] != 0)) 
        begin
            hazard = 1;
        end
        if ((WB_ins[6:0] == R || WB_ins[6:0] == I_1 || WB_ins[6:0] == I_2 ||WB_ins[6:0] == I_3 || WB_ins[6:0] == U1 || WB_ins[6:0] == U2|| WB_ins[6:0] == J)&&
            ((WB_ins[11:7] == ins[11:7]) || (WB_ins[11:7] == ins[24:20]) ||(WB_ins[11:7] == ins[19:15])) && (WB_ins[11:7] != 0)) 
        begin
            hazard = 1;
        end
    end
    else
    begin
        hazard = 0;
    end
end

// output assignmetns
always_comb 
begin
    // Decode ID_ins
    case (ID_ins[6:0])
        R: begin
            addr_mode = 1'b0;
            branch_occr = 2'b00;
            a_sel = 2'b00;
            b_sel = 2'b00;
        end
        I_1: begin
            addr_mode = 1'b0;
            branch_occr = 2'b00;
            a_sel = 2'b00;
            b_sel = 2'b01;
        end
        I_2: begin
            addr_mode = 1'b0;
            branch_occr = 2'b00;
            a_sel = 2'b00;
            b_sel = 2'b00;
        end
        I_3: begin
            addr_mode = 1'b1;
            branch_occr = 2'b01;
            a_sel = 2'b01;
            b_sel = 2'b10;
        end
        S: begin
            addr_mode = 1'b1;
            branch_occr = 2'b00;
            a_sel = 2'b00;
            b_sel = 2'b00;
        end
        B: begin
            addr_mode = 1'b0;
            branch_occr = 2'b10;
            a_sel = 2'b00;
            b_sel = 2'b00;
        end
        U1, U2: begin
            addr_mode = 1'b0;
            branch_occr = 2'b00;
            a_sel = ID_ins[5:4];
            b_sel = 2'b11;
        end
        J: begin
            addr_mode = 1'b0;
            branch_occr = 2'b01;
            a_sel = 2'b01;
            b_sel = 2'b10;
        end
        NOP1, NOP2, NOP3: begin
            addr_mode = 1'b0;
            branch_occr = 2'b00;
            a_sel = 2'b00;
            b_sel = 2'b00;
        end
    endcase

    // decode ex_ins
    case (EX_ins[6:0])
        R: begin
            alu_mode = {EX_ins[31:25], EX_ins[14:12]};
            branch_cond = 2'b00;
        end
        I_1: begin
            alu_mode = (EX_ins[14:12] == 3'b101) ? {EX_ins[31:25], EX_ins[14:12]} : {3'b000, EX_ins[14:12]};
            branch_cond =2'b00;
        end
        I_2: begin
            alu_mode = 6'b000000;
            branch_cond =2'b00;
        end
        I_3: begin
            alu_mode = 6'b000000;
            branch_cond =2'b11;
        end
        S: begin
            alu_mode = 6'b000000;
            branch_cond =2'b00;
        end
        B: begin
            case(EX_ins[14:12])
                3'b100, 3'b101: alu_mode =6'b000010;
                3'b110, 3'b111: alu_mode =6'b000011;
                default: alu_mode = 6'b100000;
            endcase
            branch_cond = (EX_ins[14:12] == 3'b001 || EX_ins[14:12] == 3'b100 || EX_ins[14:12] == 3'b110) ? 2'b01 : 2'b10;
        end
        U1, U2, J: begin
            alu_mode = 6'b000000;
            branch_cond = 2'b00;
        end
        NOP1, NOP2, NOP3: begin
            alu_mode = 6'b000000;
            branch_cond = 2'b00;
        end
    endcase

    // Decode MEM_ins
    case (MEM_ins[6:0])
        R: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
        I_1: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
        I_2: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b1;
        end
        I_3: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
        S: begin
            data_mode = MEM_ins[14:12];
            dcache_rw = 1'b1;
            dcache_en = 1'b1;
        end
        B: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
        U1, U2: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
        J: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
        NOP1, NOP2, NOP3: begin
            data_mode = 2'b00;
            dcache_rw = 1'b0;
            dcache_en = 1'b0;
        end
    endcase

    // Decode WB_ins
    case (WB_ins[6:0])
        R: begin
            wbs =3'b011;
            wbe = 1'b1;
        end
        I_1: begin
            wbs = 3'b011;
            wbe = 1'b1;
        end
        I_2: begin
            wbs = WB_ins[14:12];
            wbe = 1'b1;
        end
        I_3: begin
            wbs = 3'b011;
            wbe = 1'b1;
        end
        S: 
        begin
            wbs = 3'b000;
            wbe = 1'b0;
        end
        B:
        begin
            wbs = 3'b000;
            wbe = 1'b0;
        end
        U1:begin
            wbs = 3'b011;
            wbe = 1'b1;
        end
        U2:begin
            wbs = 3'b011;
            wbe = 1'b1;
        end
        J:begin
            wbs = 3'b011;
            wbe = 1'b1;
        end
        NOP1:begin
            wbs = 3'b000;
            wbe = 1'b0;
        end
        NOP2:begin
            wbs= 3'b000;
            wbe = 1'b0;
        end
        NOP3:begin
            wbs = 3'b000;
            wbe =1'b0;
        end
    endcase

end
endmodule