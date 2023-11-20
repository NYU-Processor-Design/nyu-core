interface Int_DCache_Manager_Control();

logic dcache_en, dcache_rw;
logic [1:0] data_mode;

modport general_control (
output dcache_en, dcache_rw,
output [1:0] data_mode
);

modport dcache_manager {
input dcache_en, dcache_rw,
input [1:0] data_mode
};
endinterface
