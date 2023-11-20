interface Data_Cache_Manager_Control();

logic dcache_en, dcache_rw;
logic [1:0] data_mode;

modport if_id (
output dcache_en, dcache_rw,
output [1:0] data_mode
);

modport id_ex {
input dcache_en, dcache_rw,
input [1:0] data_mode
};
endinterface