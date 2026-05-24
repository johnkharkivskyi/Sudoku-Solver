# Lab 8 Report: Sudoku Solver Architecture

Student: Ivan Kharkivskyi  
Group: KN-1624

## Project overview

This project is a Sudoku solver developed during the Programming Paradigms course. The same basic problem was changed several times to try different ways of structuring code. In the final version the program can read a Sudoku board, validate it, solve it with several strategies, and print simple statistics about the solving process.

The most important stages were not individual commits, but the larger design changes:

- procedural implementation
- object-oriented implementation
- polymorphic solver design
- functional-style solver logic
- optimized search with heuristics

Looking at the project this way is more useful than describing every small change. The main question is how each approach affected readability, extensibility, correctness, and performance.

## Procedural stage

The first version used a simple data structure for the Sudoku board and separate functions for logic. The board was basically a 9 by 9 array, and functions checked rows, columns, boxes, and the whole board.

This was the easiest way to begin. There was no class hierarchy and no extra abstraction. For a small validator it was readable enough: data was passed into functions, and the functions returned whether the board was valid.

The problem was that the board representation was too exposed. Since the grid was public data, any part of the code could change it directly. That makes the code simple, but also fragile. Every function has to remember the exact representation and handle indexes correctly.

The procedural version was good for learning the problem, but not very good as a base for several solver strategies.

## Object-oriented stage

The next design step was to make `SudokuBoard` a real class. Reading, printing, cell access, and validation became methods of the board. The grid became private, and validation helpers became internal implementation details.

This made the code more organized. A board now knew how to check itself, and the rest of the program did not need to know how validation was implemented. This is a better match for the problem because row, column, and box rules are part of the board's behavior.

The object-oriented version also made invalid access easier to control. Instead of allowing any code to write into the array, the board exposes `getCell` and `setCell`. In the final version these methods check bounds and valid digit values. That is a small thing, but it gives the rest of the program a safer interface.

This stage improved code structure the most. It separated board responsibility from program flow. `main.cpp` could focus on reading input and showing output, while `SudokuBoard` handled Sudoku-specific validation.

## Polymorphic solver design

After the project became a solver and not only a validator, the next issue was how to support more than one solving strategy. A single hard-coded solver would work, but it would make comparison awkward.

The solution was a base `Solver` interface with a common `solve` method. Then different strategies could be implemented as separate classes. In the current project the solver classes include baseline backtracking, simple propagation, MRV, and MRV with propagation.

This design made the project easier to extend. The program can treat solvers through the same interface, while each class keeps its own algorithm. Adding a new solver no longer requires changing the board class or rewriting the whole program.

The trade-off is extra structure. For only one solver, an interface is not necessary. But once the project compares different strategies, polymorphism is useful. It gives the program a stable shape: all solvers receive a board and either return a solved board or fail.

## Functional-style solver logic

The functional-style stage changed how the recursive solver handled board state. Earlier backtracking modified the same board directly, tried a value, and then reset the cell if the path failed. That approach is common and efficient, but it depends on carefully undoing every change.

The later version makes each move produce a new board:

```cpp
SudokuBoard BacktrackingSolver::applyMove(const SudokuBoard& board, const Move& move) const {
    SudokuBoard next = board;
    next.setCell(move.row, move.col, move.value);
    return next;
}
```

The solver also returns `std::optional<SudokuBoard>`. This makes failure explicit. A recursive branch either returns a solved board or `std::nullopt`.

This approach made the recursive code easier to reason about. Each branch receives its own board state, so a failed branch cannot accidentally damage another branch. The code also became more like a sequence of transformations:

- generate possible moves
- filter valid moves
- apply a move
- recurse on the new board

The downside is that boards are copied more often. For this project that is acceptable because a Sudoku board is small. If the state was much larger, I would think more carefully about performance. Still, for this solver, the clarity was worth it.

## Optimization stage

The final stage focused on performance. The baseline backtracking solver chooses the first empty cell and tries valid digits. This works, but it can waste time exploring weak choices.

The optimized version adds MRV, or Minimum Remaining Values. Instead of taking the first empty cell, it scans for the empty cell with the fewest valid candidates. This usually reduces the search tree because the solver handles the most constrained cells first.

The project also adds propagation. Before recursive search, the solver repeatedly fills cells that have only one possible value. If this solves part of the board before branching, the recursive search becomes much smaller.

This stage shows why the earlier architecture mattered. MRV was added by changing candidate generation, not by rewriting the whole solver. Propagation could reuse the existing board validation and solving structure. The optimizations were still extra complexity, but the code had places where that complexity could fit.

