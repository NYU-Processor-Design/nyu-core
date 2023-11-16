# NYU ProcDesign Core

[![github](https://github.com/NYU-Processor-Design/nyu-core/actions/workflows/main.yaml/badge.svg)](https://github.com/NYU-Processor-Design/nyu-core/actions) 
[![codecov](https://codecov.io/gh/NYU-Processor-Design/nyu-core/branch/main/graph/badge.svg?token=McspW0gLf4)](https://codecov.io/gh/NYU-Processor-Design/nyu-core) 

The NYU ProcDesign Core will be a RISCV-32I compatible core with a 5 stage pipeline.

The repo contains the modules and test for components that make up the core design.

## Core Components

The core modules include:

- [Arithmatic Logic Unit (ALU)](/Documentation/01_Module_Docs/09_ALU.md)
- [General Registers](/Documentation/01_Module_Docs/00_CPU_general_purpose_registers.md)
- [Program Counter](/Documentation/01_Module_Docs/15_Program_Counter.md)

## Branching Logic

The branch logic modules include:
- [Branch Evaluator](/Documentation/01_Module_Docs/06_Branch_Evaluator.md)
- [Branch Predictor](/Documentation/01_Module_Docs/16_Branch_Predictor.md)
- [Branch Address Calculator](/Documentation/01_Module_Docs/17_Branch_Address_Calculator.md)
- [Branch Manager](/Documentation/01_Module_Docs/18_Branch_Manager.md)

## Pipeline

The pipeline will have 5 stages:
- Instruction Fetch (IF)
- Instuction Decode (ID)
- Execution (EX)
- Memory Access (MEM)
- Write Back (WB)

The pipeline will require 4 latch modules:
- [IF/ID Latch](/Documentation/01_Module_Docs/01_IF_ID_latch.md)
- [ID/EX Latch](/Documentation/01_Module_Docs/02_ID_EX_Latch.md)
- [EX/MEM Latch](/Documentation/01_Module_Docs/03_EX_MEM_Latch.md)
- [MEM/WB Latch](/Documentation/01_Module_Docs/04_MEM_WB_Latch.md)

## General Control and Hazards

Control Modules:
- [Processor State Module](/Documentation/01_Module_Docs/08_Processor_State.md)
- [Pipeline Reset Module](/Documentation/01_Module_Docs/05_General_Control_Module.md)

## Cache

Cache Modules:
- [Instruction Cache Manager](/Documentation/01_Module_Docs/13_Instruction_Cache_Manager.md)
- [L1 Instruction Cache](/Documentation/01_Module_Docs/14_L1_Instruction_Cache.md)
- [Data Cache Manager](/Documentation/01_Module_Docs/07_Data_Cache_Manager.md)
- [L1 Data Cache](/Documentation/01_Module_Docs/10_L1_Data_Cache.md)
- [L2 Data Cache](/Documentation/01_Module_Docs/11_L2_Data_Cache.md)
- [L3 Data Cache](/Documentation/01_Module_Docs/12_L3_Data_Cache.md)

## Current Draft of CPU Diagram

![cpu](https://github.com/NYU-Processor-Design/nyu-core/assets/114675487/bbca7faa-2fb1-4a17-9122-f1c0c2c3d392)

## Further Reading

[Development and Testing Guidelines](https://github.com/NYU-Processor-Design/nyu-core/blob/main/Documentation/00_Dev_and_Test_Docs/dev-test-process.md)

[Offical RISCV Unprivileged Instruction Set Documentation](https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
