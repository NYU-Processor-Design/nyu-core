# THIS OUTLINE IS NOT YET COMPLETE #
# Branch Manager #

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)
  * [Registers](#registers)
  * [Combinational](#combinational)
  * [Clk](#on-posedge-clk)
  * [Active low reset](#asynchronous-active-low-reset)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```clk```|1-bit|
|```rstn```|1-bit|
|```pred_taken```|1-bit|
|```pred_pc```|32-bits|
|```pred_addr```|32-bits|
|```act_taken```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```flush```|1-bit|
|```npc```|32-bits|

## Functionality
### Registers
  - 32-bits ```curr_ins_addr``` register
  - 32-bits ```curr_ins_pc``` register
  - 1-bit ```curr_ins_pred``` register
  - 1-bit ```restart``` register
### Combintational
  - If ```(curr_ins_pred != act_taken)&&(!restart)```
    * ```flush = 1```
    * ```act_taken```
      |```act_taken```|```npc```|
      |:---|:---:|
      |```act_taken == 0```|```npc = curr_ins_pc + 4```|
      |```act_taken == 1```|```npc = curr_ins_addr```|
  - Else
    * ```flush = 0```
    * ```pred_taken```
      |```pred_taken```|```npc```|
      |:---|:---:|
      |```pred_taken == 0```|```npc = pred_pc + 4```|
      |```pred_taken == 1```|```npc = pred_addr```|
### On posedge clk
  - ```curr_ins_addr = pred_addr```
  - ```curr_ins_pc = pred_pc```
  - ```curr_ins_pred = pred_taken```
  - If ```restart```, ```restart = 0```

### Asynchronous active low reset
  - ```restart``` set to 1
  - All other registers set to 0
