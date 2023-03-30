# CPU General Purpose Registers

General Purpose registers are numbered from 0 through 31. Note that Register 0 always returns 0 while registers 1-31 are general-purpose 32-bit registers.

## Input
* RS1N: 5-bit wide
* RS2N: 5-bit wide
* RDN: 5-bit wide
* RDD 32-bit wide
* WBE: 1-bit wide
* RSTN: 1-bit wide
* CLK: 1-bit wide

## Output
  * RS1D: 32-bit wide
  * RS2D: 32-bit wide

## Functionality

* ### Registers
  * A total of 32 32-bit registers
  * Register 0 should always be 0
  * Registers 1 to 31 act like normal, meaning they hold 32 bits
* ### On posedge clk
  * RS1D outputs value in register indicated by RS1N
  * RS2D outputs value in register indicated by RS2N
  * If WBE is 1, register indicated by RDN is set to value of RDD
* ### Asynchronous active low reset
  * All register values reset to 0
