- [Getting Started](#org5abbc53)
  - [Installation](#orgbf9aa42)
  - [Running](#org86a3e3c)
  - [Compiling](#org1369669)
- [Specifications](#org53f172b)
  - [General information](#orgc2b5570)
  - [Interpreter (VM)](#org404974c)
  - [Compiler](#org2a7dcad)

This is a toy project to introduce myself to interpreters, compilers.

The goal is to create:

-   a Chip8 interpreter, *also refered as 'VM' in the following document (and code)*.
-   a pseudo-assembly chip8 compiler.
-   a graphical mode for the interpreter.


<a id="org5abbc53"></a>

# Getting Started


<a id="orgbf9aa42"></a>

## Installation

```bash
git clone https://github.com/VrncQuentin/Chip8
cd Chip8
make install
chip-8 -h
```

If you get something similar to the following you're good to go.

```
add help
```


<a id="org86a3e3c"></a>

## Running


<a id="org1369669"></a>

## Compiling


<a id="org53f172b"></a>

# Specifications


<a id="orgc2b5570"></a>

## General information

The main ressources I'm following are these three:

-   [Mitt Mikolay's 'Mastering Chip-8' article](http://mattmik.com/files/chip8/mastering/chip8.html)
-   [Mitt Mikolay's technical reference](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Technical-Reference)
-   [Instruction Set](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Instruction-Set)


<a id="org404974c"></a>

## Interpreter (VM)


<a id="org2a7dcad"></a>

## Compiler
