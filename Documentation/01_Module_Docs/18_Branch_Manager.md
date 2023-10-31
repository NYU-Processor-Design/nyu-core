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
  - 1-bit ```restart``` register
### On posedge clk
  - If ```(pred_taken != act_taken)&&(!restart)```
    * ```flush = 1```
    * ```act_taken```
      |```act_taken```|```npc```|
      |:---|:---:|
      |```act_taken == 0```|```npc = pred_pc + 4```|
      |```act_taken == 1```|```npc = pred_addr```|
  - Else
    * ```flush = 0```
    * ```pred_taken```
      |```pred_taken```|```npc```|
      |:---|:---:|
      |```pred_taken == 0```|```npc = pred_pc + 4```|
      |```pred_taken == 1```|```npc = pred_addr```|
   - If ```restart```, ```restart = 0```

### Asynchronous active low reset
  - ```restart``` set to 1
