# L1 Data Cache Module Documentation

### Inputs
1. **clk**: System clock signal.
2. **reset**: Reset signal for initializing the cache.
3. **request_address**: A 32-bit input representing the memory address for read or write operations.
4. **write_data**: A 32-bit input representing the data to be written to the cache.
5. **write_enable**: An input signal to control write operations to the cache.

### Outputs
1. **response_data**: A 32-bit output representing the data read from the cache.

## Functionality
The `l1_data_cache` module is designed to provide a data caching mechanism that stores frequently accessed data to improve memory access speed. It operates based on the following functionality:

## On Posedge

The L1 Data Cache is a synchronous circuit, operating on a clock signal. On the positive edge (posedge) of the clock, the following operations are performed:

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
- **`cache_tags`**: A 2D array storing the tag information for cache sets and blocks.
- **`dirty_bit`**: A 2D array indicating whether the data in each block is dirty (needs to be written back to memory).

## Combinational and Sequential Logic

- The L1 Data Cache uses both combinational and sequential logic. Combinational logic is used for address decoding, tag comparison, and hit/miss detection. Sequential logic is used to store cache lines, implement the LRU replacement policy, and track the write-back status of cache lines.


## Cache logic
The cache should use the following logic:

- **`Write allocate`**`:  When the processor writes data to the cache, the cache should fetch the block from the main memory and store it in the cache if the block is not present in the cache.
- **`Write back`**:       When the processor writes data to the cache, the cache should update the data in the cache and set the dirty bit to high. The cache should write the data to the main memory only when the block is evicted from the cache.
- **`Lookthrough`**`: When the cache misses, the cache should fetch the block from the main memory and store it in the cache. The processor should not stall during this time.
- **`LRU`**: The cache should use the LRU policy to determine the least recently used block.



