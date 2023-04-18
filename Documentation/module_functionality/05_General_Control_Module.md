# THIS MODULE IS NOT YET OUTLINED #

# General Control Module #
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
|```name```|#-bit|
|```name```|#-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```name```|#-bit|
|```name```|#-bit|

## Functionality
### Registers
  - #-bit ```name``` register
  - #-bit ```name``` register
### On posedge clk
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |Name|Bits wide|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
  

### Asynchronous active low reset
  - Register values reset to 0
