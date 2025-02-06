# CPPND: Capstone Snake Game Example

This is the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## New Features

1. **Player**
   - Enter player name before game starts
   - Display player information after game over
   - File: `player.h`

2. **Thread-safe Moving Obstacle**
   - Moving obstacle that travels horizontally across the screen
   - Game over when snake collides with obstacle
   - File: `obstacle.h/cpp`

## Code Structure
- `main.cpp`: Program entry, initializes game
- `controller.h/cpp`: Input handling
- `game.h/cpp`: Core game logic
- `renderer.h/cpp`: Game rendering
- `snake.h/cpp`: Snake movement and growth
- `obstacle.h/cpp`: Moving obstacle implementation
- `player.h/cpp`: Player info management

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo: `git clone <url>`
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg


## Rubric Points Addressed

### Loops, Functions, I/O (meet 2 criteria)
* functions and control structures.
* accepts user input and processes the input (`main.cpp`, lines 7-12)

### Object Oriented Programming (meet 3 criteria)
* two classes are added to the project with appropriate access specifiers for class members (`obstacle.h/.cpp`, `player.h`)
* Class constructors utilize member initialization lists (`obstacle.cpp`, lines 3-8, `player.h`, lines 7-13) 
* Classes abstract implementation details from their interfaces.


### Memory Management (meet 4 criteria)
* use references (`player.h`, lines 12, `game.cpp`, lines 97, `renderer.cpp`, lines 41).
* use destructors appropriately (`obstacle.cpp`, lines 10)
* use scope / Resource Acquisition Is Initialization (RAII) where appropriate (std::lock_guard).
* use move semantics to move data instead of copying it, where possible (`player.h`, lines 9).

### Concurrency (meet 2 criteria)
* use multithreading
   - Obstacle movement runs in separate thread (`obstacle.cpp`, lines 56)
* use mutex and lock
   - Position protection with mutex (`obstacle.cpp`, lines 22)
   - Thread-safe position updates (`obstacle.cpp`, lines 37)

