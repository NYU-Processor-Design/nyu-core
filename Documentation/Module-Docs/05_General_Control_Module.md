# THIS OUTLINE IS NOT YET COMPLETE #

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
|```clk```|1-bit|
|```rstn```|1-bit|
|```ins```|32-bits|
|```p_state```|#-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```immode```|3-bits|
|```wbe```|1-bit|
|```addr_mode```|1-bit|
|```a_sel```|1-bit|
|```b_sel```|2-bit|
|```alu_mode```|6-bits|
|```branch_cond```|2-bits|
|```data_mode```|2-bits|
|```dcache_rw```|1-bit|
|```dcache_en```|1-bit|
|```wbs```|3-bits|



## Functionality
### Registers
  - 32-bit ```IF_ins``` register
  - 32-bit ```ID_ins``` register
  - 32-bit ```EX_ins``` register
  - 32-bit ```MEM_ins``` register
  - 32-bit ```WB_ins``` register
### On posedge clk
  - ```IF_ins = ins```
  - ```ID_ins = IF_ins```
  - ```EX_ins = ID_ins```
  - ```MEM_ins = EX_ins```
  - ```WB_ins = MEM_ins```

### Asynchronous active low reset
  - Register values reset to 0
