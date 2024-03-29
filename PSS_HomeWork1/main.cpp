#include <iostream>
#include <fstream>
#include <string>
#include "wordfinder.h"
using namespace std;

int main()
{
    WordFinder wf;

    ifstream file("in.txt");
    cout<<(file.is_open()?"opened in.txt file":"input file doesn't open")<<endl;
    ofstream out("out.txt");
    cout<<(out.is_open()?"opened out.txt file":"output file doesn't open")<<endl;

    string textIn;
    getline(file, textIn);

    wf.addText(textIn);

    int cWords;
    file >> cWords;
    string wordToFind;
    while((file >> wordToFind) && cWords--)
        out << wf.findWord(wordToFind);

    file.close();
    out.close();
    return 0;
}
