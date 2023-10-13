# MEM Interface #
(Connects EX/MEM Latch to MEM/WB Latch)

## Contents
* [Modules](#modules)
  * [EX/MEM Latch](#ex/mem_latch)
  * [Module 2](#mem/wb_latch)

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

## Connections

|EX/MEM|MEM/WB|
|:---|:---:|
|```rdn```|```rdn_in```|
|```alu_out```|```alu_out```|
