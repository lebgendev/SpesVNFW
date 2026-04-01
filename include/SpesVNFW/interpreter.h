#pragma once
#include <string>
#include <vector>
#include "SpesVNFWCore.h"

void changeBackground(std::string t);
void showCharacter(std::string t);
void displayDialogue();
void transitionAnimation(std::vector<std::string> t);


class gameState {
public:
    int currentRow = 0;
    int lastSpace = 0;
    std::string lastScene;
    std::vector<Button*> buttons;
    std::vector<std::string> lastDialogue;
    std::vector<std::string> fileContent;
    std::vector<std::string> choicesParsing(std::string &currentLine);
    std::string oneWord(std::string &currentLine);
    std::vector<std::string> threeParsing(std::string& currentLine);
    void interpret();
};

void makeButtons(const std::vector<std::string> &t);