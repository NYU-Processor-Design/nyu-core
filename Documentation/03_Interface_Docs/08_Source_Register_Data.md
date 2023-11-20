# Source Register Data #

## Contents
* [Modules](#modules)
  * [General Purpose Registers](#general_purpose_registers)
  * [ID/EX Latch](#id/ex_latch)
  * [Branch Address Calculator](#branch_address_calculator)
* [Connections](#connections)

## Modules

### General Purpose Registers

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```rs1d```|32-bit|
|```rs2d```|32-bit|

### ID/EX Latch

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```rs1d```|32-bit|
|```rs2d_in```|32-bit|

### Branch Address Calculator

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```rs1d```|32-bit|

## Connections

|General Purpose Registers|ID/EX Latch|Branch Address Calculator|
|:---|:---:|:---:|
|```rs1d```|```rs1d```|```rs1d```|
|```rs2d```|```rs2d_in```|
