# General Control Module #

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
### Register
  - 32-bit ```ID_ins``` register
  - 32-bit ```EX_ins``` register
  - 32-bit ```MEM_ins``` register
  - 32-bit ```WB_ins``` register

### **Combinational Logic Signals**
  - 1-bit ```hazard```
    
### Combinational Logic

#### Instruction Opcodes

|Type|Opcode|
|---|---|
|R|0b0110011|
|I1|0b0010011|
|I2|0b0000011|
|I3|0b1100111|
|S|0b0100011|
|B|0b1100011|
|U|0b0110111, 0b0010111|
|J|0b1101111|
|NOP|0b0000000, 0b0001111, 0b1110011|
  
#### Instruction Decode
- ```ins[6:0]```
    |```ins[6:0]```|```immode```|
    |---|---|
    |```ins[6:0]``` == R|```immode``` = 0|
    |```ins[6:0]``` == I1|```immode``` = 1|
    |```ins[6:0]``` == I2|```immode``` = 1|
    |```ins[6:0]``` == I3|```immode``` = 1|
    |```ins[6:0]``` == S|```immode``` = 2|
    |```ins[6:0]``` == B|```immode``` = 3|
    |```ins[6:0]``` == U|```immode``` = 4|
    |```ins[6:0]``` == J|```immode``` = 5|
    |```ins[6:0]``` == NOP|```immode``` = 0|
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

#### Hazard Detection
- ```pc_en``` = ~```hazard```
- If (```ins[6:0]``` == I3, B, J) and (```hazard``` == 0)
     - ```hazard``` = 1
- Else if ```ins[6:0]``` == R, I1, I2, I3, S, B, U, J
     - If (```ID_ins[6:0]``` == R, I1, I2, I3, U, J) and ((```ID_ins[11:7]``` == ```ins[11:7]```) or (```ID_ins[11:7]``` == ```ins[24:20]```) or (```ID_ins[11:7]``` == ```ins[19:15]```))and (```ID_ins[11:7]``` != 0)
          - ```hazard``` = 1
     - If (```EX_ins[6:0]``` == R, I1, I2, I3, U, J) and ((```EX_ins[11:7]``` == ```ins[11:7]```) or (```EX_ins[11:7]``` == ```ins[24:20]```) or (```EX_ins[11:7]``` == ```ins[19:15]```))and (```EX_ins[11:7]``` != 0)
          - ```hazard``` = 1
     - If (```MEM_ins[6:0]``` == R, I1, I2, I3, U, J) and ((```MEM_ins[11:7]``` == ```ins[11:7]```) or (```MEM_ins[11:7]``` == ```ins[24:20]```) or (```MEM_ins[11:7]``` == ```ins[19:15]```))and (```MEM_ins[11:7]``` != 0)
          - ```hazard``` = 1
     - If (```WB_ins[6:0]``` == R, I1, I2, I3, U, J) and ((```WB_ins[11:7]``` == ```ins[11:7]```) or (```WB_ins[11:7]``` == ```ins[24:20]```) or (```WB_ins[11:7]``` == ```ins[19:15]```))and (```WB_ins[11:7]``` != 0)
          - ```hazard``` = 1
- Else
     - ```hazard``` = 0

### On posedge clk
- ```hazard```
   - if ```hazard```
        - ```ID_ins``` = 0
        - ```EX_ins``` = ```ID_ins```
        - ```MEM_ins``` = ```EX_ins```
        - ```WB_ins``` = ```MEM_ins```
   - else
        - ```ID_ins``` = ```ins```
        - ```EX_ins``` = ```ID_ins```
        - ```MEM_ins``` = ```EX_ins```
        - ```WB_ins``` = ```MEM_ins```
    
### Asynchronous active low reset
  - Register values reset to 0
