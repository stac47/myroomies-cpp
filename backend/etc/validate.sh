#! /usr/bin/env zsh

echo "Clean up"
echo "--------"
scons --compile-tests --toolchain=clang -Q -c
scons --compile-tests --build-exe -Q -c

echo "\n----------------------"
echo "Compiling with clang++"
echo "----------------------"
scons --compile-tests --toolchain=clang -j9 -Q
if [[ $? -ne 0 ]]; then exit 1; fi

echo "\n------------------"
echo "Compiling with gnu"
echo "------------------"
scons --compile-tests -j9 -Q
if [[ $? -ne 0 ]]; then exit 1; fi

echo "\n--------------------------"
echo "Building binaries with gnu"
echo "--------------------------"
scons --compile-tests --build-exe -Q
if [[ $? -ne 0 ]]; then exit 1; fi

echo "\n------------------"
echo "Running unit tests"
echo "------------------"
./myroomies-unittest-gnu
if [[ $? -ne 0 ]]; then exit 1; fi

echo "\n------------------------"
echo "Running regression tests"
echo "------------------------"
cd test/regression
python3 -m unittest
if [[ $? -ne 0 ]]; then exit 1; fi
cd -

