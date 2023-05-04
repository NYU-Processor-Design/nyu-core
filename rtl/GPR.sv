module GPR #(
  WordSize = 32
)(
  input clk, rstn, wbe,
  input [4:0] rs1n, rs2n, rdn,
  input [WordSize - 1:0] rdd,
  output logic [WordSize - 1:0] rs1d, rs2d
);
  
  
  logic [31:0] registers [31:0];
  assign registers[0] = 32'd0;
  
  integer i;
  always @ (posedge clk or negedge rstn) begin
    if (rstn == 0)
      initial begin
        for (i = 0; i < 32; i = i+1)
          registers[i] <= 32'd0;
      end
    else begin
      rs1d <= registers[rs1n];
      rs2d <= registers[rs2n];
      if (wbe)
        registers[rdn] <= rdd;
    end
  end
endmodule
