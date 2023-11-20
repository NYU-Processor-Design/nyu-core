interface Branch_Manager_Input #(
  WordSize = 32
)();

logic [WordSize - 1:0] pc, addr;
logic taken;

modport id_ex (
output [WordSize - 1:0] pc, addr,
output taken
);

modport branch_manager (
input [WordSize - 1:0] pc, addr,
input taken
);

modport branch_predictor (
input taken
);
  
endinterface
