# THIS CONNECTION MODULE IS NOT YET OUTLINED #

# Top Level Module #

## Contents
* [Inputs](#inputs)
* [Parameters](#parameters)
* [Modules](#modules)
  * [General Cpntrol Module](#general_control_module)
  * [IF Connection Module](#if_connection_module)
  * [ID Connection Module](#id_connection_module)
  * [EX Connection Module](#ex_connection_module)
  * [MEM Connection Module](#mem_connection_module)
  * [Branching Control Module](#branching_control_module)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```cache_clk```|1-bit|
|```rstn_h```|1-bit|

## Parameters 
|Name|Bits wide|Logic|
|:---|:---:|:---:|
|```rstn```|1-bit|If ```rstn_h``` == 0, ```rstn``` = 0|

## Modules

### General Control Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```rstn```|1-bit|
|```ins```|32-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```pc_en```|1-bit|
|```immode```|3-bits|
|```wbe```|1-bit|
|```addr_mode```|1-bit|
|```branch_occr```|2-bits|
|```a_sel```|2-bit|
|```b_sel```|2-bit|
|```alu_mode```|6-bits|
|```branch_cond```|2-bits|
|```data_mode```|2-bits|
|```dcache_rw```|1-bit|
|```dcache_en```|1-bit|
|```wbs```|3-bits|

### IF Connection Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```cache_clk```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```rstn```|1-bit|
|```pc_en```|1-bit|
|```npc```|32-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```pc```|32-bit|
|```ina```|32-bit|

### ID Connection Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```cache_clk```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```rstn```|1-bit|
|```immode```|3-bit|
|```ins```|32-bit|
|```pc_in```|32-bit|
|```wbe```|1-bit|
|```addr_mode```|1-bit|
|```branch_taken```|1-bit|
|```rdd```|32-bit|
|```rdn_in```|5-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```imm```|32-bit|
|```pc```|32-bit|
|```rdn```|5-bit|
|```rs1d```|32-bit|
|```rs2d```|32-bit|
|```npc```|32-bit|
|```branch_addr```|32-bit|

### EX Connection Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
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

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```branch_taken```|1-bit|
|```pc```|32-bit|
|```branch_addr```|32-bit|
|```rdn```|5-bit|
|```rs2d```|32-bit|
|```alu_out```|32-bit|

### MEM Connection Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```cache_clk```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```rstn```|1-bit|
|```rdn_in```|5-bits|
|```alu_out_in```|32-bits|
|```rs2d```|32-bits|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bits|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```rdn```|5-bits|
|```alu_out```|32-bits|
|```mrd```|32-bits|

### Branching Control Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn_h```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```rstn```|1-bit|
|```branch_occr```|2-bit|
|```branch_cond```|2-bit|
|```pred_taken```|1-bit|
|```pred_pc```|32-bit|
|```pred_addr```|32-bit|
|```alu_out```|32-bit|
|```npc_in```|32-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```npc```|32-bit|
|```rstn_out```|1-bit Tri-State|
|```branch_taken```|1-bit|

## Internal Connections

|Module 1|Module 2|Module N|
|:---:|:---:|:---:|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
|```name```|```name```|```name```|

