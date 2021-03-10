#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

const std::unordered_map<std::string, std::pair<int,int>> POSITIONS = { 
    {"tl",{0,0}},
    {"tm",{0,1}},
    {"tr",{0,2}},
    {"ml",{1,0}},
    {"mm",{1,1}},
    {"mr",{1,2}},
    {"bl",{2,0}},
    {"bm",{2,1}},
    {"br",{2,2}}
};

const char VALUES[3] = { ' ', 'x','o' };

class Board {
private:
    int _size;
    vector<vector<unsigned char>> _board;
public:
    Board(int size) : _board(size, vector<unsigned char>(size)) {
        _size = size;
    }

    void printBoard() {
        //Do print board logic
        for (int i = 0; i < _size; i++) {
            cout << std::string((_size * 4) + 1, '-') << endl;;
            cout << "| ";
            for (int j = 0; j < _size; j++) {
                cout << VALUES[_board[i][j]] << " | ";
            }
            cout << endl;
        }
        cout << std::string((_size * 4) + 1, '-') << endl;;
    }

    void setBit(int x, int y, char bit) {
        _board[x][y] = bit;
    }

    void resetBoard() {
        _board = vector<vector<unsigned char>>(_size, vector<unsigned char>(_size));
    }
    vector<vector<unsigned char>> getBoard() {
        return _board;
    }
};

enum GameStatus {
    ONGOING,
    ENDED
};

class Game {
private:
    int _size;
    Board _board;
    GameStatus _gameStatus;
    char _player = 'x';
    vector<int> rows;
    vector<int> cols;
    int diags = 0;
    int antidiags = 0;

    int loop() {
        std::string input;
        cout << "What do you want to play? (" << _player << ") ";
        std::cin >> input;
        if (input == "exit") return -1;
        auto value = POSITIONS.find(input);
        if (value == POSITIONS.end()) {
            cout << "\"" << input << "\" is an invalid position." << endl;
            return 0;
        }
        if (_board.getBoard()[value->second.first][value->second.second] != 0) {
            cout << "\"" << input << "\" is not empty." << endl;
            return 0;
        }
        handleSetBit(value->second.first, value->second.second);
        int checkWinResult = checkWin((int) value->second.first, (int) value->second.second);
        switch (checkWinResult) {
        case 0:
            cout << "It's a draw!" << endl;
            _gameStatus = ENDED;
            break;
        case 1:
            cout << "X has won!" << endl;
            _gameStatus = ENDED;
            break;
        case 2:
            cout << "O has won!" << endl;
            _gameStatus = ENDED;
        case -1:
            break;
        }
        switchPlayer();
        return 0;
    }
    int checkWin(int x, int y) {
        vector<vector<unsigned char>> board = _board.getBoard();
        int innerResult = 0;
        for (int i = 0; i < _size; i++) {
            if (std::all_of(board[i].cbegin(), board[i].cend(), [](unsigned char j) { return j > 0; })) innerResult++;
        }

        if (innerResult == _size) return 0;
        else if (rows[x] == _size || cols[y] == _size || diags == _size || antidiags == _size) return 1;
        else if (rows[x] == -1 * _size || cols[y] == -1 * _size || diags == -1 * _size || antidiags == -1 * _size) return 2;

        return -1;
    }
    void switchPlayer() {
        if (_player == 'x') _player = 'o';
        else _player = 'x';
    }
    void handleSetBit(int x, int y) {
        if (_player == 'x') {
            _board.setBit(x, y, 1);
            rows[x]++;
            cols[y]++;
            if (x == y) diags++;
            if (x + y + 1 == _size) antidiags++;
        }
        else {
            _board.setBit(x, y, 2);
            rows[x]--;
            cols[y]--;
            if (x == y) diags--;
            if (x + y + 1 == _size) antidiags--;
        }
        return;
    }
public:
    Game(int size): _board(size) {
        rows = vector<int>(size);
        cols = vector<int>(size);
        _size = size;
    }

    void start() {
        // Do start game logic
        cout << "Starting game..." << endl;
        _board.printBoard();
        _gameStatus = ONGOING;
        while (_gameStatus == ONGOING) {
            if (loop() == -1) break;
            _board.printBoard();
        }
        cout << "Ending game..." << endl;
        _gameStatus = ENDED;
        return;
    }

    GameStatus getGameStatus() {
        return _gameStatus;
    }
};

int main()
{
    Game game = Game(3);
    game.start();
    return 0;
}