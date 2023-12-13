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

Divider © 2018 Monkey Claps Inc.

Usage:
	divider <numerator> <denominator>

Description:
	Computes the result of a fractional division,
	and reports both the result and the remainder.
```

But with arguments, it computes as expected the denominator:

```bash
❯ bin/divider 112443477 12309324

Divider © 2018 Monkey Claps Inc.

Division : 112443477 / 12309324 = 9
Remainder: 112443477 % 12309324 = 1659561
```

