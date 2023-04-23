# CPU General Purpose Registers #
General Purpose registers are numbered from 0 through 31. 

Note: Register 0 always returns 0 while registers 1-31 are general-purpose 32-bit registers.

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
|```rs1n```|5-bits|
|```rs2n```|5-bits|
|```rdn```|5-bits|
|```rdd```|32-bits|
|```wbe```|1-bit|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```rs1d```|32-bits|
|```rs2d```|32-bits|

## Functionality
### Registers
  * Total of 32 32-bit registers:
    * Register 0 should always be 0
    * Registers 1 to 31 act like normal, meaning they hold 32 bits
### On posedge clk
  * rs1d outputs value in register indicated by rs1n
  * rs2d outputs value in register indicated by rs2n
  * If wbe is 1, rdn = value in rdd
### Asynchronous active low reset
  * All register values reset to 0