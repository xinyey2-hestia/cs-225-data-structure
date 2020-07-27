/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"


using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
      if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
          if (word.length()>=3){
          string first = word.substr(1);
          string firstc = word.substr(0,1);
          string second = word.substr(2);
          second = firstc +second;

          bool same = d.homophones(first,word);
          bool two  = d.homophones(second,word);
          if (same&&two){
            tuple<string,string,string> current(word,first,second);
            ret.push_back(current);
          }
        }
    }
}

    return ret;
}
