# Branch Evaluator #


## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```ALU_OUT```|32-bits|
|```Cond```|2-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```Branch_Taken```|1-bit|

## Functionality
  |Name|Bits wide|When Used|
  |---|---|---|
  |```Cond == 0```|```Branch_Taken = 0```| Non-branching Instruction|
  |```Cond == 1```|```Branch_Taken = ALU_OUT```| ```rs1 < rs2```, ```rs1 != rs2```|
  |```Cond == 2```|```Branch_Taken = ~ ALU_OUT```| ```rs1 >= rs2```, ```rs1 = rs2```|
  |```Cond == 3```|```Branch_Taken = 1```| ```jal``` or ```jalr``` instructions|
