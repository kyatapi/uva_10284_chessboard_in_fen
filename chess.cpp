#ifndef ONLINE_JUDGE
#include "test_cases.h"
extern void run_test(int argc, char **argv);
#else
inline void run_test(int argc, char **argv) {}
#endif // !ONLINE_JUDGE

#include "chess.h"

using namespace std;

istream & operator >> (istream &is, chessboard &rhs) {
    static const string VALID_CHESS_LETTERS("pnbrqkPNBRQK");

    for (unsigned int y = 0; y < chessboard::CHESS_BOARD_SIZE; ++y) {
        string row;
        getline(is, row, '/');
        size_t x = 0;
        for (char chess : row) {
            if (isdigit(chess)) {
                x += (chess - '0');
            }
            else if (VALID_CHESS_LETTERS.find(chess) >= 0) {
                rhs.m_squares[x][y].chess = chess;
                x++;
            }
        }
    }
    return is;
}

const map<char, function<void(size_t, size_t, vector<vector<chessboard::square>>&)>> chessboard::ATTACK_PATTERNS = {
    {'k', [](size_t x, size_t y, vector<vector<chessboard::square>>& squares) {
        squares[x - 1][y].attacked_count++;
        squares[x][y - 1].attacked_count++;
        squares[x + 1][y].attacked_count++;
        squares[x][y + 1].attacked_count++;
        squares[x - 1][y - 1].attacked_count++;
        squares[x + 1][y - 1].attacked_count++;
        squares[x - 1][y + 1].attacked_count++;
        squares[x + 1][y + 1].attacked_count++;
    }}
};

size_t chessboard::calculate_unattacked_count() {
    for (size_t y = 0; y < CHESS_BOARD_SIZE; ++y) {
        for (size_t x = 0; x < CHESS_BOARD_SIZE; ++x) {
            if (m_squares[x][y].chess) {
                ATTACK_PATTERNS.at(tolower(m_squares[x][y].chess))(x, y, m_squares);
            }
        }
    }

    size_t unattacked = 0;
    for (size_t x = 0; x < CHESS_BOARD_SIZE; ++x) {
        unattacked += count_if(m_squares[x].begin(), m_squares[x].end(), [](square s) { return s.attacked_count == 0; });
    }
    return unattacked;
}

int main(int argc, char** argv) {
    run_test(argc, argv);
    return 0;
}