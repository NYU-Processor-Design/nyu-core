interface DReg_Info #(
  WordSize = 32
)();

logic [WordSize - 1:0] rdd;
logic [4:0] rdn;

modport id_ex (
output [WordSize - 1:0] rdd,
output [4:0] rdn
);

modport branch_manager {
input [WordSize - 1:0] rdd,
input [4:0] rdn
};
endinterface