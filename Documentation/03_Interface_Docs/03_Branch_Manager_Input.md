# Branch Manager Input #

## Contents
* [Modules](#modules)
  * [ID/EX Latch](#id/ex_latch)
  * [Branch Manager](#branch_manager)'
* [Connections](#connections)

## Modules

### ID/EX Latch

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|
|```pc```|32-bit|
|```branch_addr```|32-bit|

### Branch Manager

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```pred_taken```|1-bit|
|```pred_pc```|32-bit|
|```pred_addr```|32-bit|

## Connections

|ID/EX Latch|Branch Manager|
|:---|:---:|
|```branch_taken```|```pred_taken```|
|```pc```|```pred_pc```|
|```branch_addr```|```pred_addr```|

