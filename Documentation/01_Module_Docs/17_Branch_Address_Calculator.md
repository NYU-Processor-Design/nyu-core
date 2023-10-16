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
|```branch_taken```|1-bit|
|```pc```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_addr```|32-bits|
|```npc```|32-bits|

## Functionality
```branch_addr```
  |```addr_mode```|```branch_addr```|
  |---|---|
  |```addr_mode == 0```|```branch_addr = pc + imm```|
  |```addr_mode == 1```|```branch_addr = imm + rs1d```|

```npc```
  |```branch_taken```|```npc```|
  |---|---|
  |```branch_taken == 0```|```npc = pc + 4```|
  |```branch_taken = 1```|```npc = branch_addr```|
  
