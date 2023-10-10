# ID Interface #
(Connects Outputs of IF/ID Latch to Inputs of ID/EX Latch)

## Contents
* [Modules](#modules)
  * [IF/ID Latch](#if/id_latch)
  * [ID/EX Latch](#id/ex_latch)
* [Connections](#connections)

## Modules

### IF/ID Latch

#### Outputs
|Input|Bits wide|
|:---|:---:|
|```imm```|32-bit|
|```pc```|32-bit|
|```rdn```|5-bit|

### ID/EX Latch

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```imm```|32-bit|
|```pc_in```|32-bit|
|```rdn_in```|5-bit|

## Connections

|IF/ID|ID/EX|
|:---|:---:|
|```imm```|```imm```|
|```pc```|```pc_in```|
|```rdn```|```rdn_in```|
