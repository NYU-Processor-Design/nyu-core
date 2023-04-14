# NYU ProcDesign Core

The NYU ProcDesign Core will be a RISCV-32I compatible core with a 5 stage pipeline.

The repo contains the modules and test for components that make up the core design.

## Core Components

The core modules include:

- Arithmatic Logic Unit (ALU)
- General Registers
- Program Counter


## Branching Logic

The branch logic modules include:
- Branch Evaluator
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
- IF/ID Latch
- ID/EX Latch
- EX/MEM Latch
- MEM/WB Latch

## General Control and Hazards

Control Modules:
- Processor State Module
- General Control Module
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

![cpu](https://user-images.githubusercontent.com/114675487/227744544-d11337b4-d2cd-4ffe-ab16-372450b8b47d.png)

## Further Reading

[Offical RISCV Instruction Set Documentation](/https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)

