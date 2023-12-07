# THIS OUTLINE IS NOT YET COMPLETE #

# Instruction Cache Manager #
(Any Notes would go here)

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
|```cache_clk```|1-bit|
|```rstn```|1-bit|
|```pc```|32-bits|
|```ins_in```|32-bits|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```ins_out```|32-bits|

### Registers
  - 32-bit ```pc``` register
  - 32-bit ```ins_in``` register
  - 32-bit ```ins_out``` register

### On posedge cache_clk
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |Name|Bits wide|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
