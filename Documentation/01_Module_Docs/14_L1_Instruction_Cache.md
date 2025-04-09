# L1 Instruction Cache #

## Contents
* Inputs
* Outputs
* Functionality
  * Registers
  * Clk
  * Active low reset

## Inputs
| Name                | Bits wide        |
|:--------------------|:----------------:|
| `clk`               | 1-bit            |
| `rstn`              | 1-bit            |
| `read_enable`       | 1-bit            |
| `request_address`   | ADDR_WIDTH-bit   |
| `mem_response_data` | DATA_WIDTH-bit   |
| `mem_ready`         | 1-bit            |

## Outputs
| Name                | Bits wide        |
|:--------------------|:----------------:|
| `response_data`     | DATA_WIDTH-bit   |
| `mem_request`       | 1-bit            |
| `mem_address`       | ADDR_WIDTH-bit   |
| `c_state`           | 2-bit            |

## Functionality
### Registers
- `valid_bits`: Indicates whether a cache line is valid.
- `tag_array`: Holds the tag for each cache line.
- `lru_bits`: Maintains the least recently used (LRU) replacement policy.

### On posedge clk
- If `read_enable` is high:
  - Check whether the cache has a hit or miss.
  - If it’s a hit, set `response_data` to the instruction stored in the cache.
  - If it’s a miss, generate a memory request by setting `mem_request` to 1 and load data from the address stored in `mem_address`.

  - Use the LRU algorithm to select which cache line to replace:
    | Name           | Condition               |
    |----------------|-------------------------|
    | `lru_bits == 0`| Replace the first cache line |
    | `lru_bits == 1`| Replace the second cache line |

### Asynchronous active low reset
- All `valid_bits` and `lru_bits` are reset to 0.
- The `tag_array` is cleared.
