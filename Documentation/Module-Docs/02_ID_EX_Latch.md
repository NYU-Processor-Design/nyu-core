# ID/EX Latch #
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
|```b_sel```|1-bit|
|```nranch_taken_in```|1-bit|
|```imm```|32-bits|
|```pc_in```|32-bits|
|```rdn_in```|5-bits|
|```rs1d```|32-bits|
|```rs2d```|32-bits|
|```branch_addr_in```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|
|```pc```|32-bits|
|```branch_addr```|32-bits|
|```rdn```|5-bits|
|```a```|32-bits|
|```b```|32-bits|




## Functionality
### Registers
  - 5-bit ```rdn``` register
  - 32-bit ```a``` register
  - 32-bit ```b``` register
  - 32-bit ```branch_addr``` register
  - 32-bit ```pc``` register
  - 1-bit ```branch_taken``` register
### On posedge clk
  - ```rdn = rdn_in```
  - ```branch_taken = branch_taken_in```
  - ```a = rs1d```
  - ```branch_addr = branch_addr_in```
  - ```pc = pc_in```
  - ```b_sel```

    |```b_sel```|```b```|
    |---|---|
    |```b_sel == 0```|```b = rs2d```|
    |```b_sel == 1```|```b = imm```|

### Asynchronous active low reset
  - Register values reset to 0
