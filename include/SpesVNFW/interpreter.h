#pragma once
#include <string>
#include <vector>
#include "SpesVNFWCore.h"


void displayDialogue(Screen &sc, std::vector<std::string> t);


class gameState {
public:
    int currentRow = 0;
    int lastSpace = 0;
    std::vector<std::string> fileContent;
    std::vector<std::string> choicesParsing(std::string &currentLine);
    std::vector<std::string> threeParsing(std::string& currentLine);
    void interpret(Screen &sc);
};
