(Note: This document is currently incomplete)
# **I/O:**

## **Inputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```clk```|1-bit|Clock Signal|
|```rstn```|1-bit|Reset Signal|
|```ins```|32-bits|The Next 4-Byte Long Instruction|

## **Outputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```pc_en```|1-bit|Enables or disables program counter updating|
|```immode```|3-bits|Controls how the immediate value is constructed from the instruction|
|```wbe```|1-bit|Enables or disables writing to the destination register|
|```branch_occr```|2-bits|Specifies if instruction is guaranteed to branch, guaranteed to not branch, or could do either|
|```addr_mode```|1-bit|Specifies how the memory address to potentially branch to is calculated|
|```a_sel```|1-bit|Selects what input is used as the primary input to the ALU|
|```b_sel```|2-bit|Selects what input is used as the secondary input to the ALU|
|```alu_mode```|6-bits|Controls the operating mode of the ALU|
|```branch_cond```|2-bits|Specifies what condition must be satisfied for a branch to occur|
|```data_mode```|2-bits|Specifies the size of the data being stored in memory|
|```dcache_rw```|1-bit|Controls if the data cache is in read or write mode|
|```dcache_en```|1-bit|Enables the data cache to be read from or written to|
|```wbs```|3-bits|Specifies what data to store in the destination register|

### **Output Options:**
 
