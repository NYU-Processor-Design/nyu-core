interface MEM #(
  WordSize = 32
)();

logic [WordSize - 1:0] alu_out;
logic [4:0] rdn;

modport ex_mem (
output [WordSize - 1:0] alu_out,
output [4:0] rdn
);

modport mem_wb (
input [WordSize - 1:0] alu_out,
input [4:0] rdn
);

modport dcache_manager (
input [WordSize - 1:0] alu_out,
);
  
endinterface
