
# Sudoku Project

## Project Description

This project is part of the **Programming Paradigms** course.

The goal of the project is to implement a Sudoku processing system step by step throughout the course.
Each laboratory assignment extends the functionality of this project.

Current functionality:

- Reading a Sudoku board
- Printing a Sudoku board
- Validating whether the board configuration is correct

Future assignments will extend this project with additional functionality such as solving Sudoku puzzles.

---

## Project Structure

Example project structure:

```
Sudoku/
│
├── src/
│   ├── main.cpp
│   ├── io.cpp
│   ├── logic.cpp
│
├── include/
│   ├── types.h
│   ├── io.h
│   ├── logic.h
│
└── README.md
```

---

## Build Instructions

Example using **g++**:

```
g++ -std=c++17 src/*.cpp -o sudoku
```

If you are using another compiler or build system, update this section accordingly.

---

## Run Instructions

Example:

```
./sudoku
```

The program expects a Sudoku board from standard input.

Example input:

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

---

## Author

Student name: Ivan Kharkivskyi, КН-1624  
Student ID: ХА14861627
