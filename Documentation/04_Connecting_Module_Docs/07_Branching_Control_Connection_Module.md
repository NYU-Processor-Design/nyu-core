# Branching Control Connection Module #
(Verilog module known as Con_Branch_Cont)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [Pipeline Reset Module](#pipeline_reset_module)
  * [Branch Predictor](#branch_predictor)
  * [Branch Manager](#branch_manager)
  * [Branch Evaluator](#branch_evaluator)
* [Internal Connections](#internal_connections)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```rstn_h```|1-bit|
|```branch_occr```|2-bit|
|```branch_cond```|2-bit|
|```pred_taken```|1-bit|
|```pred_pc```|32-bit|
|```pred_addr```|32-bit|
|```alu_out```|32-bit|
|```npc_in```|32-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```npc```|32-bit|
|```rstn_out```|1-bit Tri-State|
|```branch_taken```|1-bit|

## Modules

### Pipeline Reset Module

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```npc_in```|32-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```npc```|32-bit|
|```rstn_out```|1-bit Tri-State|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```npc_corr```|32-bit|
|```flush```|1-bit|

### Branch Predictor

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn_h```|1-bit|
|```branch_occr```|2-bit|
|```branch_cond```|2-bit|
|```pred_taken```|1-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```branch_taken```|1-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```act_taken```|1-bit|

### Branch Manager

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```pred_taken```|1-bit|
|```pred_pc```|32-bit|
|```pred_addr```|32-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```act_taken```|1-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```flush```|1-bit|
|```npc```|32-bit|

### Branch Evaluator

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```branch_cond```|2-bit|
|```alu_out```|32-bit|

#### Internal IO

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```act_taken```|1-bit|

## Internal Connections

|Pipeline Reset|Branch Predictor|Branch Manager|Branch Evaluator|
|:---:|:---:|:---:|:---:|
|```flush```||```flush```||
|```npc_corr```||```npc```||
||```act_taken```|```act_taken```|```act_taken```|
