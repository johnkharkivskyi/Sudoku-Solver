
# Sudoku Project

## Project Description

This project is part of the **Programming Paradigms** course.

The goal of the project is to implement a Sudoku processing system step by step throughout the course.
Each laboratory assignment extends the functionality of this project.

Current functionality:

- Reading a Sudoku board
- Printing a Sudoku board
- Validating whether the board configuration is correct
- Solving a board with a simple method
- Solving a board with a backtracking method
- Comparing different solver strategies using basic statistics

This version includes an `analysis.md` file in the `report` folder containing a full report comparing the programming paradigms used throughout the course and providing an overall reflection.

---

## Project Structure

```
Sudoku-Solver/
│
├── src/
│   ├── main.cpp
│   ├── board.cpp
│   ├── solver.cpp
│
├── include/
│   ├── board.h
│   ├── solver.h
│
├── report/
│   ├── analysis.md
│
└── README.md
```

---

## Build Instructions

```
g++ -std=c++17 src/*.cpp -o sudoku
```

---

## Run Instructions

```
./sudoku
```

The program expects a Sudoku board from standard input.

Example input:

Easy board

```
530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079
```

Hard board

```
009586000
000020000
400000683
900650032
060700098
030200704
003000000
620015040
000400050
```
---

## Author

Student name: Ivan Kharkivskyi, КН-1624  
Student ID: ХА14861627
