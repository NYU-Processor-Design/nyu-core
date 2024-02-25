# L1_Data_Cache Module

## Overview
`L1_Data_Cache` is a Verilog module designed to simulate an L1 data cache with a write-back policy and a least recently used (LRU) replacement algorithm. This module is a part of a larger memory hierarchy system and interacts with lower memory levels (like L2 cache).

## Module Interface

### Inputs
- **clk**: Clock signal.
- **reset**: Reset signal.
- **write_enable**: Enable signal for write operations.
- **read_enable**: Enable signal for read operations.
- **request_address**: Address for the current read/write request.
- **write_data**: Data to be written into the cache.
- **mem_response_data**: Data received from the RAM.
- **mem_ready**: Signal indicating readiness of the RAM.

### Outputs
- **response_data**: Data returned in response to a read operation.
- **c_state**: Current state of the cache (for debugging/monitoring).
- **mem_request**: Signal to request data from RAM.
- **mem_write_enable**: Enable signal for writing data to RAM.
- **mem_address**: Address for RAM operations.
- **mem_write_data**: Data to be written to the RAM.

## Key Parameters and Constants
- **CACHE_SIZE**: Total size of the L1 cache (4 KB).
- **BLOCK_SIZE**: Size of each cache block (4 bytes).
- **ASSOCIATIVITY**: Set associativity of the cache (2-way).
- **DATA_WIDTH**: Width of the data (32 bits).
- **NUM_SETS**: Number of sets in the cache.
- **ADDR_WIDTH**: Width of the memory address.

## Internal Design

### SRAM Module
- The cache utilizes an `sram_module` for storing and retrieving cache data.

### Cache Structure
- The cache is organized into sets and ways, with arrays for tags, valid bits, and dirty bits.
- LRU counters are maintained for each set to implement the LRU replacement policy.

### State Machine
- The cache operates as a `Mealy`` finite state machine with states: `IDLE`, `CHECK_TAG`, `WRITEBACK`, and `FILL`.

## Functionality

### Cache Operations
- **Read/Write Access**: On receiving a read or write request, the cache checks for a hit or miss.
- **Write-Back**: On a write miss with a dirty line, data is written back to the lower memory level.
- **Cache Fill**: On a miss, data is loaded from the lower memory level.

### LRU Algorithm
- The cache uses an LRU algorithm to determine which cache line to replace on a miss.

### Reset Logic
- A reset functionality is provided to clear the cache and reset its state.

## Implementation Details

### Tasks and Functions
- Several tasks and functions are used to modularize operations like handling cache hits, cache misses, LRU calculations, and SRAM interactions.

### Handling Cache States
- The module defines specific tasks for handling different cache states and transitioning between them based on the current operation.

## Notes & Scope for Improvements
- This module is designed with considerations for modularity and performance optimization. It can be integrated into larger systems requiring cache functionality with LRU management.
- ECC, byte accessible, Non-blocking cache, different controllers 


---
