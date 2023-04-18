# MEM/WB Latch #
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
|```WBS```|1-bit|
|```RDN_IN```|5-bits|
|```MRD```|32-bits|
|```ALU_OUT```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```RDD```|32-bits|
|```RDN```|5-bits|

## Functionality
### Registers
  - 32-bit ```RDD``` register
  - 5-bit ```RDN``` register
### On posedge clk
  - ```RDN = RDN_IN```
  - ```WBS```
    |Name|Bits wide|
    |---|---|
    |```WBS == 0```|```RDD = ALU_OUT```|
    |```WBS == 1```|```RDD = MRD```|
  

### Asynchronous active low reset
  - Register values reset to 0
