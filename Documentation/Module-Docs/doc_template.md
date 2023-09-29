USE THIS TEMPLATE AS A GUIDE TO DOCUMENT OUTLINED MODULES

# Module Name #
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
    |```name```|```reg```|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
  

### Asynchronous active low reset
  - Register values reset to 0
