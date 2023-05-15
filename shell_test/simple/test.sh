#!/bin/bash

# Compile the shell program
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# Test basic commands
./hsh <<< "ls"
./hsh <<< "echo hello world"
./hsh <<< "pwd"
./hsh <<< "date"

# Test command with arguments
./hsh <<< "ls -l"
./hsh <<< "echo -n hello world"
./hsh <<< "mkdir testdir"
./hsh <<< "cd testdir"

# Test command with input/output redirection
./hsh <<< "echo hello > output.txt"
./hsh <<< "cat output.txt"
./hsh <<< "echo world >> output.txt"
./hsh <<< "cat output.txt"

# Test command with pipes
./hsh <<< "ls | wc -l"
./hsh <<< "ls | sort"

# Test command with background execution
./hsh <<< "sleep 5 &"
./hsh <<< "echo background job started"

# Clean up test files
rm -f output.txt
rm -rf testdir
