module Imm_extender #(
  InputWordSize = 12,
  OutputWordSize = 32
)(
    input [InputWordSize  - 1:0] imm,
    output logic [OutputWordSize - 1:0] out
);

assign out = {{(OutputWordSize - InputWordSize){imm[InputWordSize - 1]}}, imm};

endmodule