# Branch Predictor #

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
|```rstn_h```|1-bit|
|```branch_occr```|2-bits|
|```act_taken```|1-bit|
|```pred_taken```|1-bit|
|```branch_cond```|2-bits|


## Outputs
|Name|Bits wide|
|:---|:---:|
|```branch_taken```|1-bit|

## Functionality
### Registers
  - 1-bit ```curr_pred``` register
  - 1-bit ```incorrect_pred``` register
### Combinational
  - ```branch_occr```
    |```branch_occr```|```reg```|
    |---|---|
    |```branch_occr[1] == 0```|```branch_taken = branch_occr[0]```|
    |```branch_occr[1] == 1```|```branch_taken = curr_pred```|
### On posedge clk
  - Use a table when necessary if statements are used:
  - ```branch_cond```, ```pred_taken```, ```act_taken```
    |```condition```|```curr_pred```|```incorrect_pred```|
    |---|---|---|
    |^```branch_cond``` == 0|```curr_pred``` = ```curr_pred```|```incorrect_pred``` = ```incorrect_pred```|
    |(^```branch_cond``` == 1) & (```act_taken```^```pred_taken``` == 0)|```curr_pred``` = ```curr_pred```|```incorrect_pred``` = 0|
     |(^```branch_cond``` == 1) & (```act_taken```^```pred_taken``` == 1) & (```incorrect_pred``` == 1|```curr_pred``` = ~```curr_pred```|```incorrect_pred``` = 1|
    |(^```branch_cond``` == 1) & (```act_taken```^```pred_taken``` == 1) & (```incorrect_pred``` == 0)|```curr_pred``` = ```curr_pred```|```incorrect_pred``` = 1|

### Asynchronous active low reset on rstn_h
  - Register values reset to 0
