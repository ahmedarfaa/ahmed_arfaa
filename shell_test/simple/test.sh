#!/bin/bash

# Debug output
echo "Current directory: $(pwd)"
echo "Command: ./hsh <<< \"echo Hello, ahmed!\" > output.txt"

# Test command execution
./hsh <<< "echo Hello, ahmed!" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"ls /nonexistent\" > output.txt"

# Test $? variable
./hsh <<< "ls /nonexistent" > output.txt
if [ $? -ne 0 ]; then
    echo "ls failed as expected"
else
    echo "ls succeeded unexpectedly"
fi

# Debug output
echo "Command: ./hsh <<< \"echo My PID is $$\" > output.txt"

# Test $$ variable
./hsh <<< "echo My PID is $$" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"echo $PATH\" > output.txt"

# Test $PATH variable
./hsh <<< "echo $PATH" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"cat < input.txt\" > output.txt"

# Test input/output redirection
echo "Hello, world!" > input.txt
./hsh <<< "cat < input.txt" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"ls | grep Makefile\" > output.txt"

# Test pipes
./hsh <<< "ls | grep Makefile" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"sleep 5 & echo Background process started\" > output.txt"

# Test background processes
./hsh <<< "sleep 5 & echo Background process started" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"echo The date is $(date)\" > output.txt"

# Test command substitution
./hsh <<< "echo The date is $(date)" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"export MY_VAR=hello && echo $MY_VAR\" > output.txt"

# Test environment variables
./hsh <<< "export MY_VAR=hello && echo $MY_VAR" > output.txt
diff -b output.txt expected_output.txt

# Debug output
echo "Command: ./hsh <<< \"alias ll='ls -l' && ll\" > output.txt"

# Test aliases
./hsh <<< "alias ll='ls -l' && ll" > output.txt
diff -b output.txt expected_output.txt

# Check exit status
if [ $? -eq 0 ]; then
    echo "All tests passed"
else
    echo "Some tests failed"
fi

# Clean up
rm hsh output.txt input.txt