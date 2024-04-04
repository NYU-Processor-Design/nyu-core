# THIS MODULE IS NOT YET OUTLINED #

# L1 Instruction Cache #
(Any Notes would go here)

## Contents
* [Inputs](#inputs)
* [Outputs](#outputs)
* [Functionality](#functionality)
  * [Registers](#registers)
  * [Clk](#on-posedge-clk)
  * [Active low reset](#asynchronous-active-low-reset)

## Inputs
|Name|Bits wide|
|:---|:---:|
|```name```|#-bit|
|```name```|#-bit|

## Outputs
|Name|Bits wide|
|:---|:---:|
|```name```|#-bit|
|```name```|#-bit|

## Functionality
### Registers
  - #-bit ```name``` register
  - #-bit ```name``` register
### On posedge clk
  - ```somebranch = someval```
  - Use a table when necessary if statements are used:
  - ```name```
    |Name|Bits wide|
    |---|---|
    |```name == 0```|```reg = val```|
    |```name == 1```|```reg = val```|
  

### Asynchronous active low reset
  - Register values reset to 0
#include <iostream>
#include <unordered_map>

class L1Cache {
 private:
  std::unordered_map<int, int> cache;
  int size;

 public:
  L1Cache(int size) : size(size) {}

  int read(int address) {
    if (cache.count(address) > 0) {
      // Cache hit
      return cache[address];
    } else {
      // Cache miss
      if (cache.size() >= size) {
        // Evict the least recently used entry
        auto iter = cache.begin();
        cache.erase(iter);
      }
      cache[address] = address; // Store the new entry
      return address;
    }
  }
};

int main() {
  L1Cache cache(4); // Create a cache of size 4
  cache.read(1);
  cache.read(2);
  cache.read(3);
  cache.read(4);
  cache.read(5); // This should evict the entry at address 1
  cache.read(1); // This should re-add the entry at address 1
  return 0;
}
