# Data Cache #
(Verilog module known as Conn_Data_Cache)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [Data Cache Manager](#data_cache_manager)
  * [L1 Data Cache](#l1_data_cache)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```cache_clk```|1-bit|
|```rstn_h```|1-bit|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bit|
|```request_address```|32-bit|
|```write_data```|32-bit|
|```mem_response_data```|32-bit|
|```mem_busy```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```response_data```|32-bit|
|```wEn```|1-bit|
|```rEn```|1-bit|
|```isBurst```|1-bit|
|```mem_address```|32-bit|
|```mem_write_data```|32-bit|

## Modules

### Data Cache Manager

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```dcache_en```|1-bit|
|```dchache_rw```|1-bit|
|```mem_busy```|1-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```wEn```|1-bit|
|```rEn```|1-bit|
|```isBurst```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```mem_request```|1-bit|
|```mem_write_enable```|1-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```write_enable```|1-bit|
|```read_enable```|1-bit|
|```mem_ready```|1-bit|

### L1 Data Cache

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```request_address```|32-bit|
|```write_data```|32-bit|
|```mem_response_data```|32-bit|
|```data_mode```|2-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```response_data```|32-bit|
|```mem_address```|32-bit|
|```mem_write_data```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```write_enable```|1-bit|
|```read_enable```|1-bit|
|```mem_ready```|1-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```mem_request```|1-bit|
|```mem_write_enable```|1-bit|


## Internal Connections

|Data Cache Manager|L1 Data Cache|M
|:---:|:---:|
|```write_enable```|```write_enable```|
|```read_enabke```|```read_enable```|
|```mem_ready```|```mem_ready```|
|```mem_request```|```mem_request```|
|```mem_write_enable```|```mem_write_enable```|
