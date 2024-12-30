# Trade-lab

Exchange data aggregation tool.

## Building

To build this project, follow these steps:

```
rm -rf build && mkdir build
git submodule init && git submodule update
cd build
cmake ..
make && make install
cd ..
```

## Running Tests

After building, you can run the tests:

```
./bin/tests
```

## Running the application

You can run the application:

```
./bin/trade-lab
```

## Debugging and Coverage

For debugging purposes, you can build with debug information using:

```
rm -rf build && mkdir build
git submodule init && git submodule update
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make && make install
cd ..
```

To check test coverage, use:

```
make trade-lab_coverage
```

The coverage result will be available in `build/coverage`.
