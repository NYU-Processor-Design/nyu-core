# Pipeline Reset Module #

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```npc_in```|32-bit|
|```npc_corr```|32-bit|
|```flush```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```rstn_out```|1-bit Tri-State|
|```npc```|32-bit|

## Functionality
* ```npc```
  |```flush```|```npc```|
  |---|---|
  |```flush == 0```|```npc = npc_in```|
  |```flush == 1```|```npc = npc_corr```|

* ```rstn_out```
  |```flush```|```rstn_out```|
  |---|---|
  |```flush == 0```|```rstn_out = Z```|
  |```flush == 1```|```rstn_out = 0```|
