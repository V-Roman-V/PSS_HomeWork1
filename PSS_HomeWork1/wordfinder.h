#ifndef WORDFINDER_H
#define WORDFINDER_H
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>


using WordLocation = std::vector<std::pair<unsigned int,unsigned int> >; // sentence + number_in_the_sentence

class WordFinder
{
public:
    WordFinder();
    void addText(const std::string& textIn);
    std::string findWord(const std::string& wordToFind);

private:
    std::vector< std::vector<std::string> > text;
    std::unordered_map<std::string, WordLocation> dictionary;

    inline bool isEnd(char c);

    std::string doProperWord(const std::string& word);
    void toUpper(std::string& word);
    void toLower(std::string& word);
    void removeS(std::string& word);
    std::string onlyLetters(const std::string& word);
};

#endif // WORDFINDER_H
