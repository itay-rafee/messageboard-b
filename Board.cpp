#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <cmath>
#include "Board.hpp"
using namespace std;

#include "Direction.hpp"

using ariel::Direction;

namespace ariel
{
    const unsigned int zero = 0, one = 1, two = 2, five = 5, ten = 10;

    void Board::set_min_max(unsigned int row, unsigned int col, Direction n, unsigned int len_s)
    {
        //set minimum
        if (row < min_row){min_row = row;}
        if (col < min_col){min_col = col;}

        //set maximum
        if (n == Direction::Vertical)
        {
            if (row + len_s > max_row){max_row = row + len_s;}
            if (col > max_col){max_col = col;}
        }
        else if (n == Direction::Horizontal)
        {
            if (col + len_s > max_col){max_col = col + len_s;}
            if (row > max_row){max_row = row;}
        }
    }

    /* Add the message to board */
    void Board::add_message(unsigned int row, unsigned int col, Direction d, string &s, unsigned int len_s)
    {
        for (char ch : s)
        {
            board[row][col] = ch;
            (d == Direction::Horizontal) ? col++ : row++;
        }
    }

    /* true - if contain message in this location, 
     * false - if not */
    bool Board::contain_message(unsigned int row, unsigned int col)
    {
        bool ans = false;
        it1 = board.find(row);
        if (it1 != board.end())
        {
            it2 = board[row].find(col);
            if (it2 != board[row].end()){ans = true;}
        }
        return ans;
    }

    /* return the number of space that need to row in the board */ 
    unsigned int Board::add_space(unsigned int a)
    {
        unsigned int i = 1;
        while (a / pow(ten, i) >= one)
        {
            i++;
        }
        return i;
    }

    /* post message to the board by location */
    void Board::post(unsigned int row, unsigned int col, Direction n, string s)
    {
        unsigned int len_s = s.size();
        set_min_max(row, col, n, len_s);
        add_message(row, col, n, s, len_s);
    }

    /* read message from the board by location */
    string Board::read(unsigned int row, unsigned int col, Direction d, unsigned int len)
    {
        string ans;
        for (size_t i = 0; i < len; i++)
        {
            if (contain_message(row, col)){ans += board[row][col];}
            else{ans += "_";}
            (d == Direction::Horizontal) ? col++ : row++;
        }
        return ans;
    }

    void Board::show()
    {
        /* print empty board */
        if (board.empty())
        {
            cout << "1: _________\n2: _________\n3: _________\n4: _________\n5: _________" << endl;
            return;
        }

        /* set the maximum and the minimum of the row and the col */
        unsigned int min_r = min(min_row, min_row - one);
        unsigned int min_c = min(min_col, min_col - two);
        unsigned int max_r = max(max_row, max_row + one);
        unsigned int max_c = max(max_col, max_col + two);

        string ans;
        for (unsigned int i = min_r; i < max_r; ++i)
        {
            ans += to_string(i) + ":";
            
            /* add space to the row */
            unsigned int space = add_space(i);
            for (unsigned int j = space; j < five; ++j){ans += " ";}
            
            /* add the rest of the row */
            for (unsigned int j = min_c; j < max_c; ++j)
            {
                if (contain_message(i, j)){ans += board[i][j];}
                else{ans += "_";}
            }
            cout << ans << endl;
            ans = "";
        }
    }
}