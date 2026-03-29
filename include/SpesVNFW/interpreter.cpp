#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<std::string> gameState::choicesParsing(std::string &currentLine){
    std::string cur;
    std::istringstream iss(currentLine);
    std::vector<std::string> c;
    while(iss >> std::quoted(cur)){
        c.push_back(cur);
    }
    return c;
}

std::vector<std::string> gameState::threeParsing(std::string &currentLine) {
    std::string author, dialogue, expression, background;
    std::istringstream iss(currentLine);
    std::vector<std::string> textVec;

    if (iss >> std::quoted(author)) {
        textVec.push_back(author);
    } else return textVec;

    if (iss >> std::quoted(dialogue)) {
        textVec.push_back(dialogue);
    } else return textVec;

    if (iss >> std::quoted(expression)) {
        if (!expression.empty())
            textVec.push_back(expression);
    }

    if (iss >> std::quoted(background)) {
        if (!background.empty())
            textVec.push_back(background);
    }



    return textVec;
}



void gameState::interpret(Screen &sc){
    if(fileContent.empty()) {
        std::ifstream script("script.spesDX");
        std::string line;
        while(getline(script, line)) {
            fileContent.push_back(line);
        }
    }

    currentRow++;

    std::string currentLine = fileContent[currentRow - 1];
    int j;
    for(int i = 0; i < currentLine.length(); i++){
        if(currentLine[i] == ' '){
            continue;
        }
        j = i;
        break;
    }



    if(currentLine.substr(j) == "INPUT:"){
        currentRow++;
        //std::vector<std::string> choices = choicesParsing(fileContent[currentRow - 1]);
        
    }

    

    std::cout << currentLine << "\n";
    displayDialogue(sc, threeParsing(currentLine));
    

}