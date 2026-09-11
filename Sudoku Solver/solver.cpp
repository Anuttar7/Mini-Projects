#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    bool valid (int num, int i1, int j1, vector<vector<char>>& board){
        for (int i = 0; i < 9; i++){
            if (board[i][j1] == num + '0'){
                return false;
            }
        }
        for (int j = 0; j < 9; j++){
            if (board[i1][j] == num + '0'){
                return false;
            }
        }
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (board[(i1/3)*3 + i][(j1/3)*3 + j] == num + '0'){
                    return false;
                }
            }
        }
        return true;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        f(0, 0, board);
    }
    bool f (int i1, int j1, vector<vector<char>>& board){
        if (j1 == 9){
            j1 = 0;
            i1++;
        }
        if (i1 == 9){
            return true;
        }
        if (board[i1][j1] != '.'){
            if (!f(i1, j1+1, board)){
                return false;
            }
            else{
                return true;
            }
        }

        for (int i = 1; i <= 9; i++){
            if (valid(i, i1, j1, board)){
                board[i1][j1] = i + '0';
                if (!f(i1, j1+1, board)){
                    board[i1][j1] = '.';
                }
                else{
                    return true;
                }
            }
        }
        return false;
    }
};

int main(){
    Solution sol;
    vector<vector<char>> board;

    //Input board. Enter number or '.' (for empty cell) for each cell of Sudoku board you want to solve
    for (int i = 0; i < 9; i++){
        vector<char> temp;
        for (int j = 0; j < 9; j++){
            char c;
            cin >> c;
            temp.push_back(c);
        }
        board.push_back(temp);
    }

    //Solves the sudoku.
    sol.solveSudoku(board);
    
    //Outputs the solved sudoku
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}