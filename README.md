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
❯ bin/divider_tests

[ RUN      ] TradeTests.TestOne
[       OK ] TradeTests.TestOne (0 ms)
[----------] 1 test from TradeTests (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

## Running the CLI Executable

Without arguments, it prints out its usage:

```bash
❯ bin/divider

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

