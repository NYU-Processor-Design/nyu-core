# MEM Connection Module #
(Verilog module known as Con_MEM)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [EX/MEM Latch](#exmem_latch)
  * [Data Cache](#data_cache)
* [Internal Connections](#internal_connections)


## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```rstn_h```|1-bit|
|```cache_clk```|1-bit|
|```rdn_in```|5-bits|
|```alu_out_in```|32-bits|
|```rs2d```|32-bits|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bits|
|```mem_response_data```|32-bits|
|```mem_busy```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```rdn```|5-bits|
|```alu_out```|32-bits|
|```response_data```|32-bits|
|```wEn```|1-bit|
|```rEn```|1-bit|
|```isBurst```|1-bit|

## Modules

### EX/MEM Latch

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```rdn_in```|5-bits|
|```alu_out_in```|32-bits|
|```rs2d```|32-bits|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```rdn```|5-bits|
|```alu_out```|32-bits|

#### Internal IO

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```mem_data```|32-bits|

### Data Cache

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```cache_clk```|1-bit|
|```rstn_h```|1-bit|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bits|
|```mem_response_data```|32-bit|
|```mem_busy```|1-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```wEn```|1-bit|
|```rEn```|1-bit|
|```isBurst```|1-bit|
|```mem_address```|32-bit|
|```mem_write_data```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```request_address```|32-bits|
|```write_data```|32-bits|

#### External IO

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```mrd```|32-bits|

## Internal Connections

|EX/MEM|Data Cache|
|:---:|:---:|
|```alu_out```|```request_addresss```|
|```mem_data```|```write_data```|
