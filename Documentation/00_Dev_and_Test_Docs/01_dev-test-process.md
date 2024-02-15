# Module Development and Testing

You've decided to create a module for the processor. That's great news! Here's a rundown on the development process.

## Step 1: Pick a module
The nyu-core repository will have open issues with modules that are yet to be outlined and/or implemented. 

If a module needs to be outlined, edit the corresponding Markdown file in the [Module Documentation folder](https://github.com/NYU-Processor-Design/nyu-core/tree/main/Documentation/01_Module_Docs) with a description of the module, including the inputs, outputs, and functions.

If a module has already been outlined, and needs to be implemented, find the outline document for that module on the [ReadMe](https://github.com/NYU-Processor-Design/nyu-core/blob/889d6077905a8af8b316b49c64898d4c2cb00006/ReadMe.md) or [Core Design and Implementation Project](https://github.com/orgs/NYU-Processor-Design/projects/4/views/1) to assist you as you implement.

## Step 2: Implement the module
There are two main parts/files you need to add when implementing a component.
+ Module: this will be a System Verilog file with the module itself, based on the component outline.

  + The module file should be stored in the [**rtl folder**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/rtl).
      
      + For interfaces and connection modules, a prefix is added to distinguish them from base-level modules. Int for interfaces and Con for connection modules.
+ Test: this is a C++ file with a design verification test that ensures your module works properly.

  + The test file belongs in the [**dv folder**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/dv).

### Step 2.1: Test the module
To link your module and test, you need to *call* the module within your test program. In order to properly call the module, use these [guidelines](https://nyu-processor-design.github.io/getting_started/onboarding/05_verification2.html#adapting-the-test-cases) from Onboarding Lab 4.

Ensure that these statements are included at the top of your cpp file:
```cpp
#include <cstdint>
#include <catch2/catch_test_macros.hpp>
#include <NyuTestUtil.hpp>
#include <VDevice.h>
```
Grab reference to a device with `nyu::getDUT<VDevice>()` to set up needed evaluations/tests:
```cpp
static void some_test(uint32_t input1, uint32_t input2) {
   auto& device {nyu::getDUT<VDevice>()};
   // needed inputs
   device.input1 = input1;
   device.input2 = input2;
   nyu::eval(device);

   // INFO statements help give visibility to what is being tested
   INFO("Testing an input1 = " << input1 << ", input2 = " << input2);

   // REQUIRE statements are needed to ensure requirements of the module exist before continuing with testing
   REQUIRE(device.input1 == some_required_value); 
}
```
Create a test function that runs through different inputs utilized in this module (take care that all inputs that affect the module are included in the input variables for test() and are looped through):
```cpp
static void test(uint32_t input1, uint32_t input2) {
    // loop through inputs ensuring consistent and proper coverage! (Demonstrated below)
    for(std::uint32_t input1 {0}; input1 < 128; ++input1)
        for(std::uint32_t input2 {0}; input2 < 128; ++input2)
          some_test(input1, input2);
    for(std::uint32_t input1 {1}; input1; input1 <<= 1)
        for(std::uint32_t input2 {1}; input2; input2 <<= 1)
          some_test(input1, input2);
```
Create test cases for the functions your module should be able to handle using the test function you've created:
```cpp
TEST_CASE("Module Test") {
  // define the inputs as the values utilized in the particular test case you are created, create as many test cases as needed
  test(input1, input2); ex: test(0,0), test(0,1), etc.
}
```

## Step 3: Edit CML files
In order to allow the repo's Verilator to properly verify your module with your test, you must edit the CMakeLists files in the `dv` and `rtl` folders.
**Modules containing other sub modules must come *before* the sub modules in question.**

In the [dv CML](https://github.com/NYU-Processor-Design/nyu-core/blob/889d6077905a8af8b316b49c64898d4c2cb00006/dv/CMakeLists.txt), find the `target_sources()` command. This command will likely have tests already. Add the name of your .cpp file to the list of tests. Next, locate the `nyu_target_verilate()` command, which will also already have modules. Add the name of your module (without the .sv suffix) to the list of top modules.

In the [rtl CML](https://github.com/NYU-Processor-Design/nyu-core/blob/889d6077905a8af8b316b49c64898d4c2cb00006/rtl/CMakeLists.txt), add your module file name (with the .sv suffix) to the list within `nyu_add_sv()` command.

For a refresher on enabling testing and the commands mentioned above, check out Onboarding Lab 4 from the [Subdirectories section](https://nyu-processor-design.github.io/getting_started/onboarding/05_verification2.html#subdirectories-and-nyu_-commands)

## Step 4: PR & Verilator test
It's time to check your module functionality and design verification. Create a pull request from your fork to the main nyu-core repo. After doing so, the Verilator will automatically run through all of the available modules and tests specified in the CML files and tell you if your test cases passed.

You can also run the tests locally using the process described in the onboarding labs. It is generally best practice to first run tests locally to ensure no simple-to-fix issues like syntax errors are present.

## Good Development & Testing Practices
+ Test as many inputs as possible. Testing a single input won't fully check the functionality of your module.

  + Each bit of the input space should be tested in isolation so that the coverage is always reported consistently! This can be done similarly to the following:
  ```cpp
    for(std::uint32_t input1 {0}; input1 < 128; ++input1)
        for(std::uint32_t input2 {0}; input2 < 128; ++input2)
          some_test(input1, input2);
  ```
  
+ Use good variable and data object names! This will make it easier for you when testing your modules and others when using your modules.
+ Remember the engineering cycle: make, test, break, redo, repeat. Many modules can and should be improved. Create tests to find the breaking points of your components so you can fix them!
+ **USE COMMENTS!!!** This helps you to document your thought process, which can help you code better AND can allow others to help you out with a problem or carry on through something you started but had to drop.

Happy developing!
