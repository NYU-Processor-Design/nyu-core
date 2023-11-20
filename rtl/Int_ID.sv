interface Int_ID #(
  WordSize = 32
)();

logic [WordSize - 1:0] imm, pc;
logic [4:0] rdn;

modport if_id (
output [WordSize - 1:0] imm, pc,
output [4:0] rdn
);

modport id_ex (
input [WordSize - 1:0] imm, pc,
input [4:0] rdn
);

modport branch_addr_calc (
input [WordSize - 1:0] imm, pc,
);
endinterface
