# L1 Data Cache Outline

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)
  * [Registers](#registers)
  * [On posedge clk](#on-posedge-clk)
  * [Asynchronous active low reset](#asynchronous-active-low-reset)

## Inputs
| Name              | Bits wide | Description                                  |
|-------------------|:---------:|----------------------------------------------|
| `clk`             | 1         | Clock input                                  |
| `reset`           | 1         | Asynchronous active low reset input         |
| `write_enable`    | 1         | Write enable signal                         |
| `request_address` | 32        | Address for read or write operation         |
| `write_data`      | 32        | Data to be written to the cache             |

## Outputs
| Name            | Bits wide | Description                                  |
|-----------------|:---------:|----------------------------------------------|
| `response_data` | 32        | Data read from the cache                     |

## Functionality

### Registers
| Name                  | Type         | Dimensions                       | Description                                  |
|-----------------------|--------------|----------------------------------|----------------------------------------------|
| `cache_data`          | 32-bit array | `[0:NO_OF_SETS-1][0:ASSOCIATIVITY-1]` | Data storage array in each cache set         |
| `cache_tags`          | 32-bit array | `[0:NO_OF_SETS-1][0:ASSOCIATIVITY-1]` | Tag storage array in each cache set          |
| `valid`               | 1-bit array  | `[0:NO_OF_SETS-1][0:ASSOCIATIVITY-1]` | Valid bit array indicating cache line status |
| `dirty`               | 1-bit array  | `[0:NO_OF_SETS-1][0:ASSOCIATIVITY-1]` | Dirty bit array indicating modified data    |
| `lru_counter`         | 32-bit array | `[0:NO_OF_SETS-1][0:ASSOCIATIVITY-1]` | LRU counter array for each cache set         |

### On posedge clk
- Calculate cache set index: `set = (request_address / BLOCK_SIZE) % NO_OF_SETS;`
- Determine cache hit or miss
  - If hit, update `response_data` with cache data and reset LRU counter
  - If miss, (not implemented for simplicity) fetch data from memory and update cache_tags, cache_data, and LRU counters

### Asynchronous active low reset
- Reset all LRU counters, dirty bits, and valid bits to initial values


