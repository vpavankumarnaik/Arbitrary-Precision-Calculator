# Arbitrary-Precision-Calculator

A C-based implementation of an Arbitrary Precision Calculator capable of performing arithmetic operations on very large integers beyond the limits of standard C data types.

## Overview

This project implements large integer arithmetic using dynamic memory and linked lists. Each digit of a number is stored in a node, allowing calculations on numbers of virtually unlimited size.

## Features

- Addition of large integers
- Subtraction of large integers
- Multiplication of large integers
- Handles numbers larger than built-in C data types
- Linked list based implementation
- Command-line interface

## How It Works

Numbers are stored as linked lists where each node represents a single digit. Arithmetic operations are performed digit-by-digit, similar to manual calculation, handling carry and borrow operations appropriately.

## Project Structure

All files are located in the root directory:

APC/
│
├── main.c          # Program entry point
├── functions.c     # Helper and utility functions
├── operation.c     # Arithmetic operations implementation
├── header.h        # Structure definitions and function declarations
├── README.md
├── LICENSE
└── .gitignore

## Compilation

To compile using gcc:

```bash
gcc *.c -o apc

## Usage

Run the program:

./apc
