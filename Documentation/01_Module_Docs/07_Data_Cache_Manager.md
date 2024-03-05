# Data Cache Manager #

## Contents
- [Data Cache Manager](#data-cache-manager)
  - [Contents](#contents)
  - [Inputs](#inputs)
  - [Outputs](#outputs)
  - [Functionality](#functionality)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```dcache_en```|1-bit|
|```dcache_rw```|1-bit|
|```mem_request```|1-bit|
|```mem_write_enable```|1-bit|
|```mem_busy```|1-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```write_enable```|1-bit|
|```read_enable```|1-bit|
|```mem_ready```|1-bit|
|```wEn```|1-bit|
|```rEn```|1-bit|
|```isBurst```|1-bit|

## Functionality
  - ```write_enable``` = ```dcache_en``` & ```dcache_rw```
  - ```read_enable``` = ```dcache_en``` & ~```dcache_rw```
  - ```isBurst``` = 0
  - ```mem_ready``` = ~```mem_busy```
  - ```wEn``` = ```mem_request``` & ```mem_write_enable```
  - ```rEn``` = ```mem_request``` & ~```mem_write_enable```