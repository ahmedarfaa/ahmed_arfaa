#!/bin/bash

# Test variable replacement
echo "Hello, $USER!"
./hsh <<< "echo Hello, $USER!" > output.txt
diff -b output.txt expected_output.txt

# Test $? variable
./hsh <<< "ls /nonexistent" > output.txt
if [ $? -ne 0 ]; then
    echo "ls failed as expected"
else
    echo "ls succeeded unexpectedly"
fi

# Test $$ variable
./hsh <<< "echo My PID is $$" > output.txt
diff -b output.txt expected_output.txt

# Check exit status
if [ $? -eq 0 ]; then
    echo "All tests passed"
else
    echo "Some tests failed"
fi
