# 2048 Clone in C++

## Introduction

This repository contains a basic 2048 clone written in C++. This reimplementation was created as a learning exercise in order to experience writing in C++, writing these very sorts of documents, as well as learning how to implement the simple game of 2048.

## Features

To provide an almost identical 2048 experience, the simulacrum tries to reproduce the core gameplay of the original game, including correct merge detection order and the ommission of new tiles whilst being directionally immobile.

## User Interface - I/O

### Visuals - Outputs

The game features a grid-layout terminal based User Interface.

### Controls - Inputs

The controls are configured to the WASD keys and are established within the program by reading the terminal's file descriptor. This unfortunately results in having to depress the Enter key at each individual input for confirmation.

## Getting Started

To get to play the game for yourself, follow these steps:

0. ### Prerequisites

   Make sure you are using a [Bash](https://www.gnu.org/software/bash/)-like shell while executing compile.sh or any of the binaries  
   Make sure you have both [Git](https://github.com/git-guides/install-git) and the [GCC](https://gcc.gnu.org/) C++ compiler installed on your system.

1. ### Clone the Repository:

```bash
git clone https://github.com/Esphyx/2048.git
```

2. ### Compile the Code:
   Using the follow snippet you can compile the source code into an executable binary

```bash
./compile.sh
```

3. ### Run the Code and Play!

```bash
./main
```
