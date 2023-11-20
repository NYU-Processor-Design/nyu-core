interface Alu_Ops #(
  WordSize = 32
)();

logic [WordSize - 1:0] a, b;

modport id_ex (
output [WordSize - 1:0] a, b
);

modport branch_manager {
input [WordSize - 1:0] a, b
};
endinterface