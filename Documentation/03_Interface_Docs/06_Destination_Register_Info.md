# Destination Register Info #

## Contents
* [Modules](#modules)
  * [MEM/WB Latch](#mem/wb_latch)
  * [General Purpose Registers](#general_purpose_registers)

## Modules

### MEM/WB Latch

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```rdn```|5-bit|
|```rdd```|32-bit|

### Registers

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```rdn```|5-bit|
|```rdd```|32-bit|

## Connections

|MEM/WB|Registers|
|:---|:---:|
|```rdn```|```rdm```|
|```rdd```|```rdd```|

