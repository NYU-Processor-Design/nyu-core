module Branch_Manager #(
  WordSize = 32
)(
    input clk, rstn, pred_taken, act_taken,
    input [WordSize - 1:0] pred_pc, pred_addr,
    output logic flush,
    output logic [WordSize - 1:0] npc
);

logic restart;

always @ (posedge clk or negedge rstn) begin
    if (!rstn) begin
      restart <= 1;
      flush <= 0;
      npc <= 0;
    end
    else begin
      if ((pred_taken != act_taken) && !restart) begin
        flush <= 1;
        case(act_taken)
        0: npc <= pred_pc + 4;
        1: npc <= pred_addr;
        endcase
      end
      else begin
        flush <= 0;
        case(pred_taken)
        0: npc <= pred_pc + 4;
        1: npc <= pred_addr;
        endcase
      end
      if (restart) restart <= 0;
    end
end
endmodule