module EXMEM #(
    WordSize = 32
) (
    input clk,
    input rstn,
    input [4:0] rdn_in,
    input [WordSize - 1:0] alu_out_in,
    input [WordSize - 1:0] rs2d,
    output logic [4:0] rdn,
    output logic [WordSize - 1:0] alu_out,
    output logic [WordSize - 1:0] mem_data
);

  always_ff @(posedge clk, negedge rstn) begin
    if (!rstn) begin
      rdn <= 0;
      alu_out <= 0;
      mem_data <= 0;
    end else begin
      rdn <= rdn_in;
      alu_out <= alu_out_in;
      mem_data <= rs2d;
    end
  end
endmodule
