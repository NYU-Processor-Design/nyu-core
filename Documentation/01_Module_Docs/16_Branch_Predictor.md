# THIS OUTLINE IS NOT YET COMPLETE #

# Branch Predictor #
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
|```clk```|1-bit|
|```rstn```|1-bit|
|```branch_occr```|2-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|

## Functionality
### Registers
  - 1-bit ```name``` register
### On posedge clk
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |```name```|```reg```|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
  

### Asynchronous active low reset
  - Register values reset to 0z
