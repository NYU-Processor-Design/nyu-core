# Data Cache Manager Control #

## Contents
* [Modules](#modules)
  * [General Control Module](#general_control_module)
  * [MEM Connection Module](#mem_connection_module)
* [Connections](#connections)

## Modules

### General Control Module

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bit|

### MEM Connection Module

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bit|

## Connections

|General Control Module|MEM_Connection_Module|
|:---|:---:|
|```dcache_en```|```dcache_en```|
|```dcache_rw```|```dcache_rw```|
|```data_mode```|```data_mode```|
