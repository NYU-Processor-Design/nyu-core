module Pipeline_Reset #(
    WordSize = 32
) (
    input [WordSize - 1:0] npc_in,
    input [WordSize - 1:0] npc_corr,
    input flush,
    output logic [WordSize - 1:0] npc,
    output logic rstn_out
);

  always_comb begin
    case (flush)
      0: begin
        npc = npc_in;
        rstn_out = 1'bZ;
      end
      1: begin
        npc = npc_corr;
        rstn_out = 0;
      end
    endcase
  end
endmodule