#### **IF Stage:**
  - **immode**
    - 0: imm = 32'b0
    - 1: imm = {20{ins[31]}}, ins[31:20]}
    - 2: imm = {20{ins[31]}}, ins[31: 25], ins[11:7]}
    - 3: imm = {19{ins[31]}}, ins[31], ins[7], ins[30:25], ins[11:8], 0}
    - 4: imm = {ins[31:12], 12b'0}
    - 5: imm = {11'b0, ins[31], ins[19:12], ins[20], ins[30:21], 0}
#### **ID Stage:**
  - **addr_mode**
    - 0: branch_addr = pc + imm
    - 1: branch_addr = imm + rs1d
  - **branch_occr**
    - 0: non-branching instruction
    - 1: always-branching instruction
    - 2: branch-condition instruction
  - **a_sel**
    - 0: a = rs1d
    - 1: a = pc
    - 3: a = 0
  - **b_sel**
    - 0: b = rs2d_in
    - 1: b = imm
    - 2: b = 4
    - 3: b = imm << 12
#### **EX Stage:**
  - **alu_mode**
    - 0x00: Addition
    - 0x01: Logical Left Shift
    - 0x02; Signed Set on Less Than
    - 0x03: Unsigned Set on Less Than
    - 0x04: Bitwise XOR
    - 0x05: Logical Right Shift
    - 0x06: Bitwise OR
    - 0x07: Bitwise AND
    - 0x20: Subtraction
    - 0x25: Arithmetic Right Shift
  - **branch_cond**
    - 0: branch_taken = 0 (non-branching instructions)
    - 1: branch_taken = |alu_out (rs1d < rs2d, rs1d != rs2d)
    - 2: branch_taken = ~|alu_out (rs1d >= rs2d, rs1d = rs2d)
    - 3: branch_taken = 1 (jal, jalr)
#### **MEM Stage:**
  - **data_mode**
    - 0: Store Byte (M[addr][7:0] = data[7:0])
    - 1: Store Half (M[addr][15:0] = data[15:0])
    - 2: Store Word (M[addr][31:0] = data[31:0])
  - **dcache_rw**
    - 0: Read
    - 1: Write
  - **dcache_en**
    - 0: Disabled
    - 1: Enabled
#### **WB Stage:**
  - **wbs**
    - 0: rdd = sign extend mrd[7:0]
    - 1: rdd = sign extend mrd[15:0]
    - 2: rdd = mrd
    - 3: rdd = alu_out
    - 4: rdd = mrd[7:0]
    - 5: rdd = mrd[15:0]
  - **wbe**
    - 0: don't update register[rdn]
    - 1: register[rdn] = rdd

# **Functionality:**

## **Registers:**
  - 32-bit ```ID_ins``` register
  - 32-bit ```EX_ins``` register
  - 32-bit ```MEM_ins``` register
  - 32-bit ```WB_ins``` register
## **Combinational Logic Signals:**
  - 1-bit ```Hazard```

## **Instruction Type Decoding:**

#### R Type (ins[6:0] = 0110011):
  - IF Stage:
    - immode = 0
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 0
    - a_sel = 0
    - b_sel = 0
  - EX Stage:
    - alu_mode = ins[31:25] + ins[14:12]
    - branch_cond = 0
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = 3
    - wbe = 1
#### I Type 1 (ins[6:0] = 0010011):
  - IF Stage:
    - immode = 1
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 0
    - a_sel = 0
    - b_sel = 1
  - EX Stage:
    - alu_mode:
       - If ins[14:12] = 0x5:
         - alu_mode = ins[31:25] + ins[14:12] 
       - Else:
         - alu_mode = ins[14:12] 
    - branch_cond = 0
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = 3
    - wbe = 1
#### I Type 2 (ins[6:0] = 0000011):
  - IF Stage:
    - immode = 1
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 0
    - a_sel = N/A
    - b_sel = N/A
  - EX Stage:
    - alu_mode = N/A
    - branch_cond = 0
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = 0
    - dcache_en = 1
  - WB Stage:
    - wbs = ins[14:12]
    - wbe = 1
#### I Type 3 (ins[6:0] = 1100111):
  - IF Stage:
    - immode = 1
  - ID Stage:
    - addr_mode = 1
    - branch_occr = 1
    - a_sel = 1
    - b_sel = 2
  - EX Stage:
    - alu_mode = 0
    - branch_cond = 3
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = 3
    - wbe = 1
#### S Type (ins[6:0] = 0100011):
  - IF Stage:
    - immode = 2
  - ID Stage:
    - addr_mode = 1
    - branch_occr = 0
    - a_sel = N/A
    - b_sel = N/A
  - EX Stage:
    - alu_mode = N/A
    - branch_cond = 0
  - MEM Stage:
    - data_mode = ins[14:12] 
    - dcache_rw = 1
    - dcache_en = 1
  - WB Stage:
    - wbs = N/A
    - wbe = 0
#### B Type (ins[6:0] = 1100011):
  - IF Stage
    - immode = 3
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 2
    - a_sel = 0
    - b_sel = 0
  - EX Stage:
    - alu_mode:
      - If ins[14:12] = 0, 1
        - alu_mode = 0x20
      - If ins[14:12] = 4, 5
        - alu_mode = 0x02
      - If ins[14:12] = 6, 7
        - alu_mode = 0x03
    - branch_cond:
      - If ins[14:12] = 1, 4, 6
        - branch_cond = 1
      - If ins[14:12] = 0, 5, 7
        - branch_cond = 2 
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = N/A
    - wbe = 0
#### U Type (ins[6:0] = 0110111, 0010111):
  - IF Stage:
    - immode = 4
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 0
    - a_sel = ins[5:4]
    - b_sel = 3
  - EX Stage:
    - alu_mode = 0
    - branch_cond = 0
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = 3
    - wbe = 1
#### J Type (ins[6:0] = 1101111):
  - IF Stage:
    - immode = 5
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 1
    - a_sel = 1
    - b_sel = 2
  - EX Stage:
    - alu_mode = 0
    - branch_cond = 3
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = 3
    - wbe = 1
#### NOP (ins[6:0] = 0000000, 0001111, 1110011):
  - IF Stage:
    - immode = 0
  - ID Stage:
    - addr_mode = N/A
    - branch_occr = 0
    - a_sel = 0
    - b_sel = 0
  - EX Stage:
    - alu_mode = 0
    - branch_cond = 0
  - MEM Stage:
    - data_mode = N/A
    - dcache_rw = N/A
    - dcache_en = 0
  - WB Stage:
    - wbs = N/A
    - wbe = 0
      
## **Hazard Detection:**

### Hazard Description:
When the ins instruction poses a read-after-write or write-after-write hazard, we need to stall that instruction until the instruction it depends on exits the pipeline. A similar rule needs to be applied for branching hazards since we could potentially load an errant instruction into the IF stage. As such, we use combinational logic to check if the instruction in the ins input is a branching instruction or otherwise dependent on any instruction currently in the other stages of the pipeline; if there is a branching instruction or dependency, the hazard signal is set and we insert a NOP to stall execution, otherwise, we continue as normal with the hazard signal not set. This hazard detection logic must be combinational and not rely on the clock cycle so that we can entirely and instantly prevent the pipeline from advancing to the next instruction for as long as the hazard is present. 

Note that we don't have to worry about write-after-read hazards since we do not reorder instructions and there is no way for a subsequent instruction to read data from either the memory or registers before the proceeding instruction can write the data.

### Instructions That Can Pose Hazards:

#### Hazards Related to CPU Registers
- All R Type Instructions: They all read and write to CPU registers
- All I Type 1 Instructions: They all read and write to CPU registers
- All I Type 2 Instructions: They all read and write to CPU registers
- All I Type 3 Instructions: They all read and write to CPU registers
- All S Type Instructions: They all read from CPU registers
- All B Type Instructions: They all read from CPU registers
- All U Type Instructions: They all write to CPU registers
- All J Type Instructions: They all write to CPU registers

#### Hazards Related to Memory
- Can't have memory hazards since all interactions with memory happen in the MEM stage so no conflicts can happen between two instructions

#### Branching Hazards
- All I Type 3 Instructions: They can all branch
- All B Type Instructions: They can all branch
- All J Type Instructions: They can all branch

### Hazard Detection Logic:

#### Detecting if IF_ins holds branch hazard
- If IF_ins[6:0] == 1100111, 1100011, 1101111, hazard = 1

#### Detecting if IF_ins holds data hazard
- Since we don't have to worry about write-after-read hazards, S and B type instructions only need to be screened for in IF_ins, not anywhere else
- If (ins[6:0] == 0110011, 0010011, 0000011, 0100011, 1100011, 1101111, 1100111, 0110111, 0010111)
and ((ID_ins[6:0] == 0110011, 0010011, 0000011, 1101111, 1100111, 0110111, 0010111 and     
ID_ins[11:7] == ins[11:7] != 0) or (EX_ins[6:0] == 0110011, 0010011, 0000011, 1101111, 
1100111, 0110111, 0010111 and EX_ins[11:7] == ins[11:7] != 0) or (MEM_ins[6:0] == 0110011, 
0010011, 0000011, 1101111, 1100111, 0110111, 0010111 and MEM_ins[11:7] == 
ins[11:7] != 0) or (WB_ins[6:0] == 0110011, 0010011, 0000011, 1101111, 1100111, 0110111, 
0010111 and WB_ins[11:7] == ins[11:7] != 0))

#### Combination Logic
- If (ins[6:0] == 1100111, 1100011, 1101111) hazard = 1
- Else if ((ins[6:0] == 0110011, 0010011, 0000011, 0100011, 1100011, 1101111, 1100111, 0110111, 0010111) and ((ID_ins[6:0] == 0110011, 0010011, 0000011, 1101111, 1100111, 0110111, 0010111 and     
ID_ins[11:7] == ins[11:7] != 0) or (EX_ins[6:0] == 0110011, 0010011, 0000011, 1101111, 
1100111, 0110111, 0010111 and EX_ins[11:7] == ins[11:7] != 0) or (MEM_ins[6:0] == 0110011, 
0010011, 0000011, 1101111, 1100111, 0110111, 0010111 and MEM_ins[11:7] == 
ins[11:7] != 0) or (WB_ins[6:0] == 0110011, 0010011, 0000011, 1101111, 1100111, 0110111, 
0010111 and WB_ins[11:7] == ins[11:7] != 0))) hazard = 1
- Else hazard = 0

### Hazard Dependent Outputs and Registers:
  - Hazard = 0:
    - ID_ins = ins
    - pc_en = 1
  - Hazard = 1:
    - ID_ins = NOP (32'b0)
    - pc_en = 0
