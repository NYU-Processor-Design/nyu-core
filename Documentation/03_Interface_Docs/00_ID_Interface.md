# ID Interface #
(Connects Outputs of IF/ID Latch to Inputs of ID/EX Latch and Branch Address Calculator)

## Contents
* [Modules](#modules)
  * [IF/ID Latch](#if/id_latch)
  * [ID/EX Latch](#id/ex_latch)
  * [Branch Address Calculator](#branch_address_calculator)
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

### Branch Address Calculator

#### Inputs
|Input|Bits wide|
|:---|:---:|
|```imm```|32-bit|
|```pc```|32-bit|

## Connections

|IF/ID|ID/EX|Branch Address Calculator|
|:---|:---:|:---:|
|```imm```|```imm```|```imm```|
|```pc```|```pc_in```|```pc```|
|```rdn```|```rdn_in```|
