# ID Connection Module #
(Verilog module known as Con_ID)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [IF/ID Latch](#if_id_latch)
  * [General Purpose Registers](#general_purpose_registers)
  * [Branch Address Calculator](#branch_address_calculator)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```cache_clk```|1-bit|
|```rstn```|1-bit|
|```immode```|3-bit|
|```ins```|32-bit|
|```pc_in```|32-bit|
|```wbe```|1-bit|
|```addr_mode```|1-bit|
|```branch_taken```|1-bit|
|```rdd```|32-bit|
|```rdn_in```|5-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```imm```|32-bit|
|```pc```|32-bit|
|```rdn```|5-bit|
|```rs1d```|32-bit|
|```rs2d```|32-bit|
|```npc```|32-bit|
|```branch_addr```|32-bit|

## Modules

### IF/ID Latch

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```immode```|3-bit|
|```pc_in```|32-bit|
|```ins```|32-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```imm```|32-bit|
|```pc```|32-bit|
|```rdn```|5-bit|

#### Internal IO

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```imm```|32-bit|
|```pc```|32-bit|
|```rs1n```|5-bit|
|```rs2n```|5-bit|

### General Purpose Registers

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```cache_clk```|1-bit|
|```rstn```|1-bit|
|```wbe```|1-bit|
|```rdn_in```|5-bit|
|```rdd```|32-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```rs1d```|32-bit|
|```rs2d```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```rs1n```|5-bit|
|```rs2n```|5-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```rs1d```|32-bit|

### Branch Address Calculator

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```addr_mode```|1-bit|
|```branch_taken```|1-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```npc```|32-bit|
|```branch_addr```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```pc```|32-bit|
|```imm```|32-bit|
|```rs1d```|5-bit|

## Internal Connections

|IF/ID|Registers|Branch Address Calculator|
|:---:|:---:|:---:|
|```imm```||```imm```|
|```pc```||```pc```|
|```rs1n```|```rs1n```||
|```rs2n```|```rs2n```||
||```rs1d```|```rs1d```|
