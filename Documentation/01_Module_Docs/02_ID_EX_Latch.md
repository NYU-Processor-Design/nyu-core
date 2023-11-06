# ID/EX Latch #

## Contents
- [ID/EX Latch](#idex-latch)
  - [Contents](#contents)
  - [Inputs](#inputs)
  - [Outputs](#outputs)
  - [Functionality](#functionality)
    - [Registers](#registers)
    - [On posedge clk](#on-posedge-clk)
    - [Asynchronous active low reset](#asynchronous-active-low-reset)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```a_sel```|2-bit|
|```b_sel```|2-bit|
|```branch_taken_in```|1-bit|
|```imm```|32-bits|
|```pc_in```|32-bits|
|```rdn_in```|5-bits|
|```rs1d```|32-bits|
|```rs2d_in```|32-bits|
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
|```rs2d```|32-bits|




## Functionality
### Registers
  - 5-bit rdn register
  - 32-bit a register
  - 32-bit b register
  - 32-bit branch_addr register
  - 32-bit pc register
  - 32-bit rs2d register
  - 1-bit branch_taken register
### On posedge clk
  - ```rdn = rdn_in```
  - ```branch_taken = branch_taken_in```
  - ```rs2d = rs2d_in```
  - ```branch_addr = branch_addr_in```
  - ```pc = pc_in```
  - ```a```

    |State|Output|
    |---|---|
    |```a_sel == 0```|```a = rs1d```|
    |```a_sel == 1```|```a = pc_in```|
    |```a_sel == 3```|```a = 0```|
  - ```b```

    |State|Output|
    |---|---|
    |```b_sel == 0```|```b = rs2d_in```|
    |```b_sel == 1```|```b = imm```|
    |```b_sel == 2```|```b = 4```|
    |```b_sel == 3```|```b = imm << 12```|

### Asynchronous active low reset
  - Register values reset to 0
