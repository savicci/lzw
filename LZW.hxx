#ifndef LZW_HXX
#define LZW_HXX

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
using std::endl;
using std::cout;
using std::cin;

//typ kodowania znakow w strukturze map
using CodeType=std::uint16_t;


class LZW{
    public:

    //kompresuje z standardowego strumienia input i zwraca na output
    //void LZW::compress(std::ifstream input, std::ofstream output)

    //dekompresja wektora kodow
    //void LZW::decompress(std::ifstream input, std::ofstream output)

    //kompresuje z wejscia na wyjscie
    void compress();

    //dekompresuje z wejscia na wyjscie
    void decompress();
};

#endif