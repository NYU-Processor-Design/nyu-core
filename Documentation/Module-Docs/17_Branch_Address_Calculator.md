# Branch Address Calculator #

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```addr_mode```|1-bit|
|```imm```|32-bits|
|```rs1d```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_addr```|32-bits|

## Functionality
```addr_mode```
  |```addr_mode```|```branch_addr```|
  |---|---|
  |```addr_mode == 0```|```branch_addr = pc + imm```|
  |```addr_mode == 1```|```branch_addr = imm + rs1d```|
