interface Int_Alu_Ops #(
  WordSize = 32
)();

logic [WordSize - 1:0] a, b;

modport id_ex (
output a, b
);

modport alu (
input a, b
);
endinterface
