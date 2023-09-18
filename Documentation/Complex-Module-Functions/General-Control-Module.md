(Note: This document is currently incomplete)
# **I/O:**

**Inputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```clk```|1-bit|Clock Signal|
|```rstn```|1-bit|Reset Signal|
|```ins```|32-bits|The Next 4-Byte Long Instruction|
|```p_state```|#-bits|Input from Processor State Module|

**Outputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```immode```|3-bits|Controls how the immediate value is constructed from the instruction|
|```wbe```|1-bit|Enables or disables writing to the destination register|
|```addr_mode```|1-bit|
|```b_sel```|1-bit|
|```alu_mode```|6-bits|Controls the operating mode of the ALU|
|```branch_cond```|2-bits|
|```data_mode```|2-bits|
|```dcache_rw```|1-bit|
|```dcache_en```|1-bit|
|```wbs```|3-bits|

# **Output Options:**

- **IF Stage:**
  - **immode**
    - 0: imm = 32'b0
    - 1: imm = {20{ins[31]}}, ins[31:20]}
    - 2: imm = {20{ins[31]}}, ins[31: 25], ins[11:7]}
    - 3: imm = {19{ins[31]}}, ins[31], ins[7], ins[30:25], ins[11:8], 0}
    - 4: imm = {ins[31:12], 12b'0}
    - 5: imm = {11'b0, ins[31], ins[19:12], ins[20], ins[30:21], 0}
- **ID Stage:**
  - **addr_mode**
    - 0: branch_addr = pc + imm
    - 1: branch_addr = imm + rs1d
  - **b_sel**
    - 0: b = rs2d_in
    - 1: b = imm
- **EX Stage:**
  - **alu_mode)**
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
    - 1: branch_taken = alu_out (rs1d < rs2d, rs1d != rs2d)
    - 2: branch_taken = ~alu_out (rs1d >= rs2d, rs1d = rs2d)
    - 3: branch_taken = 1 (jal, jalr)
- **MEM Stage:**
  - **data_mode**
    - 0: Store Byte (M[addr][7:0] = data[7:0])
    - 1: Store Half (M[addr][15:0] = data[15:0])
    - 2: Store Word (M[addr][31:0] = data[31:0])
  - **dcache_rw**
   - 0:
  - **dcache_en**
    - 0:
  - **wbs**
    - 0: rdd = alu\_out
    - 1: rdd = sign extend mrd[7:0]
    - 2: rdd = sign extend mrd[15:0]
    - 3: rdd = mrd[7:0]
    - 4: rdd = mrd[15:0]
    - 5: rdd = mrd
- **WB Stage:**
  - **wbe**
    - 0: don't update register[rdn]
    - 1: register[rdn] = rdd

# **Functionality:**

**Instruction Type Decoding:**

- R Type (ins[6:0] = 0110011):
  - IF Stage:
    - immode = 0
  - ID Stage:
    - addr_mode = N/A
    - b_sel = 0
  - EX Stage:
    - alu_mode = ins[31:25] + ins[14:12]
    - branch_cond = 0
  - MEM Stage:
    - 
  - WB Stage:
    - wbe = 1

- 

