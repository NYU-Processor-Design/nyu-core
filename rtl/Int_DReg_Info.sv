interface Int_DReg_Info #(
  WordSize = 32
)();

logic [WordSize - 1:0] rdd;
logic [4:0] rdn;

modport mem_wb (
output rdd, rdn
);

modport registers (
  input rdd, rdn
);
endinterface
