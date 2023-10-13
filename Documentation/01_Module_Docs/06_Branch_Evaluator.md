# Branch Evaluator #


## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```branch_cond```|2-bits|
|```alu_out```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|

## Functionality
  |Name|Bits wide|When Used|
  |---|---|---|
  |```branch_cond == 0```|```branch_taken = 0```| Non-branching Instruction|
  |```branch_cond == 1```|```branch_taken = |alu_out```| ```rs1 < rs2```, ```rs1 != rs2```|
  |```branch_cond == 2```|```branch_taken = ~|alu_out```| ```rs1 >= rs2```, ```rs1 = rs2```|
  |```branch_cond == 3```|```branch_taken = 1```| ```jal``` or ```jalr``` instructions|
