module Imm_extender (
    input [11:0] imm,
    output logic [31:0] out
);

assign out = {{20{imm[11]}}, imm};

endmodule