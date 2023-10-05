module EXMEM #(
  WordSize = 32
)(
  input clk, rstn,
  input [4:0] rdn_in,
  input [Wordsize - 1:0] alu_out_in, rs2d,
  input branch_taken_in,
  output branch_taken,
  output logic [4:0] rdn,
  output logic [Wordsize - 1:0] alu_out, mem_data
);

  always @ (posedge clk or negedge rstn) begin
    if (!rstn) begin
      rdn <= 0;
      alu_out <= 0;
      mem_data <= 0;
      branch_taken <= 0;
    end
    else begin
      rdn <= rdn_in;
      alu_out <= alu_out_in;
      branch_taken <= branch_taken_in;
      mem_data <= rs2d;
    end
  end
endmodule
