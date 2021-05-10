# Exampls and Tests

This folder contains an example program and tests for the goldtest stream comparer.

## Example Program

The example program shows how one might test a class using this extension. The class `goldtest::example::FileWriter` simply writes a paragraph of text to a file whose filename is provided. The test for this class in `example/tests/` runs a gold test comparing this generated file to the `.gold` file in that same directory. 

The CMake target to build this example program is `goldtest_example`. Building this target will also move all `.gold` files to the CMake build directory (in a subdirectory called `test_data/`) so the tests can run properly.

## Tests

The tests will check the operation of the `goldtest::GoldStreamEvaluator` class if you are having issues.
