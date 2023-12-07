# THIS MODULE IS NOT YET OUTLINED #

# L1 Instruction Cache #
Not sure about the index, offset, tag bit

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
|```tag_in```|17-bit|
|```index_in```|9-bit|
|```offset_in```|6-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```ins```|32-bit|

## Functionality
### Registers
  - 32-bit ```ins``` register
  - 17-bit ```tag``` register
  - 9-bit ```index``` register
  - 6-bit ```offset``` register

### On posedge clk
  - Check if hit or miss
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |Name|Bits wide|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
  

### Asynchronous active low reset
  - Register values reset to 0
