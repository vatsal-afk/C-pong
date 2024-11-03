# C-Pong

A simple Pong game built with C and GTK+ 3.0. This project uses either a `Makefile` or `Meson` for build automation, allowing you to compile and run the game in an easy and modular way.

## Features

- Simple Pong gameplay
- Implemented using GTK+ 3.0 for a graphical interface
- Supports paddle movement, ball collision, and basic game mechanics

## Requirements

- GCC
- GTK+ 3.0
- Meson (for Meson build option)

To install GTK+ 3.0 on Ubuntu, use:

```bash
sudo apt update
sudo apt install libgtk-3-dev
```

For Meson, install it with:

```bash
sudo apt install meson
```

## Setup and Build

### Option 1: Using Makefile

Clone the repository and navigate to the project directory:

```bash
git clone <repository_url>
cd C-pong
```

Build the project:

```bash
make
```

Run the game:

```bash
make run
```

To clean up the build files:

```bash
make clean
```

### Option 2: Using Meson

Set up the build directory:

```bash
meson setup build
```

Compile the project:

```bash
meson compile -C build
```

Run the game:

```bash
./build/C-pong
```

To clean up build files:

```bash
meson compile -C build --clean
```

## Game Controls

- Paddle 1: Use the Up and Down arrow keys
- Paddle 2: Use the W and S keys

### Summary

This setup provides a dual-build system with instructions for both `Makefile` and `Meson`.