THIS OUTLINE IS INCOMPLETE

# IF Connection Module #
(Verilog module known as Con_IF)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [PC](#pc)
  * [Instruction Cache](#instruction_cache)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```cache_clk```|1-bit|
|```rstn```|1-bit|
|```rstn_h```|1-bit|
|```pc_en```|1-bit|
|```npc```|32-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```pc```|32-bit|
|```ins```|32-bit|

## Modules

### PC

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```pc_en```|1-bit|
|```npc```|32-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```pc```|32-bit|

#### Internal IO

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```pc```|32-bit|

### Instruction Cache

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```cache_clk```|1-bit|
|```rstn_h```|1-bit|
|```mem_response_data```|32-bit|
|```mem_busy```|1-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```ins```|32-bit|
|```ins```|32-bit|
|```wEn```|1-bit|
|```rEn```|1-bit|
|```isBurst```|1-bit|
|```mem_address```|32-bit|
|```mem_write_data```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```pc```|32-bit|

## Internal Connections

|PC|Instruction Cache|
|:---:|:---:|:---:|
|```pc```|```pc```|
