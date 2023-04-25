# NYU ProcDesign Core

The NYU ProcDesign Core will be a RISCV-32I compatible core with a 5 stage pipeline.

The repo contains the modules and test for components that make up the core design.

## Core Components

The core modules include:

- [Arithmatic Logic Unit (ALU)](/Documentation/Module-Docs/09_ALU.md)
- [General Registers](/Documentation/Module-Docs/00_CPU_general_purpose_registers.md)
- [Program Counter](/Documentation/Module-Docs/15_Program_Counter.md)

## Branching Logic

The branch logic modules include:
- [Branch Evaluator](/Documentation/Module-Docs/06_Branch_Evaluator.md)
- [Branch Predictor](/Documentation/Module-Docs/16_Branch_Predictor.md)
- [Branch Address Calculator](/Documentation/Module-Docs/17_Branch_Address_Calculator.md)
- [Branch Manager](/Documentation/Module-Docs/18_Branch_Manager.md)

## Pipeline

The pipeline will have 5 stages:
- Instruction Fetch (IF)
- Instuction Decode (ID)
- Execution (EX)
- Memory Access (MEM)
- Write Back (WB)

The pipeline will require 4 latch modules:
- [IF/ID Latch](/Documentation/Module-Docs/01_IF_ID_latch.md)
- [ID/EX Latch](/Documentation/Module-Docs/02_ID_EX_Latch.md)
- [EX/MEM Latch](/Documentation/Module-Docs/03_EX_MEM_Latch.md)
- [MEM/WB Latch](/Documentation/Module-Docs/04_MEM_WB_Latch.md)

## General Control and Hazards

Control Modules:
- [Processor State Module](/Documentation/Module-Docs/08_Processor_State.md)
- [General Control Module](/Documentation/Module-Docs/05_General_Control_Module.md)
- [Hazard Detection](/Documentation/Module-Docs/07_Hazard_Detection.md)

## Cache

Cache Modules:
- [Instruction Cache Manager](/Documentation/Module-Docs/13_Instruction_Cache_Manager.md)
- [L1 Instruction Cache](/Documentation/Module-Docs/14_L1_Instruction_Cache.md)
- Data Cache Manager
- [L1 Data Cache](/Documentation/Module-Docs/10_L1_Data_Cache.md)
- [L2 Data Cache](/Documentation/Module-Docs/11_L2_Data_Cache.md)
- [L3 Data Cache](/Documentation/Module-Docs/12_L3_Data_Cache.md)


## Current Draft of CPU Diagram

![pipeline](https://user-images.githubusercontent.com/114675487/234124513-e89020ff-c2d0-41ae-972d-e6e19ff28416.png)


## Further Reading

[Offical RISCV Instruction Set Documentation](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)

