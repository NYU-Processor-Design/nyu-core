# MEM/WB Latch #
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
|```clk```|1-bit|
|```rstn```|1-bit|
|```wbs```|3-bits|
|```rdn_in```|5-bits|
|```alu_out```|32-bits|
|```mrd```|32-bits|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```rdn```|5-bits|
|```rdd```|32-bits|

## Functionality
### Registers
  - 32-bit ```rdd``` register
  - 5-bit ```rdn``` register
### On posedge clk
  - ```rdn = rdn_in```
  - ```wbs```
    |```wbs```|```rdd```|
    |---|---|
    |```wbs == 0```|```rdd = alu_out```|
    |```wbs == 1```|```rdd = sign extend mrd[7:0]```|
    |```wbs == 2```|```rdd = sign extend mrd[15:0]```|
    |```wbs == 3```|```rdd = mrd[7:0]```|
    |```wbs == 4```|```rdd = mrd[15:0]```|
    |```wbs == 5```|```rdd = mrd```|
  

### Asynchronous active low reset
  - Register values reset to 0
