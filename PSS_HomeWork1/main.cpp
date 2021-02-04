#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// есть набор предложений они лежат в двумерном массиве (слов)
// есть структура хранящая локации для каждого слова встретившегося в массиве

class WordLoc{
public:
    vector<pair<unsigned int,unsigned int> > location; // sentence + number_in_the_sentence
};

inline void toUpper(const string& wordIn, string& wordOut){
    transform(wordIn.begin(), wordIn.end(),wordOut.begin(), ::toupper);
}

inline void toLower(const string& wordIn, string& wordOut){
    transform(wordIn.begin(), wordIn.end(),wordOut.begin(), ::tolower);
}

int main()
{
    vector< vector<string> > text(1);
    unordered_map<string, WordLoc> dictionary;
    ifstream file;
    file.open("C:/Works/PSS_HomeWork/PSS_HomeWork1/in.txt");
    string text_in;
    getline(file, text_in);
    stringstream in(text_in);
    string wordInText;
    unsigned int countS = 0;
    unsigned int countW = 0;
    while( in >> wordInText){
        bool newSent = false;
        if(wordInText.back() == '.'){
            wordInText.pop_back();
            newSent = true;
            text.push_back(vector<string>());
        }
        text[countS].push_back(wordInText);

        toLower(wordInText,wordInText);
        //adds its location to the word
        dictionary.emplace(wordInText,WordLoc()).first->second.location.push_back(make_pair(countS,countW));

        countS += newSent;
        countW  = newSent?0:(countW+1);
    }

    int cWords;
    file >> cWords; // this action is only needed to remove the number at the beginning
    string wordToFind;
    while(file >> wordToFind){
        toLower(wordToFind, wordToFind);
        auto iter = dictionary.find(wordToFind);
        if(iter == dictionary.end()){
            cout<<0<<endl<<wordToFind<<": There is no such word in the text"<<endl;
            continue;
        }

        const auto& location = iter->second.location; // vector< pair< uint, uint > >
        auto locIt = location.begin();// iterator to the beginning of the location array

        cout<<location.size()<<endl;
        for(unsigned int i=0; i<text.size() ;i++){
            if(locIt==location.end())break;
            if(i < locIt->first)continue;
            for(unsigned int j=0;j<text[i].size();j++){
                string word = text[i][j];
                if(locIt!=location.end() && i == locIt->first && j == locIt->second){
                    locIt++;
                    toUpper(word, word);
                }
                cout<<word<<((j+1<text[i].size())?" ":"");
            }
            cout<<". ";
        }
        cout<<endl;
    }
    return 0;
}
