#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// есть набор предложений они лежат в двумерном массиве (слов)
// есть структура (может быть хэшмап) хранящая слова для каждого слова есть массив, где оно встретилось
class Word{
public:
    vector<pair<int,int> > location; // sentence + number_in_the_sentence
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
        countS+=newSent;
        countW++;
    }
    for(auto sentence: text){
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
    return 0;
}
