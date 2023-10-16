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
|```rstn```|1-bit|
|```npc```|32-bit|

## Functionality
* ```npc```
  |```flush```|```npc```|
  |---|---|
  |```flush == 0```|```npc = npc_in```|
  |```flush == 1```|```npc = npc_corr```|

* ```rstn``` = ```~flush```
