#include "wordfinder.h"

WordFinder::WordFinder()
{
    text.resize(1);
}

void WordFinder::addText(const std::string &textIn)
{
    std::stringstream in(textIn);
    std::string wordInText;
    while( in >> wordInText){
        text.back().push_back(wordInText);

        //adds its location to the word in the dictionary
        dictionary[doProperWord(wordInText)].emplace_back(text.size()-1,text.back().size()-1);

        if(isEnd(wordInText.back()))
            text.push_back(std::vector<std::string>());
    }
    text.pop_back();
}

std::string WordFinder::findWord(const std::string& wordToFind)
{
    std::stringstream out;
    auto iter = dictionary.find(doProperWord(wordToFind));
    if(iter == dictionary.end()){
        out<<"word \""<<wordToFind<<"\" never appears in the text\n\n";
        return out.str();
    }

    const auto& location = iter->second; // vector< pair< uint, uint > >
    out<<"word \""<<wordToFind<<"\" was found "<<location.size()<<" times:"<<std::endl<<"\t";

    for(auto locIt = location.begin();locIt!=location.end();){
        unsigned int sentence = locIt->first;
        for(unsigned int j=0;j<text[sentence].size();j++){
            std::string word = text[sentence][j];
            if(locIt!=location.end() && sentence == locIt->first && j == locIt->second){
                locIt++;
                toUpper(word);
            }
            out<<word<<" ";
        }
    }
    out<<"\n\n";
    return out.str();
}

bool WordFinder::isEnd(char c)
{
    return (c=='.' || c=='!' || c=='?');
}

std::string WordFinder::doProperWord(const std::string &word)
{
    std::string pWord = onlyLetters(word);
    toLower(pWord);
    removeS(pWord);
    return pWord;
}

void WordFinder::toUpper(std::string &word)
{
    transform(word.begin(), word.end(),word.begin(), ::toupper);
}

void WordFinder::toLower(std::string &word)
{
    transform(word.begin(), word.end(),word.begin(), ::tolower);
}

void WordFinder::removeS(std::string &word)
{
    if(word.back() == 's')
        word.pop_back();
}

std::string WordFinder::onlyLetters(const std::string &word)
{
    std::string out;
    for(auto c: word)
        if( ('a'<=c && c<='z') || ('A'<=c && c<='Z') || ('0'<=c && c<='9') )
            out+=c;
    return out;
}
