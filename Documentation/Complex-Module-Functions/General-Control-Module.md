(Note: This document is currently incomplete)
# **I/O:**

**Inputs:**

-

**Outputs:**

-

# **Output Options:**

- **immode (IF Stage)**
  - 0: imm = 32'b0
  - 1: imm = {20{ins[31]}}, ins[31:20]}
  - 2: imm = {20{ins[31]}}, ins[31: 25], ins[11:7]}
  - 3: imm = {19{ins[31]}}, ins[31], ins[7], ins[30:25], ins[11:8], 0}
  - 4: imm = {ins[31:12], 12b'0}
  - 5: imm = {11'b0, ins[31], ins[19:12], ins[20], ins[30:21], 0}
- **wbe (ID Stage)**
  - 0: don't update rdn
  - 1: rdn = rdd
- **addr\_mode (ID Stage)**
  - 0: branch\_addr = pc + imm
  - 1: branch\_addr = imm + rs1d
- **b\_sel (ID Stage)**
  - 0: b = rs2d\_in
  - 1: b = imm
- **alu\_mode (EX Stage)**
  -
- **branch\_cond (EX Stage)**
  - 0: branch\_taken = 0 (non-branching instructions)
  - 1: branch\_taken = alu\_out (rs1 \< rs2, rs1 != rs2)
  - 2: branch\_taken = ~alu\_out (rs1 \>= rs2, rs1 = rs2)
  - 3: branch\_taken = 1 (jal, jalr)
- **data\_mode (MEM Stage)**
  -
- **dcache\_rw (MEM Stage)**
  -
- **dcache\_en (MEM Stage)**
  -
- **wbs (MEM Stage)**
  - 0: rdd = alu\_out
  - 1: rdd = sign extend mrd[7:0]
  - 2: rdd = sign extend mrd[15:0]
  - 3: rdd = mrd[7:0]
  - 4: rdd = mrd[15:0]
  - 5: rdd = mrd

# **Functionality:**

**Instruction Type Decoding:**

- R Type:
  - ins[6:0] = 0b0110011
  - alu_mode = ins[31:25] + ins[14:12]
  -