## Code structure and responsibilities

The final project has a clearer structure than the early versions:

```text
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

The board code is responsible for representation and validation. Solver code is responsible for search strategies. `main.cpp` is responsible for input, output, and comparing solvers.

This separation is important. If board validation and solving logic were mixed together, it would be harder to add new strategies. If input and output were mixed into the solver, it would be harder to test the algorithms. The current structure is not huge, but each file has a clear purpose.

## Extensibility

The procedural version was not very extensible. It was fine for validation, but adding several solver strategies would probably lead to many separate functions and duplicated control flow.

The object-oriented and polymorphic versions are much better for extension. The board has a stable interface, and solvers can be added as separate classes.

The functional-style decomposition also helps extension. Since move generation, filtering, validation, and applying moves are separated, it is easier to replace one part without changing everything else.

If I added another solver now, I would probably keep the same interface and add a new class. For example, a future solver could order digits differently. The current architecture would support that reasonably well.

## Readability

The procedural version was easiest to read at the very beginning. There were fewer files and fewer concepts. For a small validator, that is an advantage.

The final version is easier to understand as a complete project. It has more classes, but the responsibilities are clearer. A reader can look at `board.cpp` for board rules and `solver.cpp` for solving strategies.

The hardest part to read is the optimized solver logic, because MRV and propagation add more conditions before recursion. That is the normal cost of optimization. The benefit is that the solver does much less unnecessary work.

So the readability trade-off is simple:

- procedural code is short and direct
- object-oriented code is more organized
- functional-style recursion is safer to reason about
- optimized code is faster, but less minimal

For this project, the final version is a good balance.

## Testability

The later designs are easier to test. `SudokuBoard::isValid` can be tested independently from any solver. The solver classes can be tested with the same input board because they share the same interface.

The functional-style solver also helps with testing because the input board is treated as immutable. A test can check that the original board was not changed after calling `solve`.

The current repository does not include automated tests, which is a weakness. If I continued the project, I would add tests for:

- valid and invalid rows
- valid and invalid columns
- valid and invalid 3 by 3 boxes
- a board solved by propagation
- a board that needs backtracking
- invalid or unsolvable input

This would be useful because the project went through several refactors.

## Performance comparison

I ran the two sample boards from the README. The program reports recursive calls and tried branches. These are not exact time measurements, but they show the size of the search.

Easy board:

- baseline backtracking: 4209 recursive calls, 4208 branches
- MRV: 52 recursive calls, 51 branches
- MRV with propagation: 1 recursive call, 0 branches

Hard board from the README:

- baseline backtracking: 592 recursive calls, 591 branches
- MRV: 52 recursive calls, 51 branches
- MRV with propagation: 2 recursive calls, 1 branch

MRV made a major difference. It reduced the number of branches because the solver no longer picked cells in simple row order. Propagation helped even more on these examples because many cells could be filled before recursive search.

One interesting result is that the baseline solver used fewer calls on the hard board than on the easy board. That does not mean the second puzzle is generally easier. It means this exact puzzle and digit order happened to lead the baseline solver to a solution faster. This is why heuristics are useful: they make performance less dependent on lucky ordering.

## Reflection

The most natural paradigm for this project was object-oriented programming. A Sudoku board fits well as an object because it has data and clear rules. Hiding the grid and giving the board methods made the code feel more controlled.

The functional-style part was the most useful for recursion. At first it felt less direct than changing the board in place, but it made backtracking safer. Each recursive path has its own board state, and failure is represented directly with `std::optional`.

The hardest paradigm to apply was the functional-style one. The idea itself is clear, but in C++ it takes more discipline to avoid mutation. Backtracking is usually written by changing the board and then undoing the change, so rewriting it as a sequence of new board states felt less natural at first. It also required more small helper functions, such as move generation, filtering, and applying moves.

The optimization stage was the most practical one. It showed that a correct algorithm is not always enough. Backtracking works, but MRV and propagation make it behave much better.

The main lesson is that the paradigms are not competing solutions. The final project uses several of them together. Object-oriented design organizes the domain, polymorphism makes strategies replaceable, functional-style code makes recursive search cleaner, and heuristics improve performance.

In a real project I would use the same combination of ideas: keep the domain model object-oriented, put different algorithms behind a common interface, keep recursive search as close to immutable as practical, and use heuristics when simple brute force becomes too slow. The useful lesson is not that one paradigm won, but that each one solved a different problem in the project.
