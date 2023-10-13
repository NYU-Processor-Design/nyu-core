# EX Interface #
(Connects Outputs of ID/EX Latch to Inputs of EX/MEM Latch)

## Contents
* [Modules](#modules)
  * [ID/EX Latch](#id/ex_latch)
  * [EX/MEM Latch](#ex/mem_latch)
* [Connections](#connections)

## Modules

### ID/EX Latch

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```rdn```|5-bits|
|```rs2d```|32-bits|

### EX/MEM Latch

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```rdn_in```|5-bits|
|```rs2d```|32-bits|


## Connections

|ID/EX|EX/MEM|
|:---|:---:|
|```rdn```|```rdn_in```|
|```rs2d```|```rs2d```|
