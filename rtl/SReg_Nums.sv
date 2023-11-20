interface SReg_Nums();

logic [4:0] rs1n, rs2n;

modport if_id (
output [4:0] rs1n, rs2n
);

modport registers (
input [4:0] rs1n, rs2n
);
endinterface
