# EX/MEM Latch #
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
|```data_mode```|2-bits|
|```rdn_in```|5-bits|
|```alu_out_in```|32-bits|
|```rs2n```|32-bits|
|```branch_taken_in```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|
|```rdn```|5-bits|
|```alu_out```|32-bits|
|```mem_data```|32-bits|


## Functionality
### Registers
  - 5-bit ```rdn``` register
  - 32-bit ```alu_out``` register
  - 32-bit ```mem_data``` register
  - 1-bit ```branch_taken``` register
### On posedge clk
  - ```rdn = rdn_in```
  - ```alu_out = alu_out_in```
  - ```branch_taken = branch_taken_in```
  - ```data_mode```

    |Name|Bits wide|
    |---|---|
    |```data_mode == 0```|```mem_data = sign extend rs2n[7:0]```|
    |```data_mode == 1```|```mem_data = sign extend rs2n[15:0]```|
    |```data_mode == 2```|```mem_data = rs2n```|

### Asynchronous active low reset
  - Register values reset to 0
