# Module Development and Testing

You've decided to create a module for the processor. That's great news! Here's a rundown on the development process.

## Step 1: Pick a module
The nyu-core repository will have open issues with modules that are yet to be outlined and/or implemented. 

If a module needs to be outlined, add a Markdown file to the [Module Documentation folder](https://github.com/NYU-Processor-Design/nyu-core/tree/main/Documentation/Module-Docs) with a description of the module, including the inputs, outputs, and functions. Additionally, edit the [ReadMe file](https://github.com/NYU-Processor-Design/nyu-core#readme) of the repository and link your outline document to the corresponding module name.

If a module has already been outlined, and needs to be implemented, find the outline document for that module on the ReadMe to assist you as you implement.

## Step 2: Implement the module
There are two main parts/files you need to add when implementing a component.
+ Module: this will be a System Verilog file with the module itself, based on the component outline.

  + The module file should be stored in the /nyu-core/**rtl** folder.
+ Test: this is a C++ file with a design verification test that ensures your module works properly.

  + The test file belongs in the /nyu-core/**dv** folder.

### Step 2.1: Test the module
To link your module and test, you need to *call* the module within your test program. In order to properly call the module, use these [guidelines](https://nyu-processor-design.github.io/getting_started/onboarding/05_verification2.html#adapting-the-test-cases) from Onboarding Lab 4.
```cpp
TEST_CASE("Module Test") {
  // replace exampleModule with the name of your module
  VexampleModule model;
  
  //setup module inputs
  model.input1 = 1;
  model.input2 = 2;
  model.eval();
  
  //calculate expected value
  int expected;
  
  REQUIRE(model.out == expected);
}
```

## Step 3: Edit CML files
In order to allow the repo's Verilator to properly verify your module with your test, you must edit the CMakeLists files in the `dv` and `rtl` folders.

In the `dv` CML, find the `target_sources()` command. This command will likely have tests already. Add the name of your .cpp file to the list of tests. Next, locate the `nyu_target_verilate()` command, which will also already have modules. Add the name of your module (without the .sv suffix) to the list of top modules.

In the `rtl` CML, add your module file name (with the .sv suffix) to the list within `nyu_add_sv()` command.

For a refresher on enabling testing and the commands mentioned above, check out Onboarding Lab 4 from the [Subdirectories section](https://nyu-processor-design.github.io/getting_started/onboarding/05_verification2.html#subdirectories-and-nyu_-commands)

## Step 4: PR & Verilator test
It's time to check your module functionality and design verification. Create a pull request from your fork to the main nyu-core repo. After doing so, the Verilator will automatically run through all of the available modules and tests specified in the CML files and tell you if your test cases passed.

## Good Development & Testing Practices
+ Test as many inputs as possible. Testing a single input won't fully check the functionality of your module.

  + When in doubt, create a loop with MANY iterations and use random number generation for your inputs.
  ```cpp
  TEST_CASE("Module Test Loop") {
    VexampleModule2 model;
    
    // large for loop
    for (int i = 0; i < 1000; i++) {
    
      //random number generation
      uint32_t input = rand() % (int) (pow(2, 32) - 1); // mod your random number by the largest possible value of the input size
      // the input here is 32 bits, so we mod by pow(2, 32) - 1
      
      model.input1 = input;
      model.eval();
  
      int expected;
  
      REQUIRE(model.out == expected);
    }
  }
  ```
  
+ Use good variable and data object names! This will make it easier for you when testing your modules and others when using your modules.
+ Remember the engineering cycle: make, test, break, redo, repeat. Many modules can and should be improved. Create tests to find the breaking points of your components so you can fix them!

Happy developing!
