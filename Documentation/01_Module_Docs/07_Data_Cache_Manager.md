# THIS OUTLINE IS NOT YET COMPLETE #

# Data Cache Manager #
(Any Notes would go here)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bits|
|```addr```|32-bits|
|```data```|32-bits|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```mrd```|32-bits|

## Functionality
### Combinational
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |Name|Bits wide|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
 
