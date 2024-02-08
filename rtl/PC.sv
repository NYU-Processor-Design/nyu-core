
module PC #(
    WordSize = 32
) (
    input clk,
    input rstn,
    input pc_en,
    input [WordSize - 1:0] npc,
    output logic [WordSize - 1:0] pc
);

  always_ff @(posedge clk, negedge rstn) begin
    if (rstn == 0) pc <= 0;
    else begin
      if (pc_en) pc <= npc;
    end
  end
endmodule
