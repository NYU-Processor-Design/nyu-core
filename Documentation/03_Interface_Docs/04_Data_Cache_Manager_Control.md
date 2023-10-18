# Data Cache Manager Control #

## Contents
* [Modules](#modules)
  * [General Control Module](#general_control_module)
  * [Data Cache Manager](#data_cache_manager)
* [Connections](#connections)

## Modules

### General Control Module

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bit|

### Data Cache Manager

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```data_mode```|2-bit|

## Connections

|General Control Module|Data Cache Manager|
|:---|:---:|
|```dcache_en```|```dcache_en```|
|```dcache_rw```|```dcache_rw```|
|```data_mode```|```data_mode```|
