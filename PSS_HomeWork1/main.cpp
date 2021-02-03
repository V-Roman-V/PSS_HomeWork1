#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

// есть набор предложений они лежат в двумерном массиве (слов)
// есть структура (может быть хэшмап) хранящая слова для каждого слова есть массив, где оно встретилось
class Word{
public:
    vector<pair<unsigned int,unsigned int> > location; // sentence + number_in_the_sentence
};

int main()
{
    vector< vector<string> > text(1);
    unordered_map<string, Word> dictionary;
    ifstream file;
    file.open("C:/Works/PSS_HomeWork/PSS_HomeWork1/in.txt");
    string text_in;
    getline(file, text_in);
    stringstream in(text_in);
    string word;
    unsigned int countS = 0;
    unsigned int countW = 0;
    while( in >> word){
        bool newSent = false;
        if(word.back() == '.'){
            word.pop_back();
            newSent = true;
            text.push_back(vector<string>());
        }
        text[countS].push_back(word);
        auto pair = dictionary.emplace(word,Word());
        auto iter = pair.first;
        iter->second.location.push_back(make_pair(countS,countW));
        countS += newSent;
        countW  = newSent?0:(countW+1);
    }
    int cWords;
    file >> cWords; // this action is only needed to remove the number at the beginning

    while(file >> word){
        vector < set <unsigned int> > needUppercase(text.size());
        auto iter = dictionary.find(word);
        if(iter == dictionary.end()){
            cout<<word<<"There is no such word in the text"<<endl;
            continue;
        }
        auto location = iter->second.location; // vector< uint, uint>
        for( auto loc:location)
            needUppercase[loc.first].insert(loc.second);

        cout<<location.size()<<endl;
        for(unsigned int i=0; i<needUppercase.size() ;i++){
            if(needUppercase[i].empty())continue;
            auto up = needUppercase[i].begin();
            for(unsigned int j=0;j<text[i].size();j++){
                string word = text[i][j];
                if(j == *up){
                    up++;
                    transform(word.begin(), word.end(),word.begin(), ::toupper);
                }
                cout<<word<<((j+1<text[i].size())?" ":"");
            }
            cout<<". ";
        }
        cout<<endl;
    }

    // Print for debug
    /*for(auto sentence: text){
        for(auto word: sentence)
            cout<<word<<" ";
        cout<<endl;
    }
    for(auto word: dictionary){
        cout<<word.first<<": ";
        for(auto l: word.second.location)
            cout<<l.first<<"-"<<l.second<<" ";
        cout<<";"<<endl;
    }
    cout<<endl;
    for(unsigned int i=0 ;i < needUppercase.size();i++){
        cout<<i<<": ";
        for(auto w: needUppercase[i])
            cout<<w;
        cout<<";"<<endl;
    }*/
    return 0;
}
