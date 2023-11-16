# THIS OUTLINE IS NOT YET COMPLETE #

# General Control Module #
Note: The inputs and outputs for this module should be made into an interface

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
|```rstn```|1-bit|
|```ins```|32-bits|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```pc_en```|1-bit|
|```immode```|3-bits|
|```wbe```|1-bit|
|```addr_mode```|1-bit|
|```branch_occr```|2-bits|
|```a_sel```|2-bit|
|```b_sel```|2-bit|
|```alu_mode```|6-bits|
|```branch_cond```|2-bits|
|```data_mode```|2-bits|
|```dcache_rw```|1-bit|
|```dcache_en```|1-bit|
|```wbs```|3-bits|

## Functionality
### Registers
  - 32-bit ```IF_ins``` register
  - 32-bit ```ID_ins``` register
  - 32-bit ```EX_ins``` register
  - 32-bit ```MEM_ins``` register
  - 32-bit ```WB_ins``` register
### On posedge clk

#### Instruction Control Signals
- Instruction Opcodes
    |Type|Opcode|
    |---|---|
    |R|0110011|
    |I1|0010011|
    |I2|0000011|
    |I3|1100111|
    |S|0100011|
    |B|1100011|
    |U|0110111, 0010111|
    |J|1101111|
    |NOP|0000000, 0001111, 1110011|
- ```IF_ins[6:0]```
    |```IF_ins[6:0]```|```pc_en```|```immode```|
    |---|---|---|
    |```IF_ins[6:0]``` == R|```pc_en``` = 1|```immode``` = 0|
    |```IF_ins[6:0]``` == I1|```pc_en``` = 1|```immode``` = 1|
    |```IF_ins[6:0]``` == I2|```pc_en``` = 1|```immode``` = 1|
    |```IF_ins[6:0]``` == I3|```pc_en``` = 1|```immode``` = 1|
    |```IF_ins[6:0]``` == S|```pc_en``` = 1|```immode``` = 2|
    |```IF_ins[6:0]``` == B|```pc_en``` = 1|```immode``` = 3|
    |```IF_ins[6:0]``` == U|```pc_en``` = 1|```immode``` = 4|
    |```IF_ins[6:0]``` == J|```pc_en``` = 1|```immode``` = 5|
    |```IF_ins[6:0]``` == NOP|```pc_en``` = 0|```immode``` = 0|
- ```ID_ins[6:0]```
    |```ID_ins[6:0]```|```addr_mode```|```branch_occr```|```a_sel```|```b_sel```|
    |---|---|---|---|---|
    |```ID_ins[6:0]``` == R|```addr_mode``` = 0|```branch_occr``` = 0|```a_sel``` = 0|```b_sel``` = 0|
    |```ID_ins[6:0]``` == I1|```addr_mode``` = 0|```branch_occr``` = 0|```a_sel``` = 0|```b_sel``` = 1|
    |```ID_ins[6:0]``` == I2|```addr_mode``` = 0|```branch_occr``` = 0|```a_sel``` = 0|```b_sel``` = 0|
    |```ID_ins[6:0]``` == I3|```addr_mode``` = 1|```branch_occr``` = 1|```a_sel``` = 1|```b_sel``` = 2|
    |```ID_ins[6:0]``` == S|```addr_mode``` = 1|```branch_occr``` = 0|```a_sel``` = 0|```b_sel``` = 0|
    |```ID_ins[6:0]``` == B|```addr_mode``` = 0|```branch_occr``` = 2|```a_sel``` = 0|```b_sel``` = 0|
    |```ID_ins[6:0]``` == U|```addr_mode``` = 0|```branch_occr``` = 0|```a_sel``` = ```ID_ins[5:4]```|```b_sel``` = 3|
    |```ID_ins[6:0]``` == J|```addr_mode``` = 0|```branch_occr``` = 1|```a_sel``` = 1|```b_sel``` = 2|
    |```ID_ins[6:0]``` == NOP|```addr_mode``` = 0|```branch_occr``` = 0|```a_sel``` = 0|```b_sel``` = 0|
