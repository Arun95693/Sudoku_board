#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 9;

bool isSafe(vector<vector<int>>& board, int row, int col, int num) {
    // Check row and column
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num || board[x][col] == num)
            return false;
    }
    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Find unassigned location
bool findUnassignedLocation(vector<vector<int>>& board, int& row, int& col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Solve using Backtracking
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;
    if (!findUnassignedLocation(board, row, col))
        return true; // Success!

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0; // Backtrack
        }
    }
    return false;
}

// Print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (int r = 0; r < SIZE; r++) {
        if (r % 3 == 0 && r != 0)
            cout << "------+-------+------\n";
        for (int c = 0; c < SIZE; c++) {
            if (c % 3 == 0 && c != 0)
                cout << "| ";
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
}

int main() {
    // 0 represents an empty cell
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Initial Sudoku Board:\n";
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku Board:\n";
        printBoard(board);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
