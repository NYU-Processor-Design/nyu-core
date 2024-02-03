module Con_Branch_Cont #(
    WordSize=32
)(
    input clk,rstn,rstn_h,pred_taken,
    input [1:0] branch_occr, branch_cond,
    input [WordSize-1:0] pred_pc, pred_adder,alu_out,npc_in,
    output logic [WordSize-1:0] npc,
    output logic rstn_out,branch_taken
);

logic act_taken,flush;
logic [WordSize-1:0] npc_corr;

Pipeline_Reset #(WordSize) pipeline_reset_module(.npc_in(npc_in),.npc_corr(npc_corr),.flush(flush),.npc(npc),.rstn_out(rstn_out));
Branch_Predictor branch_predictor(.clk(clk),.rstn_h(rstn_h),.act_taken(act_taken),.pred_taken(pred_taken),.branch_occr(branch_occr),.branch_cond(branch_cond),.branch_taken(branch_taken));
Branch_Manager  branch_manager(.clk(clk),.rstn(rstn),.pred_taken(pred_taken),.pred_pc(pred_pc),.pred_adder(pred_adder),.act_taken(act_taken),.flush(flush),.npc(npc));
Branch_Eval #(WordSize) branch_eval(.alu_out(alu_out),.branch_cond(branch_cond),.act_taken(act_taken));

endmodule

