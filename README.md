# BlankConsoleApp

This project is a template for C (not C++, irrespective of GitHub's language analysis) code in Visual Studio 2019 set up for two methods of unit tests
 - MS Test
 - minunit
 
The idea is that you start by checking out a copy of this repo, then rename the app projects, then replace the sample_funcs files with your own and add your own tests.

Once you've done the renaming, commit your files to your own repo, keeping this repo clean as a template.

Setting up this repo from scratch is described at http://blog.martincowen.me.uk/unit-testing-embedded-c-on-target-with-minunit-and-off-target-with-ms-test.html

You do not need to know C++ to use this repo and to write tests despite the .cpp files.
 
## Structure  
The code-under-test is in the BlankConsoleApp project with these source code files
- main.c
- main.h
- minunit.h
- mu_test_main.c
- sample_funcs.c
- sample_funcs.h

The MS Test unit tests are in the BlankUnitTest project in
 - BlankUnitTest.cpp
 
## Usage
The project is setup to run tests using either MS Test or minunit.

### Your code-under-test
If testing a few small functions, you can just add them to sample_funcs.c and prototypes for the externally visible ones (non static) to sample_funcs.h

If you want to test complete files, add them to the (renamed) BlankConsoleApp project and add them to the #include list in (renamed) BlankUnitTest.cpp. In this file, the #include list needs the C files, not the H files.  
Then add the H files to the #includes in mu_test_main.c

### Adding Tests
Unfortunately the test syntax is slightly different between minunit and MS Test so you can't repurpose the exact same tests. There is also the problem that one is C and one is C++ and there are incompatibilities between those.

#### Adding tests for MS Test
In (renamed) BlankUnitTest.cpp, copy and edit the sample test method, making sure that each test method has a unique name within the test class. This name will appear in the Test Explorer but does not appear anywhere else in code. The MS Test framework does the work of discovering it, running the test and listing it, when you ask it to run.

The only C++ you need to use is Assert, likely only the AreEqual and AreNotEqual methods will suffice. If you need to know the complete list of methods for Assert, they are documented here https://docs.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts

#### Adding tests for minunit
In mu_test_main.c, copy and edit the mu_sampletest1() function. You can add custom messages for each assert failure.  
Add calls to those new functions from mu_all_test().

### Running Tests
#### Running MS Tests
Use the Test menu in Visual Studio to Run All Tests or Repeat Last Run. The results show up in the Test Explorer window.

#### Running minunit Tests
Build and run your project with F5. The results show up in the console.

### Debugging Tests
#### Debugging with MS Test
You have to use the Debug within the Test menu of Visual Studio, not the top level Debug menu. Debug All Tests or Debug Last Run. Breakpoints can be set in the tests and the code under test.

#### Debugging with minunit
The standard Start Debugging run command F5 works with this.

#### Log Info Options
Since minunit can run either on the host (PC, in Visual Studio) or target (any embedded C compiler), you may need to get the log messages to display differently depending on your available hardware.

mu_test_main.c has these options  
 - #define STD_OUTPUT_TO_PRINTF so that the messages are sent to the console, use this for stdio
 - #define STD_OUTPUT_TO_NRF_LOG_INFO on a Nordic Semiconductor platform with Segger SES so that the messages are displayed on the SES console window.

If your target hardware does not have a standard IO display but has a few pins  available and you have a digital scope or logic analyser, my blog post mentioned at the top shows other methods of getting logs displayed on those. Otherwise you'll be limited to LEDs for running, pass, failed status.

## Environment
This is a Visual Studio 2019 solution and project but you can also take these files and build in an embedded environment
 - minunit.h
 - mu_test_main.c
 - main.c, or its contents incorporated into your main.c
