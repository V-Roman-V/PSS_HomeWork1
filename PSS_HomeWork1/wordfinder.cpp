#include "wordfinder.h"

WordFinder::WordFinder()
{
    text.resize(1);
}

void WordFinder::addText(const std::string &text_in)
{
    std::stringstream in(text_in);
    std::string wordInText;
    unsigned int countS = 0;
    unsigned int countW = 0;
    while( in >> wordInText){
        bool newSent = false;
        if(wordInText.back() == '.'){
            newSent = true;
            text.push_back(std::vector<std::string>());
        }
        text[countS].push_back(wordInText);

        //adds its location to the word in the dictionary
        dictionary[doProperWord(wordInText)].push_back(std::make_pair(countS,countW));

        countS += newSent;
        countW  = newSent?0:(countW+1);
    }
    text.pop_back();
}

void WordFinder::findWord(std::ofstream &out, std::string wordToFind)
{
    auto iter = dictionary.find(doProperWord(wordToFind));
    if(iter == dictionary.end()){
        out<<"the word \""<<wordToFind<<"\" never appears in the text\n\n";
        return;
    }

    const auto& location = iter->second; // vector< pair< uint, uint > >
    auto locIt = location.begin();// iterator to the beginning of the location array

    out<<"word \""<<wordToFind<<"\" was found "<<location.size()<<" times:"<<std::endl<<"\t";

    for(unsigned int i=0; i<text.size() ;i++){
        if(locIt==location.end())break;
        if(i != locIt->first)continue;
        for(unsigned int j=0;j<text[i].size();j++){
            std::string word = text[i][j];
            if(locIt!=location.end() && i == locIt->first && j == locIt->second){
                locIt++;
                toUpper(word);
            }
            out<<word<<" ";
        }
    }
    out<<"\n\n";
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
