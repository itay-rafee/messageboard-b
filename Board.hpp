#include <iostream>
#include <map>
#include <limits>
#include "Direction.hpp"

const unsigned int imax = std::numeric_limits<unsigned int>::max();

namespace ariel
{
    class Board
    {
    private:
        std::map<unsigned int, std::map<unsigned int, char>> board;
        std::map<unsigned int, std::map<unsigned int, char>>::iterator it1;
        std::map<unsigned int, char>::iterator it2;
        unsigned int max_row = 0, max_col = 0;
        unsigned int min_row = imax, min_col = imax;
        void set_min_max(unsigned int row, unsigned int col, ariel::Direction n,unsigned int len_s);
        void add_message(unsigned int row, unsigned int col, ariel::Direction n, std::string &s,unsigned int len_s);
        bool contain_message(unsigned int row, unsigned int col);
        static unsigned int add_space(unsigned int a) ;

    public:
        void post(unsigned int row, unsigned int column, ariel::Direction n, std::string s);
        std::string read(unsigned int row, unsigned int column, ariel::Direction n, unsigned int len);
        void show();
    };
}