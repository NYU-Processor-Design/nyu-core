interface Int_DReg_Info #(
  WordSize = 32
)();

logic [WordSize - 1:0] rdd;
logic [4:0] rdn;

modport mem_wb (
output [WordSize - 1:0] rdd,
output [4:0] rdn
);

modport registers (
input [WordSize - 1:0] rdd,
input [4:0] rdn
);
endinterface
