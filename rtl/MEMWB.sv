module MEMWB #(
    WordSize = 32
) (
    input clk,
    input rstn,
    input [2:0] wbs,
    input [4:0] rdn_in,
    input [WordSize - 1:0] alu_out,
    input [WordSize - 1:0] mrd,
    output logic [4:0] rdn,
    output logic [WordSize - 1:0] rdd
);

  always_ff @(posedge clk, negedge rstn) begin
    if (!rstn) begin
      rdn <= 0;
      rdd <= 0;
    end else begin
      rdn <= rdn_in;
      case (wbs)
        0: rdd <= {{{WordSize - 8{mrd[7]}}}, mrd[7:0]};
        1: rdd <= {{{WordSize - 16{mrd[15]}}}, mrd[15:0]};
        2: rdd <= mrd;
        3: rdd <= alu_out;
        4: rdd <= {{{WordSize - 8{1'b0}}}, mrd[7:0]};
        5: rdd <= {{{WordSize - 16{1'b0}}}, mrd[15:0]};
        default rdd <= 0;
      endcase
    end
  end
endmodule
