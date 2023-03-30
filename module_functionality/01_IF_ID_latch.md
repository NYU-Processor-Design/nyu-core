# IF/ID Latch #
Note: The inputs and outputs for this module should be made into an interface

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)
  * [Registers](#registers)
  * [Clk](#on-posedge-clk)
  * [Active low reset](#asynchronous-active-low-reset)

## Inputs
* CLK: 1-bit wide
* RSTN: 1-bit wide
* INS_IN: 32-bit wide
* PC_IN: 32-bit wide
* IMMODE: 3-bit wide

## Outputs
* NPC: 32-bit wide
* RDN: 5-bit wide 
  * ```INS[11:7]```
* RS1N: 5-bit wide 
  * ```INS[19:15]```
* RS2N: 5-bit wide 
  * ```INS[24:20]```
* IMM: 32-bit wide

## Functionality
* Registers
  - 32-bit PC register
  - 32-bit INS register
  - 32-bit IMM register
* On posedge clk
  - PC register set to PC_IN
  - INS register set to INS_IN
  - If IMMODE is 0 or 7, ```IMM = 32’b0```
  - If IMMODE is 1, ```IMM = {20{INS_IN[31]}}, INS_IN[31:21]}```
  - If IMMODE is 2, ```IMM = {20{INS_IN[31]}}, INS_IN[31: 25], INS_IN[11:7]}```
  - If IMMODE is 3, ```IMM = {20{INS_IN[31]}}, INS_IN[31:25], INS_IN[11:7]}```
  - If IMMODE is 4, ```IMM = {20{INS_IN[31]}}, INS_IN[31], INS_IN[7], INS_IN[30:25], INS_IN[11:8]}```
  - If IMMODE is 5, ```IMM = {INS_IN[31:12], 12b’0}```
  - If IMMODE is 6, ```IMM = {12’b0, INS_IN[31], INS_IN[19:12], INS_IN[20], INS_IN[30:21], 0}```
* Asynchronous active low reset
  - Register values reset to 0
