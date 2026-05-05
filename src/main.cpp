#include <iostream>
#include "../include/board.h"
#include "../include/solver.h"

int main() {
    SudokuBoard board;

    std::cout << "Input 9 lines with 9 digits each, where 0 represents an empty cell (no spaces):\n";
    try {
        board.read();
    } catch (const std::exception& e) {
        std::cout << "Error reading board: " << e.what() << "\n";
        return 1;
    }

    std::cout << "\nPrinted Sudoku Board:\n";
    board.print();

    if (!board.isValid()) {
        std::cout << "This Sudoku board is invalid\n";
        return 0;
    }

    std::cout << "This Sudoku board is valid\n";

    Solver* baselineSolver = new BacktrackingSolver();
    Solver* mrvSolver = new MRVSolver();
    Solver* mrvPropSolver = new MRVPropagationSolver();

    std::cout << "\n--- Baseline Solver ---\n";
    auto baselineResult = baselineSolver->solve(board);
    if (baselineResult) {
        std::cout << "Solved successfully.\n";
        SolverStats stats = baselineSolver->getStats();
        std::cout << "Recursive calls: " << stats.recursiveCalls << "\n";
        std::cout << "Branches tried: " << stats.branchesTried << "\n";
    } else {
        std::cout << "Failed to solve.\n";
    }

    std::cout << "\n--- MRV Solver ---\n";
    auto mrvResult = mrvSolver->solve(board);
    if (mrvResult) {
        std::cout << "Solved successfully.\n";
        SolverStats stats = mrvSolver->getStats();
        std::cout << "Recursive calls: " << stats.recursiveCalls << "\n";
        std::cout << "Branches tried: " << stats.branchesTried << "\n";
    } else {
        std::cout << "Failed to solve.\n";
    }

    std::cout << "\n--- MRV + Propagation Solver ---\n";
    auto mrvPropResult = mrvPropSolver->solve(board);
    if (mrvPropResult) {
        std::cout << "Solved successfully.\n";
        SolverStats stats = mrvPropSolver->getStats();
        std::cout << "Recursive calls: " << stats.recursiveCalls << "\n";
        std::cout << "Branches tried: " << stats.branchesTried << "\n";
    } else {
        std::cout << "Failed to solve.\n";
    }

    if (mrvPropResult) {
        std::cout << "\nFinal Solved Board:\n";
        mrvPropResult->print();
    }

    delete baselineSolver;
    delete mrvSolver;
    delete mrvPropSolver;

    return 0;
}
