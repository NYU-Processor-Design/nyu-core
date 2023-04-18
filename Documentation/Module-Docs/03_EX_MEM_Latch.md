# EX/MEM Latch #
Note: The inputs and outputs for this module should be made into an interface

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)
  * [Registers](#registers)
  * [Clk](#on-posedge-clk)
  * [Active low reset](#asynchronous-active-low-reset)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```CLK```|1-bit|
|```RSTN```|1-bit|
|```RDN_IN```|5-bits|
|```ALU_OUT_IN```|32-bits|
|```ALU_B_IN```|32-bits|
|```Branch_Taken_IN```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```NPC```|32-bits|
|```RDN```|5-bits|
|```ALU_OUT```|32-bits|
|```ALU_B```|32-bits|
|```Branch_Taken```|1-bit|

## Functionality
### Registers
  - 32-bit ```NPC``` register
  - 5-bit ```RDN``` register
  - 32-bit ```ALU_OUT``` register
  - 32-bit ```ALU_B``` register
  - 1-bit ```Branch_Taken``` register
### On posedge clk
  - ```RDN = RDN_IN```
  - ```ALU_OUT = ALU_OUT_IN```
  - ```ALU_B = ALU_B_IN```
  - ```Branch_Taken = Branch_Taken_IN```

### Asynchronous active low reset
  - Register values reset to 0
