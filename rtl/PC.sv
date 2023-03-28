
module PC #(
  WordSize = 32
)(
  input clk,
  input rstn,
  input [WordSize - 1:0] npc,
  output logic [WordSize - 1:0] pc
);
  
  always @ (posedge clk or posedge rstn) begin
    if (rstn == 0)
      pc <= 0;
    else
      pc <= npc;
  end
  
endmodule
