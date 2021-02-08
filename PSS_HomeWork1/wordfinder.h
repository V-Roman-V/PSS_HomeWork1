#ifndef WORDFINDER_H
#define WORDFINDER_H
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>


using WordLocation = std::vector<std::pair<unsigned int,unsigned int> >; // sentence + number_in_the_sentence

class WordFinder
{
public:
    WordFinder();
    void addText(const std::string& in_text);
    void findWord(std::ofstream& out,std::string wordToFind);

private:
    std::vector< std::vector<std::string> > text;
    std::unordered_map<std::string, WordLocation> dictionary;

    void toUpper(std::string& word);
    void toLower(std::string& word);
    std::string onlyLetters(const std::string& word);
};

#endif // WORDFINDER_H
