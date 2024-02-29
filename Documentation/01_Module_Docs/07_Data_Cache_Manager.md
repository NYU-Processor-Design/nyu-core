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

## Outputs
|Name|Bits wide|
|:---|:---:|
|```write_enable```|1-bit|
|```read_enable```|1-bit|

## Functionality
  - ```write_enable``` = ```dcache_en``` & ```dcache_rw```
  - ```read_enable``` = ```dcache_en``` & ~```dcache_rw```