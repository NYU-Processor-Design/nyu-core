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
|```CLK```|1-bit|
|```RSTN```|1-bit| 
|```INS_IN```|32-bits| 
|```PC_IN```|32-bits|
|```IMMODE```|3-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```NPC```|32-bits|
|```RDN```|5-bit <br /> ```INS[11:7]```|
|```RS1N```|5-bit <br /> ```INS[19:15]```|
|```RS2N```|5-bits <br /> ```INS[24:20]```|
|```IMM```|32-bits|

## Functionality
### Registers
  - 32-bit PC register
  - 32-bit INS register
  - 32-bit IMM register
### On posedge clk
  - ```PC = PC_IN```
  - ```INS = INS_IN```
  - ```IMMODE```
    |```IMMODE```|```IMM```|
    |:---:|---|
    |```IMMODE == 0``` <br /> or <br /> ```IMMODE == 7```|```IMM = 32’b0```|
    |```IMMODE == 1```|```IMM = {20{INS_IN[31]}}, INS_IN[31:21]}```|
    |```IMMODE == 2```|```IMM = {20{INS_IN[31]}}, INS_IN[31: 25], INS_IN[11:7]}```|
    |```IMMODE == 3```|```IMM = {20{INS_IN[31]}}, INS_IN[31:25], INS_IN[11:7]}```|
    |```IMMODE == 4```|```IMM = {20{INS_IN[31]}}, INS_IN[31], INS_IN[7], INS_IN[30:25], INS_IN[11:8]}```|
    |```IMMODE == 5```|```IMM = {INS_IN[31:12], 12b’0}```|
    |```IMMODE == 6```|```IMM = {12’b0, INS_IN[31], INS_IN[19:12], INS_IN[20], INS_IN[30:21], 0}```|
### Asynchronous active low reset
  - Register values reset to 0
