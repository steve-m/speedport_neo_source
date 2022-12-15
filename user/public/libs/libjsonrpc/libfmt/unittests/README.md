# Introduction

A unit test produce file called "result". This output is compared to a file called
"expected". It is then concluded whether the test passes.


# Basic usage

Target description:

* `make` or `make all` builds and runs all the tests
* `make build` builds all the tests
* `make run` runs all the tests (does not build)
* `make TESTS="name1 name2"` builds and runs a set of tests


# Customization

* `TIMEOUT` parameter can be overridden to change maximum execution time
* `VG` parameter can be overriden to `no` to disable Valgrind checks.
Any other value will be treated as Valgrind parameters.
