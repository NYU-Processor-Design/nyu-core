# L1_Data_Cache Module Detailed Documentation

## Overview
The `L1_Data_Cache` module in Verilog simulates an L1 data cache with write-back policy and LRU (Least Recently Used) replacement strategy. It's designed to interface with RAM.
## Module Structure

### Inputs and Outputs

#### Inputs
| Input             | Description                           | Bit Width |
|--------------------|----------------------------------------|-----------|
| `clk`              | Clock signal                           | 1         |
| `rstn `            | Reset signal                           | 1         |
| `write_enable`     | Enable signal for write operations     | 1         |
| `read_enable`      | Enable signal for read operations      | 1         |
| `request_address`  | Address for read/write request         | 32        |
| `write_data`       | Data to write into cache               | 32        |
| `mem_response_data`| Data received from RAM                 | 32        |
| `mem_ready`        | Signal indicating RAM readiness        | 1         |
| `data_mode`        | 0 for Byte, 1 for Half, 2 for Word     | 2         |

#### Outputs
| Output            | Description                           | Bit Width |
|-------------------|---------------------------------------|-----------|
| `response_data`   | Data output for read operations       | 32        |
| `c_state`         | Current state of cache (debugging)    | 2         |
| `mem_request`     | Request signal for RAM                | 1         |
| `mem_write_enable`| Write enable for RAM                  | 1         |
| `mem_address`     | Address for RAM operations            | 32        |
| `mem_write_data`  | Data to write to RAM                  | 32        |

### Parameters and Constants

| Parameter         | Description                         | Value / Formula                |
|-------------------|-------------------------------------|--------------------------------|
| `CACHE_SIZE`      | Total size of L1 cache              | 4 * 1024 (4 KB)                |
| `BLOCK_SIZE`      | Size of each cache block            | 4 bytes                        |
| `ASSOCIATIVITY`   | Set associativity of cache          | 2-way                          |
| `DATA_WIDTH`      | Width of data                       | 32 bits                        |
| `BLOCK_WIDTH`     | Width of each cache block           | `BLOCK_SIZE * 8`               |
| `NUM_SETS`        | Number of sets in cache             | `CACHE_SIZE / (BLOCK_SIZE * ASSOCIATIVITY)` |
| `ADDR_WIDTH`      | Width of memory address             | 32 bits                        |
| `OFFSET_WIDTH`    | Width of block offset               | Calculated from `BLOCK_SIZE`   |
| `INDEX_WIDTH`     | Width of cache set index            | Calculated from `NUM_SETS`     |
| `TAG_WIDTH`       | Width of cache tag                  | `ADDR_WIDTH - OFFSET_WIDTH - INDEX_WIDTH` |

### Cache Structure

| Component         | Description                       | Type / Bit Width                |
|-------------------|-----------------------------------|---------------------------------|
| `cache_tags`      | Stores tags for each cache line   | Array of TAG_WIDTH              |
| `valid`           | Indicates if a cache line is valid| Array of 1-bit flags            |
| `dirty`           | Indicates if a cache line is dirty| Array of 1-bit flags            |
| `lru_counter`     | LRU counters for each cache line  | Array of counters               |

## Functional Overview

### State Machine
The cache operates through a state machine with distinct states for handling various operations:
- **IDLE**: Awaiting read or write requests.
- **CHECK_TAG**: Checking if the requested address is in the cache (cache hit) or not (cache miss).
- **WRITEBACK**: Writing back data to the RAM for dirty cache lines on a miss.
- **FILL**: Fetching data from the RAM to fill the cache line on a miss.

### Cache Operations
- **Read/Write**: Handles read and write operations, checking for cache hits or misses.
- **Write-Back**: Writes back dirty data to RAM cache on misses.
- **Cache Fill**: Loads data from RAM cache on misses.

### LRU Algorithm
- Implements an LRU algorithm for cache line replacement.

### Modular Design
- The module leverages tasks and functions to compartmentalize operations such as hit/miss handling, LRU logic, and SRAM interactions.

### State Handling
- Dedicated tasks manage state transitions and actions, ensuring clear and maintainable state logic.

## Integration and Performance
- The design is optimized for integration into systems requiring L1 cache functionality, with a focus on performance and modularity.


---
