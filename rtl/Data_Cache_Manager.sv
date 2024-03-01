module Data_Cache_Manager #(
    WordSize = 32
) (
    input dcache_en,
    input dcache_rw,
    input mem_request,
    input mem_write_enable,
    input mem_busy,
    output logic write_enable,
    output logic read_enable,
    output logic mem_ready,
    output logic wEn,
    output logic rEn,
    output logic isBurst
);

assign write_enable = dcache_en & dcache_rw;
assign read_enable = dcache_en & ~dcache_rw;
assign isBurst = 0;
assign mem_ready = ~mem_busy;
assign wEn = mem_request & mem_write_enable;
assign rEn = mem_request & ~mem_write_enable;

endmodule