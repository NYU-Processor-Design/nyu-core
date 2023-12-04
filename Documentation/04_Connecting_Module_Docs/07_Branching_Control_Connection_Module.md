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

### Module 1

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

### Module 2

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

### Module N

#### External IO

##### External Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### External Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

#### Internal IO

##### Internal Inputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

##### Internal Outputs
|Name|Bits wide|
|:---:|:---:|
|```name```|#-bit|
|```name```|#-bit|

## Internal Connections

|Module 1|Module 2|Module N|
|:---:|:---:|:---:|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
|```name```|```name```|```name```|
