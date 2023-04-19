# IF/ID Latch #
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
|```clk```|1-bit|
|```rstn```|1-bit| 
|```immode```|3-bits|
|```ins```|32-bits| 
|```pc_in```|32-bits|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```imm```|32-bits|
|```pc```|32-bits|
|```rdn```|5-bit <br /> ```ins[11:7]```|
|```rs1n```|5-bit <br /> ```ins[19:15]```|
|```rs2n```|5-bits <br /> ```ins[24:20]```|


## Functionality
### Registers
  - 32-bit pc register
  - 32-bit imm register
### On posedge clk
  - ```pc = pc_in```
  - ```immode```
    |```immode```|```imm```|
    |:---:|---|
    |```immode == 0```|```imm = 32’b0```|
    |```immode == 1```|```imm = {20{ins[31]}}, ins[31:20]}```|
    |```immode == 2```|```imm = {20{ins[31]}}, ins[31: 25], ins[11:7]}```|
    |```immode == 3```|```imm = {19{ins[31]}}, ins[31], ins[7], ins[30:25], ins[11:8], 0}```|
    |```immode == 4```|```imm = {ins[31:12], 12b’0}```|
    |```immode == 5```|```imm = {11’b0, ins[31], ins[19:12], ins[20], ins[30:21], 0}```|
### Asynchronous active low reset
  - Register values reset to 0
