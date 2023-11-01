# L1 Data Cache Module Documentation

### Inputs
1. **clk**: System clock signal.
2. **rst**: Reset signal for initializing the cache.
3. **request_address**: A 32-bit input representing the memory address for read or write operations.
4. **write_data**: A 32-bit input representing the data to be written to the cache.
5. **write_enable**: An input signal to control write operations to the cache.

### Outputs
1. **response_data**: A 32-bit output representing the data read from the cache.

## Functionality
The `l1_data_cache` module is designed to provide a data caching mechanism that stores frequently accessed data to improve memory access speed. It operates based on the following functionality:

- **Initialization**: On reset (`rst` signal), the cache is initialized, and the LRU counters and dirty bits are set to initial values.

- **Write Operations**:
  - When a write operation is enabled (`write_enable`), the module performs the following steps:
    1. Determines the set index based on the request address.
    2. Checks if the requested data is already in the cache.
    3. If the data is present in the cache, it updates the cache with the new data, sets the dirty bit, and updates the LRU counter.
    4. If the data is not in the cache, it may write back to memory (if the block being replaced is dirty), updates the tag, writes the data to the cache, sets the dirty bit, and updates the LRU counter.

- **Read Operations**:
  - When a read operation is requested, the module performs the following steps:
    1. Determines the set index based on the request address.
    2. Searches the cache for the requested data.
    3. If the data is found, it updates the response data and updates the LRU counter.
    4. If the data is not in the cache (a cache miss), it can fetch the data from the main memory and potentially implement write allocate.

## Registers
The module utilizes several registers to maintain cache state and metadata:

- **`cache_data`**: A 3D array storing the data in the cache.
- **`lru_counter`**: A 2D array representing the LRU counters for cache sets and blocks.
- **`tag`**: A 2D array storing the tag information for cache sets and blocks.
- **`dirty_bit`**: A 2D array indicating whether the data in each block is dirty (needs to be written back to memory).

## Operation on Positive Edge of Clock (Always Block)
The cache operates on the positive edge of the clock (`clk`) using an always block. The following steps describe the operation within the always block:

1. If a reset signal (`rst`) is asserted, the cache is initialized.
2. When a write operation is enabled (`write_enable`), the cache performs the steps mentioned above for write operations.
3. When a read operation is requested, the cache performs the steps for read operations, including checking for cache hits and, in case of a cache miss, fetching data from the main memory and potentially implementing write allocate.

