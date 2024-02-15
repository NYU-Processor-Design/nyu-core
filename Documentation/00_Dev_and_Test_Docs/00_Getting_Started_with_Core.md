# Welcome to NYU Core!
Since you've decided to take part in the core development of Processor Design Team, here is all you need to know to navigate and contribute to the repo!
## Navigating through the Repo
You will notice that there is a specific organization going on in this repo that may seem slightly daunting, but fear not! All will be explained so that you know exactly where to find and pull request to. Generally, you will find yourself utilizing the [Documentation](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/Documentation) folders and Issues for guides in implementation, and the [dv](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/dv) and [rtl](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/rtl) folders for contributions.

### [Documentation](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/Documentation)
This folder is where all the outlines and guides live. These helpful outlines ensure that what is implemented in the core is exactly what is needed.

- [**Module Docs**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/Documentation/01_Module_Docs) include the inputs, outputs, function/overall behavior of the modules. 
- [**Complex Module Docs**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/Documentation/02_Complex_Module_Functions) are modules that contain more logic and implementation that the aforementioned modules. It, too, includes input/outputs and functionality, but additionally contains logic that will need to be considered in the design for the functionality to be correct.
- [**Interface Docs**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/Documentation/03_Interface_Docs) include the modules involved and desired connections amongst inputs/outputs.
- [**Connection Module Docs**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/Documentation/04_Connecting_Module_Docs) include input/outputs, modules involved, internal/external input/outputs, and internal connections needed.
- [**DV**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/dv) stands for design verification test. The dv folder thus holds all of our testing files written in C++. 
- [**RTL**](https://github.com/NYU-Processor-Design/nyu-core/tree/889d6077905a8af8b316b49c64898d4c2cb00006/rtl) holds files for the main module code and are written in system verilog.
### Issues
At the top of the repo, the second tab should house the "Issues" tab. This is where you will find what remains to be implemented and where you can find a task to get started on. 

It is recommended that you look through the documentation (if applicable) of each issue to familiarize yourself with what needs to be considered before implementation. The status of issues pertaining to hardware design and implementation is best viewed through our [Core Design and Implementation](https://github.com/orgs/NYU-Processor-Design/projects/4/views/1) project page.

**Notable Issue Categories**:
- **To Outline**: Modules that are **NOT yet outlined** and available to outline
- **Outline Complete**: Modules that are already outlined and **ready to be implemented**. 
- **Outline/Implementation in Progress**: Modules are **currently assigned to someone** but you can always ask that person if they would like help.
- **Needs To Be Connected**: Implemented and **only available** to be worked on as part of a **higher level module that contains them**. This means that if you're working on a connecting module or interface that involves a module with this tag, it is **already implemented and ready for use**.

To begin on an issue, reach out to the **Core Czar** to be assigned to the issue in question to ensure no one ends up working on the same thing unintentionally.

## Choosing an Issue
If an issue has an outlined doc, then you can refer to the [Dev and Test Process Doc](https://github.com/NYU-Processor-Design/nyu-core/blob/95ad3a6738f45e143dfd6e57852e4181e009e14d/Documentation/00_Dev_and_Test_Docs/dev-test-process.md) to begin implementing a module. The document will walk you through the development and testing processes needed to implement a module, which can be similarly applied to implementing a complex module, interface, or connecting module.

If an issue if **NOT** outlined, then you can also choose to create the outline for this module. To do this, find the corresponding Markdown document (ending in .md) and create an outline that includes the needed inputs, outputs, functionality, connectors, and anything else that is needed for this module to function.

Alternatively, if there is an "In Progress" module that you take great interest in, you can -- respectfully -- contact whoever is assigned to the module to see if any help is needed in the implementation.

## Incorporating your Work to the Repo
### Naming
Make sure that the header of your development test files and rtl module files match the name of the module being implemented, or at least is fully explicit as to which module is being implemented. Through this team's convention, **dv** file headers should be all **_lowercase_** followed by .cpp, while **rtl** files will utilize **_capitalization_** and be followed by .sv. 

For interfaces and connection modules, a prefix is added to distinguish them from base level modules. **Int** for interfaces and **Con** for connection modules. ex: Con_EX.sv or int_mem.cpp.

### Pull Requests
The pull requests tab located third from the left in the toolbar works almost the same as a pull request for your design notebook. However, please make sure that your files are located in the correct folders before PR!

If you are still unfamiliar with how to PR, kindly refer to the [Your First Pull Request](https://github.com/NYU-Processor-Design/nyu-processor-design.github.io/blob/af340fc7c9433157a88d9df93e2ec2b381032d2d/src/getting_started/notebooks/04_first_pr.md) document.

Enjoy NYU Core and happy developing!
