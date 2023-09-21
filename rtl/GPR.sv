module GPR #(
  WordSize = 32
)(
  input clk, rstn, wbe,
  input [4:0] rs1n, rs2n, rdn,
  input [WordSize - 1:0] rdd,
  output logic [WordSize - 1:0] rs1d, rs2d
);
  
  logic [31:0] registers [31:1]; 
  
  integer i;

  //if this doesn't work, try setting regs to 0 outside of always 

  always @ (posedge clk or negedge rstn) begin
    if (rstn == 0)
      begin
        for (i = 1; i < 32; i = i+1) begin
          registers[i] <= 32'd0;
        end
      end
    else begin
      //rs1d <= registers[rs1n];
      //rs2d <= registers[rs2n];
      if (wbe && rdn != 0)
        registers[rdn] <= rdd;
    end
  end

  assign rs1d = (rs1n == 0) ? 32'd0 : registers[rs1n];
  assign rs2d = (rs1n == 0) ? 32'd0 : registers[rs1n];

endmodule
