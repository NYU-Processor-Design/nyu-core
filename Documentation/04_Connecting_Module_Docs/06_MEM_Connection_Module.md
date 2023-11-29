# MEM Connection Module #

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [EX/MEM Latch](#exmem_latch)
  * [Data Cache Manager](#data_cache_manager)
* [Internal Connections](#internal_connections)


## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```cache_clk```|1-bit|
|```rdn_in```|5-bits|
|```alu_out_in```|32-bits|
|```rs2d```|32-bits|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```rdn```|5-bits|
|```alu_out```|32-bits|
|```mrd```|32-bits|

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
|```rdn```|5-bits|
|```alu_out```|32-bits|

#### Internal IO

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```mem_data```|32-bits|

### Data Cache Manager

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```cache_clk```|1-bit|
|```rstn```|1-bit|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bits|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```addr```|32-bits|
|```data```|32-bits|

#### External IO

#### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```mrd```|32-bits|

## Internal Connections

|EX/MEM|Data Cache Manager|
|:---:|:---:|
|```alu_out```|```addr```|
|```mem_data```|```data```|
