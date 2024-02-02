# Welcome to NYU Core!
Since you've decided to take part in the core development of Processor Design Team, here is all you need to know to navigate and contribute to the repo!
## Navigating through the Repo
You will notice that there is a specific organization going on in this repo that may seem slightly daunting, but fear not! All will be explained so that you know exactly where to find and pull request to.

### Documentation
This folder is where all the outlines and guides live. These helpful outlines ensure that what is implemented in the core is exactly what is needed.

- **Module Docs** include the inputs, outputs, function/overall behavior of the modules. 
- **Complex Module Docs** are modules that contain more logic and implementation that the aforementioned modules. It too includes inputs/outputs and functionality, but additionally contains logic that will need to be considered in the design for the functionality to be correct.
- **Interface Docs** include the modules involved and desired connections amongst inputs/outputs.
- **Connection Module Docs** include input/outputs, modules involved, internal/external input/outputs, and internal connections needed.
- **DV** stands for design verification test. The dv folder thus holds all of our testing files written in C++. 
- **RTL** holds files for the main module code and are written in system verilog.
### Issues
At the top of the repo, the second tab should house the "Issues" tab. This is where you will find what remains to be implemented. 

It is recommended that you look through the documentation of each issue to familiarize yourself with what needs to be considered before implementation.

To begin on an issue, reach out to Michael Lipp to be assigned to the issue in question to ensure no one ends up working on the same thing unintentionally.
### Pull Requests
The pull requests tab located third from the left in the toolbar works almost the same as a pull request for your design notebook. However, please make sure that your files are located in the correct folders before PR!

If you are still unfamiliar with how to PR, kindly refer to the ["Your First Pull Request"](https://github.com/NYU-Processor-Design/nyu-processor-design.github.io/blob/af340fc7c9433157a88d9df93e2ec2b381032d2d/src/getting_started/notebooks/04_first_pr.md).

## Choosing an Issue
### Outlined and Not Outlined
## Incorporating your Work to the Repo
### Naming
For interfaces and connection modules, a prefix is added to destingush them from base level modules. Int for interfaces and Con for connection modules.

### DV vs RTL
