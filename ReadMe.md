# NYU ProcDesign Core

The NYU ProcDesign Core will be a RISCV-32I compatible core with a 5 stage pipeline.

The repo contains the modules and test for components that make up the core design.

## Core Components

The core modules include:

- Arithmatic Logic Unit (ALU)
- Immediate Sign Extension
- General Registers
- Program Counter=
- Branch Predictor 

## Pipeline

The pipeline will require 4 latch modules:
- IF/ID Latch
- ID/EX Latch
- EX/MEM Latch
- MEM/WB Latch

The pipeline will have 5 stages:
- Instruction Fetch (IF)
- Instuction Decode (ID)
- Execution (EX)
- Memory Access (MEM)
- Write Back (WB)

## General Control and Hazards

Control Modules:
- Processor State Module
- General Control Module
- Hazard Detection

## Cache

Cache Modules:
- Cache Manager
- L1 Instruction Cache
- L1 Data Cache
- L2 Data Cache
- L3 Data Cache

## Further Reading

[Offical RISCV Instruction Set Documentation](/https://riscv.org/wp-content/uploads/2017/05/riscv-spec-v2.2.pdf)
