# Sokoban Game

Welcome to Sokoban, a classic puzzle game where the player pushes boxes onto designated storage locations.

## Introduction

Sokoban is a puzzle game where the player controls a character (often represented by the letter "R") that can move horizontally and vertically within a game board containing walls, boxes, and storage locations. The objective is to push all the boxes onto the storage locations to complete each level.

## Features

- Simple and addictive gameplay
- Three levels of difficulty
- Clean and intuitive user interface
- Unlimited undo functionality
- Customizable key bindings

## Installation

To play Sokoban, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/sokoban-game.git
    cd sokoban-game
    ```

2. Compile the source code:

    ```bash
    g++ -o sokoban main.cpp
    ```

3. Run the game:

    ```bash
    ./sokoban
    ```

## Gameplay

- Use the arrow keys (or custom key bindings) to move the player character.
- Push the boxes onto the storage locations to win.
- Avoid getting stuck or trapping boxes in corners, as this can make the level unsolvable.
- Use the "Undo" function to reverse your moves if needed.

## Controls

The default controls are as follows:

- Move Up: Up Arrow / W
- Move Down: Down Arrow / S
- Move Left: Left Arrow / A
- Move Right: Right Arrow / D
- Undo Move: Backspace / U
- Reset Level: R
- Quit Game: Q

You can customize the controls by editing the `controls.cfg` file.

## Levels

Sokoban includes three levels of increasing difficulty:

1. Beginner (Easy)
2. Intermediate (Moderate)
3. Expert (Hard)

Each level presents a new set of challenges and puzzles to solve.

