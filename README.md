# Trading tool laboratory

High-performance tool for analyzing data from exchanges

## Building Manually

```bash
❯ rm -rf build && mkdir build
❯ git submodule init && git submodule update
❯ cd build
❯ cmake ..
❯ make && make install
❯ cd ..
```
## Running the tests

```bash
❯ bin/tests

[==========] Running 20 tests from 4 test suites.
[----------] Global test environment set-up.

[----------] Global test environment tear-down
[==========] 20 tests from 4 test suites ran. (1 ms total)
[  PASSED  ] 20 tests.

```

## Running the CLI Executable

Without arguments, it prints out its usage:

```bash
❯ bin/trade-lab

Trade-lab © 2023 Rustam Shangareev.

Usage:
        trade-lab <data>

Description:
        Creates the trade class,
        and reports its inside
```

But with arguments, it executes:

```bash
❯ bin/trade-lab 1618920000,100.5,10,1005,1

1618920000,100.5,10,1005,1
```

