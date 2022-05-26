# Lab-OOT-Spring-2022
A drawing program on demand (Course Lab of Object Oriented Technology, Fudan Spring 2022)

[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)]()
[![Build Status](https://travis-ci.org/pingcap/tidb.svg?branch=master)](https://travis-ci.org/pingcap/tidb)

See:
[GitHub repo](https://github.com/codeplay0314/Lab-OOT-Spring-2022)

[Design patterns](files/Design.pdf) used in this Lab

- To build executable file

    In Windows environment, enter
    ```bash
    git checkout windows
    mkdir build
    cd build
    cmake --build .
    ```

    In Linux environment, enter
    ```bash
    git checkout linux
    mkdir build
    cd build
    cmake ..
    make
    ```

- To test cases manually, enter
    ```bash
    ./draw -g [2/256] [test input file]
    ```
    for example, enter
    ```
    ./draw -g 256 test/general/script2-g256.txt
    ```
    Then the output will show in the console.

- To test cases automatically, first put the test input under folder `test`.

    Each subfolder is for a unit test of one specific command, except for that the `test/general` folder is for any type of test cases.

    The input file names should follow rules below:
    - Filename extensions must be `.txt`
    - Filenames must end with `-g2` or `-g256` to indicate command line parameters
    - File content is definied in `files/ootlab.pdf`

    Standard output files should be put in the same folder of the corresponding input files, and the file names should follow rules below;
    - Filename extensions must be `.txt`
    - Filenames must start with the same name of the corresponding input files following `_result` string

    Then, enter
    ```bash
    ctest
    ```

    If test runs smoothly, the outputs will be like
    ```text
    Test project Lab-OOT-Spring-2022/build
        Start 1: general
    1/7 Test #1: general ..........................   Passed    0.09 sec
        Start 2: line_cmd
    2/7 Test #2: line_cmd .........................   Passed    0.07 sec
        Start 3: text_cmd
    3/7 Test #3: text_cmd .........................   Passed    0.03 sec
        Start 4: macro_cmd
    4/7 Test #4: macro_cmd ........................   Passed    0.03 sec
        Start 5: color_cmd
    5/7 Test #5: color_cmd ........................   Passed    0.06 sec
        Start 6: undo_cmd
    6/7 Test #6: undo_cmd .........................   Passed    0.06 sec
        Start 7: redo_cmd
    7/7 Test #7: redo_cmd .........................   Passed    0.06 sec

    100% tests passed, 0 tests failed out of 7

    Total Test time (real) =   0.43 sec
    ```

    If any tests fail, redo_cmd test for instance, the outputs will be like
    ```text
    Test project Lab-OOT-Spring-2022/build
        Start 1: general
    1/7 Test #1: general ..........................   Passed    0.09 sec
        Start 2: line_cmd
    2/7 Test #2: line_cmd .........................   Passed    0.06 sec
        Start 3: text_cmd
    3/7 Test #3: text_cmd .........................   Passed    0.04 sec
        Start 4: macro_cmd
    4/7 Test #4: macro_cmd ........................   Passed    0.03 sec
        Start 5: color_cmd
    5/7 Test #5: color_cmd ........................   Passed    0.07 sec
        Start 6: undo_cmd
    6/7 Test #6: undo_cmd .........................   Passed    0.06 sec
        Start 7: redo_cmd
    7/7 Test #7: redo_cmd .........................***Failed  Required regular expression not found. Regex=[OK
    ]  0.07 sec

    86% tests passed, 1 tests failed out of 7

    Total Test time (real) =   0.43 sec

    The following tests FAILED:
            7 - redo_cmd (Failed)
    Errors while running CTest
    Output from these tests are in: Lab-OOT-Spring-2022/build/Testing/Temporary/LastTest.log
    Use "--rerun-failed --output-on-failure" to re-run the failed cases verbosely.
    ```
    And there will be a file named `fail.log` in the corresponding folder to give more infomation.

    For single folder, `color_cmd` for example, enter
    ```bash
    ctest -R color_cmd
    ```

    or, put the `autotest` binary under the `color_cmd` folder, and run
    ```bash
    ./autotest
    ```

    If the test is passed, the output will be an `OK` string.