# EX Connection Module #
(Verilog module known as Con_EX)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [ID/EX Latch](#id_ex_latch)
  * [ALU](#alu)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```a_sel```|2-bit|
|```b_sel```|2-bit|
|```branch_taken_in```|1-bit|
|```imm```|32-bit|
|```pc_in```|32-bit|
|```rdn_in```|5-bit|
|```rs1d```|32-bit|
|```rs2d_in```|32-bit|
|```branch_addr_in```|32-bit|
|```alu_mode```|8-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|
|```pc```|32-bit|
|```branch_addr```|32-bit|
|```rdn```|5-bit|
|```rs2d```|32-bit|
|```alu_out```|32-bit|

## Modules

### ID/EX Latch

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```a_sel```|2-bit|
|```b_sel```|2-bit|
|```branch_taken_in```|1-bit|
|```imm```|32-bit|
|```pc_in```|32-bit|
|```rdn_in```|5-bit|
|```rs1d```|32-bit|
|```rs2d_in```|32-bit|
|```branch_addr_in```|32-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```branch_taken```|1-bit|
|```pc```|32-bit|
|```branch_addr```|32-bit|
|```rdn```|5-bit|
|```rs2d```|32-bit|

#### Internal IO

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```a```|32-bit|
|```b```|32-bit|

### ALU

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```alu_mode```|8-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```alu_out```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```a```|32-bit|
|```b```|32-bit|

## Internal Connections

|ID/EX|ALU|
|:---:|:---:|
|```a```|```a```|
|```b```|```b```|

