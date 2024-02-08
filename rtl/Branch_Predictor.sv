module Branch_Predictor (
    input clk,
    input rstn_h,
    input act_taken,
    input pred_taken,
    input [1:0] branch_occr,
    input [1:0] branch_cond,
    output logic branch_taken
);
  logic curr_pred, incorrect_pred;

  always_ff @(posedge clk or negedge rstn_h) begin
    if (!rstn_h) begin
      curr_pred <= 0;
      incorrect_pred <= 0;
    end else begin
      if (^branch_cond == 0) begin
        curr_pred <= curr_pred;
        incorrect_pred <= incorrect_pred;
      end else if (act_taken ^ pred_taken == 0) begin
        curr_pred <= curr_pred;
        incorrect_pred <= 0;
      end else if (incorrect_pred) begin
        curr_pred <= ~curr_pred;
        incorrect_pred <= 1;
      end else begin
        curr_pred <= curr_pred;
        incorrect_pred <= 1;
      end
    end
  end

  always_comb begin
    case (branch_occr[1])
      0: branch_taken = branch_occr[0];
      1: branch_taken = curr_pred;
    endcase
  end

endmodule
