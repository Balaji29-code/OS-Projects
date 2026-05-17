# Threaded Sudoku Validator in C

This project verifies whether a Sudoku board is valid using multithreading in C with POSIX threads (`pthread`).

## Overview

The program validates:

- All 9 rows
- All 9 columns
- All 9 subgrids

Each validation task is executed using separate threads to demonstrate parallelism and concurrency concepts in operating systems.

## Concepts Used

- POSIX Threads (`pthread`)
- Multithreading
- Parallel Task Execution
- Thread Synchronization using `pthread_join`

## How It Works

The Sudoku board is checked using multiple worker threads:

- Row threads validate rows
- Column threads validate columns
- Grid threads validate 3x3 subgrids

Each thread independently verifies whether numbers `1-9` appear exactly once.

If every check passes, the Sudoku is considered valid.

## Compilation

```bash
gcc sudoku.c -pthread