interface Int_MEM #(
  WordSize = 32
)();

logic [WordSize - 1:0] alu_out;
logic [4:0] rdn;

modport ex_mem (
  output alu_out, rdn
);

modport mem_wb (
input alu_out, rdn
);

modport dcache_manager (
input alu_out,
);
  
endinterface
