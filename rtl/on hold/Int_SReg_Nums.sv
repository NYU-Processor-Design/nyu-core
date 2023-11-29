interface Int_SReg_Nums();

logic [4:0] rs1n, rs2n;

modport if_id (
output rs1n, rs2n
);

modport registers (
input rs1n, rs2n
);
endinterface
