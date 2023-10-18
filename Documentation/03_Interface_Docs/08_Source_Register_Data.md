# Source Register Data #

## Contents
* [Modules](#modules)
  * [General Purpose Registers](#general_purpose_registers)
  * [ID/EX Latch](#id/ex_latch)
* [Connections](#connections)

## Modules

### General Purpose Registers

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```rs1d```|32-bit|
|```rs2d```|32-bit|

### Module 2

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```rs1d```|32-bit|
|```rs2d_in```|32-bit|

## Connections

|General Purpose Registers|ID/EX Latch|
|:---|:---:|
|```rs1d```|```rs1d```|
|```rs2d```|```rs2d_in```|
