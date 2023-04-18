# ID/EX Latch #
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
|```B_SEL```|1-bit|
|```Branch_Taken_IN```|1-bit|
|```IMM_IN```|32-bits|
|```PC_IN```|32-bits|
|```RDN_IN```|5-bits|
|```RS1D_IN```|32-bits|
|```RS2D_IN```|32-bits|
|```Branch_Addr_IN```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```RDN```|5-bits|
|```ALU_A```|32-bits|
|```ALU_B```|32-bits|
|```Branch_Addr```|32-bits|
|```PC```|32-bits|
|```Branch_Taken```|1-bit|

## Functionality
### Registers
  - 5-bit RDN register
  - 32-bit ALU_A register
  - 32-bit ALU_B register
  - 32-bit Branch_Addr register
  - 32-bit PC register
  - 1-bit Branch_Taken register
### On posedge clk
  - ```RDN = RDN_IN```
  - ```Branch_Taken = Branch_Taken_IN```
  - ```ALU_A = RS1D_IN```
  - ```B_SEL```

    |Name|Bits wide|
    |---|---|
    |```B_SEL == 0```|```ALU_B = RS2D_IN```|
    |```B_SEL == 1```|```ALU_B = IMM_IN```|
  - ```Branch_Addr = Branch_Addr_IN```
  - ```PC = PC_IN```
### Asynchronous active low reset
  - Register values reset to 0
