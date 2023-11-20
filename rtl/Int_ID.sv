interface Int_ID #(
  WordSize = 32
)();

logic [WordSize - 1:0] imm, pc;
logic [4:0] rdn;

modport if_id (
  output imm, pc, rdn
);

modport id_ex (
input imm, pc, rdn
);

modport branch_addr_calc (
input imm, pc,
);
endinterface
