# IF Connection Module
(Verilog module known as Con_IF)

## Contents
* [Overview](#overview)
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Modules](#modules)
  * [PC](#pc)
  * [Instruction Cache](#instruction_cache)
* [Internal Connections](#internal_connections)
* [Workflows](#workflows)
  * [PC Update Process](#pc-update-process)
  * [Instruction Fetch Process](#instruction-fetch-process)
  * [Memory Access Process](#memory-access-process)

## Overview
The IF Connection Module (`Con_IF`) is responsible for managing the instruction fetch stage of the pipeline. It includes the `PC` module for tracking the program counter and the `Instruction Cache` module for storing and retrieving instructions efficiently.

## Inputs
| Name | Bits wide | Description |
|:---|:---:|:---|
| `clk` | 1-bit | Global clock signal |
| `cache_clk` | 1-bit | Dedicated clock for the instruction cache |
| `rstn` | 1-bit | Active-low reset for the PC module |
| `rstn_h` | 1-bit | Active-low reset for the Instruction Cache |
| `pc_en` | 1-bit | Enables PC update when high |
| `npc` | 32-bit | Next PC value |

## Outputs
| Name | Bits wide | Description |
|:---|:---:|:---|
| `pc` | 32-bit | Current program counter value |
| `ins` | 32-bit | Instruction fetched from the Instruction Cache |

## Modules
### PC
#### External IO
##### External Inputs
| Name | Bits wide |
|:---:|:---:|
| `clk` | 1-bit |
| `rstn` | 1-bit |
| `pc_en` | 1-bit |
| `npc` | 32-bit |

##### External Outputs
| Name | Bits wide |
|:---:|:---:|
| `pc` | 32-bit |

#### Internal IO
##### Internal Outputs
| Name | Bits wide |
|:---:|:---:|
| `pc` | 32-bit |

### Instruction Cache
#### External IO
##### External Inputs
| Name | Bits wide |
|:---:|:---:|
| `cache_clk` | 1-bit |
| `rstn_h` | 1-bit |
| `mem_response_data` | 32-bit |
| `mem_busy` | 1-bit |

##### External Outputs
| Name | Bits wide |
|:---:|:---:|
| `ins` | 32-bit |
| `wEn` | 1-bit |
| `rEn` | 1-bit |
| `isBurst` | 1-bit |
| `mem_address` | 32-bit |
| `mem_write_data` | 32-bit |

#### Internal IO
##### Internal Inputs
| Name | Bits wide |
|:---:|:---:|
| `pc` | 32-bit |

## Internal Connections
| PC | Instruction Cache |
|:---:|:---:|
| `pc` | `pc` |

## Workflows
### PC Update Process
- `pc_en` controls when `pc` updates.
- If `rstn = 0`, reset `pc` to zero.
- If `pc_en = 1`, update `pc = npc`.

### Instruction Fetch Process
- `Con_IF` sends `pc` to `Instruction Cache`.
- If `rEn = 0`, `ins` is valid immediately (cache hit).
- If `rEn = 1`, `Con_IF` waits for `mem_busy = 0` before using `ins` (cache miss).

### Memory Access Process
- If `Instruction Cache` needs to access memory:
  - `rEn = 1` is asserted to request memory access.
  - `mem_address` is assigned the requested instruction's address.
  - `mem_busy = 1` indicates memory is still processing the request.
- Once `mem_busy = 0`, `Instruction Cache` updates `ins`.
- `Con_IF` receives `ins` only after `Instruction Cache` completes the memory transaction.

