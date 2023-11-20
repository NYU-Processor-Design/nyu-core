# MEM Interface #
(Connects EX/MEM Latch to MEM/WB Latch and Data Cache Manager)

## Contents
* [Modules](#modules)
  * [EX/MEM Latch](#ex/mem_latch)
  * [MEM/WB Latch](#mem/wb_latch)
  * [Data Cache Manager](#data_cache_manager)

## Modules

### EX/MEM Latch

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```rdn```|5-bit|
|```alu_out```|32-bit|

### MEM/WB Latch

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```rdn_in```|5-bit|
|```alu_out```|32-bit|

### Data Cache Manager

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```addr```|32-bit|


## Connections

|EX/MEM|MEM/WB|Data Cache Manager|
|:---|:---:|:---:|
|```rdn```|```rdn_in```|
|```alu_out```|```alu_out```|```addr```|
