#!/bin/sh
gcc -c stack1.c stack2.c
gcc stack1.c stack2.c calculator.c -lm

