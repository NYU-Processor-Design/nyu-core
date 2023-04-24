# Program Counter #

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
|```npc```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```pc```|32-bits|

## Functionality
### Registers
  - 32-bit ```pc``` register
### On posedge clk
  - ```pc = npc```
### Asynchronous active low reset
  - ```pc``` value resets to 0
