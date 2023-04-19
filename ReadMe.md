# NYU ProcDesign Core

The NYU ProcDesign Core will be a RISCV-32I compatible core with a 5 stage pipeline.

The repo contains the modules and test for components that make up the core design.

## Core Components

The core modules include:

- Arithmatic Logic Unit (ALU)
- [General Registers](/Documentation/Module-Docs/00_CPU_general_purpose_registers.md)
- Program Counter

## Branching Logic

The branch logic modules include:
- [Branch Evaluator](/Documentation/Module-Docs/06_Branch_Evaluator.md)
- Branch Predictor 
- Branch Address Calculator
- Branch Manager

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
- Processor State Module
- [General Control Module](/Documentation/Module-Docs/05_General_Control_Module.md)
- Hazard Detection

## Cache

Cache Modules:
- Instruction Cache Manager
- Data Cache Manager
- L1 Instruction Cache
- L1 Data Cache
- L2 Data Cache
- L3 Data Cache


## Current Draft of CPU Diagram

![cpu](https://user-images.githubusercontent.com/114675487/233169910-1430ea5e-cd6b-414c-972b-b1a268fcb4f2.png)


## Further Reading

[Offical RISCV Instruction Set Documentation](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)