- ```EX_ins[6:0]```
    |```EX_ins[6:0]```|```alu_mode```|```branch_cond```|
    |---|---|---|
    |```EX_ins[6:0]``` == R|```alu_mode``` = ```EX_ins[31:25]``` + ```EX_ins[14:12]```|```branch_cond``` = 0|
    |```EX_ins[6:0]``` == I1|```alu_mode``` = ```EX_ins[31:25]``` + ```EX_ins[14:12]``` if ```EX_ins[14:12]``` == 0x5, ```alu_mode``` = ```EX_ins[14:12]```|```branch_cond``` = 0 otherwise|
    |```EX_ins[6:0]``` == I2|```alu_mode``` = 0|```branch_cond``` = 0|
    |```EX_ins[6:0]``` == I3|```alu_mode``` = 0|```branch_cond``` = 3|
    |```EX_ins[6:0]``` == S|```alu_mode``` = 0|```branch_cond``` = 0|
    |```EX_ins[6:0]``` == B|```alu_mode``` = 0x02 if ```EX_ins[14:12]``` == 4 or 5, ```alu_mode``` = 0x03 if ```EX_ins[14:12]``` == 6 or 7, ```alu_mode``` = 0x20 otherwise |```branch_cond``` = 1 if ```EX_ins[14:12]``` == 1 or 4 or 6,  ```branch_cond``` = 2| otherwise
    |```EX_ins[6:0]``` == U|```alu_mode``` = 0|```branch_cond``` = 0|
    |```EX_ins[6:0]``` == J|```alu_mode``` = 0|```branch_cond``` = 3|
    |```EX_ins[6:0]``` == NOP|```alu_mode``` = 0|```branch_cond``` = 0|
- ```MEM_ins[6:0]```
    |```MEM_ins[6:0]```|```data_mode```|```dcache_rw```|```dcache_en```|
    |---|---|---|---|
    |```MEM_ins[6:0]``` == R|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
    |```MEM_ins[6:0]``` == I1|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
    |```MEM_ins[6:0]``` == I2|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 1|
    |```MEM_ins[6:0]``` == I3|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
    |```MEM_ins[6:0]``` == S|```data_mode``` = ```MEM_ins[14:12]```|```dcache_rw``` = 1|```dcache_en``` = 1|
    |```MEM_ins[6:0]``` == B|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
    |```MEM_ins[6:0]``` == U|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
    |```MEM_ins[6:0]``` == J|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
    |```MEM_ins[6:0]``` == NOP|```data_mode``` = 0|```dcache_rw``` = 0|```dcache_en``` = 0|
- ```WB_ins[6:0]```
    |```WB_ins[6:0]```|```wbs```|```wbe```|
    |---|---|---|
    |```WB_ins[6:0]``` == R|```wbs``` = 3|```wbe``` = 1|
    |```WB_ins[6:0]``` == I1|```wbs``` = 3|```wbe``` = 1|
    |```WB_ins[6:0]``` == I2|```wbs``` = ```WB_ins[14:12]```|```wbe``` = 1|
    |```WB_ins[6:0]``` == I3|```wbs``` = 3|```wbe``` = 1|
    |```WB_ins[6:0]``` == S|```wbs``` = 0|```wbe``` = 0|
    |```WB_ins[6:0]``` == B|```wbs``` = 0|```wbe``` = 0|
    |```WB_ins[6:0]``` == U|```wbs``` = 3|```wbe``` = 1|
    |```WB_ins[6:0]``` == J|```wbs``` = 3|```wbe``` = 1|
    |```WB_ins[6:0]``` == NOP|```wbs``` = 0|```wbe``` = 0|


### Asynchronous active low reset
  - Register values reset to 0
