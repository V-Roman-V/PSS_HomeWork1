# PSS_HomeWork1
A program that reads the text from the file then splits the input text into sentences and returns all sentences that contain the word from the input and make the word UPPERCASE.

## Program description

### How the text is stored:
 The text is stored as a two-dimensional array of words. The first index is the number of the sentence, the second index is the number of the word.
### How the dictionary is stored:
 The dictionary is stored in a HashMap structure.
 The key is a word, the value is an array of all the locations in the text where the word is found. The locations are arranged in sequential order.
  
## Program features
  * The search for all word positions in the text is done on average in a constant time, in the worst case in a linear, because HashMap is used. 
  
  * The search ignores the case of the word.  
    &nbsp;&nbsp;example: if you search "hello" in the text "Hello world!!!", the program will display "HELLO world!!!"  
    
  * The search will highlight multiple words, even if it occurs more than once in the same sentence.  
    &nbsp;&nbsp;example: if you search "hello" in the text "Hello, hello.", the program will display "HELLO, HELLO."  
  * The search ignores all extraneous characters except letters and numbers.  
    &nbsp;&nbsp;example: if you search "you" in the text "If not you, then me", the program will display "If not YOU, then me"  
  * The search ignores plurals and 's of a word.  
    &nbsp;&nbsp;examples:  
        &nbsp;&nbsp;1) if you search "pen" in the text "Where are my pens?", the program will display "Where are my PENS?"  
        &nbsp;&nbsp;2) if you search "it" in the text "It's not mine, I don't know how it got here.", the program will display "IT'S not mine, I don't know how IT got here."
  
        
## How to run the code
 Qt Creator was used as the IDE for this project. If you have it, you will be able to open this project through it.

### Where the source code is located
  main.cpp and other classes are located in the directory:
 > PSS_HomeWork1 
 
### How to execute the code
  Compiled and ready to run .exe file is located in the directory:
 > build-PSS_HomeWork1-Desktop_Qt_5_12_5_MinGW_64_bit-Debug\debug
  
in.txt have to be in the same directory
