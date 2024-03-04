# Data Cache #
(Verilog module known as Conn_Data_Cache)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [Data Cache Manager](#instruction_cache_manager)
  * [L1 Data Cache](#l1_instruction_cache)
  * [L2 Data Cache](#l1_instruction_cache)
  * [L3 Data Cache](#l1_instruction_cache)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```cache_clk```|1-bit|
|```rstn```|1-bit|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bit|
|```addr```|32-bit|
|```data```|32-bit|
|```

## Outputs
|Name|Bits wide|
|:---|:---:|
|```mrd```|32-bit|
|```

## Modules

### Data Cache Manager

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

### L1 Data Cache

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

### L2 Data Cache

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

### L3 Data Cache

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

## Internal Connections

|Module 1|Module 2|Module N|
|:---:|:---:|:---:|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
