module Pipeline_Reset #(
  WordSize = 32
)(
  input [WordSize - 1:0] npc_in, npc_corr,
  input flush,
  output [WordSize - 1:0] npc,
  output logic rstn
);

always_comb begin
case(flush)
0: begin
    npc = npc_in;
    rstn = 1'bZ;
end
1: begin
    npc = npc_corr;
    rstn = 0;
end
endcase
end
endmodule