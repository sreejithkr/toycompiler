#!/bin/bash

# Check if no arguments are provided
if [ $# -eq 0 ]; then
    echo "No arguments provided."
    exit 1
fi

# Switch case to handle different arguments
case "$1" in
    "build")
        echo "Building..."
        make -C ./src  clean
        make -C ./src  
        # Add your build commands here
        ;;
    "run")
        echo "Running..."
        ./out/main ./testdir/test.c
        # Add your run commands here
        ;;
    *)
        echo "Invalid argument: $1"
        exit 1
        ;;
esac

