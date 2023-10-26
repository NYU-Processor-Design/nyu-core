# Flush Bus #
(Any Notes would go here)

## Contents
* [Modules](#modules)
  * [Branch Manager](#branch_manager)
  * [Pipeline Reset Module](#pipeline_reset_module)
* [Connections](#connections)

## Modules

### Branch Manager

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```npc```|32-bit|
|```flush```|1-bit|

### Pipeline Reset Module

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```npc_corr```|32-bit|
|```flush```|1-bit|

## Connections

|Branch Manager|Pipeline Reset Module|
|:---|:---:|
|```npc```|```npc_corr```|
|```flush```|```flush```|
