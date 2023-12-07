# THIS OUTLINE IS NOT YET COMPLETE #

# Instruction Cache Manager #
*NOTES*:
- Cache manager calculate the cache parameters (index, tag, offset) from the `pc` and pass them into the cache for instruction retrieval.


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
|```ins_in```|32-bits|
|```rstn```|1-bit|
|```pc```|32-bits|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```ins_out```|32-bits|
|```tag```|17-bit|
|```index```|9-bit|
|```offset```|6-bit|

### Registers
  - 32-bit ```pc``` register
  - 32-bit ```ins_in``` register


### On posedge cache_clk
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |Name|Bits wide|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
