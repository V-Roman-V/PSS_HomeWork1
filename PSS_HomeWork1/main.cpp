#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

using WordLocation = vector<pair<unsigned int,unsigned int> >; // sentence + number_in_the_sentence

inline void toUpper(string& word){
    transform(word.begin(), word.end(),word.begin(), ::toupper);
}

inline void toLower(string& word){
    transform(word.begin(), word.end(),word.begin(), ::tolower);
}

string onlyLetters(const string& word){
    string out;
    for(auto c: word)
        if( ('a'<=c && c<='z') || ('A'<=c && c<='Z') || ('0'<=c && c<='9') )
            out+=c;
    return out;
}


void splitSentences(vector< vector<string> >& text, unordered_map<string, WordLocation>& dictionary,const string& text_in){
    text.resize(1);
    stringstream in(text_in);
    string wordInText;
    unsigned int countS = 0;
    unsigned int countW = 0;
    while( in >> wordInText){
        bool newSent = false;
        if(wordInText.back() == '.'){
            newSent = true;
            text.push_back(vector<string>());
        }
        text[countS].push_back(wordInText);

        wordInText = onlyLetters(wordInText);
        toLower(wordInText);
        //adds its location to the word in the dictionary
        dictionary.emplace(wordInText,WordLocation() ).first->second.push_back(make_pair(countS,countW));

        countS += newSent;
        countW  = newSent?0:(countW+1);
    }
    text.pop_back();
}

void findWord(ofstream& out, const vector< vector<string> >& text,const unordered_map<string, WordLocation>& dictionary,string wordToFind){
    wordToFind = onlyLetters(wordToFind);
    toLower(wordToFind);
    auto iter = dictionary.find(wordToFind);
    if(iter == dictionary.end()){
        out<<0<<endl<<wordToFind<<": There is no such word in the text"<<endl;
        return;
    }

    const auto& location = iter->second; // vector< pair< uint, uint > >
    auto locIt = location.begin();// iterator to the beginning of the location array

    out<<location.size()<<endl;
    for(unsigned int i=0; i<text.size() ;i++){
        if(locIt==location.end())break;
        if(i < locIt->first)continue;
        for(unsigned int j=0;j<text[i].size();j++){
            string word = text[i][j];
            if(locIt!=location.end() && i == locIt->first && j == locIt->second){
                locIt++;
                toUpper(word);
            }
            out<<word<<" ";
        }
    }
    out<<endl;
}

int main()
{
    vector< vector<string> > text;
    unordered_map<string, WordLocation> dictionary;

    ifstream file("in.txt");
    if(file.is_open())
        cout<<"opened in.txt file"<<endl;
    else
        cout<<"output file doesn't open"<<endl;

    ofstream out("out.txt");
    if(file.is_open())
        cout<<"opened out.txt file"<<endl;
    else
        cout<<"output file doesn't open"<<endl;

    string text_in;
    getline(file, text_in);

    splitSentences(text,dictionary, text_in);

    int cWords;
    file >> cWords; // this action is only needed to remove the number at the beginning

    string wordToFind;
    while(file >> wordToFind)
        findWord(out,text,dictionary,wordToFind);

    return 0;
}
