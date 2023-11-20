interface Int_Branch_Manager_Input #(
  WordSize = 32
)();

logic [WordSize - 1:0] pc, addr;
logic taken;

modport id_ex (
output pc, addr, taken
);

modport branch_manager (
input pc, addr, taken
);

modport branch_predictor (
input taken
);
  
endinterface
