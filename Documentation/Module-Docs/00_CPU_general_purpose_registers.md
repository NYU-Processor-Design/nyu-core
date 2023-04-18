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
|```RS1N```|5-bits|
|```RS2N```|5-bits|
|```RDN```|5-bits|
|```RDD```|32-bits|
|```WBE```|1-bit|
|```RSTN```|1-bit|
|```CLK```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```RS1D```|32-bits|
|```RS2D```|32-bits|

## Functionality
### Registers
  * Total of 32 32-bit registers:
    * Register 0 should always be 0
    * Registers 1 to 31 act like normal, meaning they hold 32 bits
### On posedge clk
  * RS1D outputs value in register indicated by RS1N
  * RS2D outputs value in register indicated by RS2N
  * If WBE is 1, RDN = value in RDD
### Asynchronous active low reset
  * All register values reset to 0