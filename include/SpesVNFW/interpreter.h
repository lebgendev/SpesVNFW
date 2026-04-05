#pragma once
#include <string>
#include <vector>
#include "SpesVNFWCore.h"

void changeBackground(std::string t);
void showCharacter(std::string t);
void displayDialogue(bool overtimeTyping);
void transitionAnimation(std::vector<std::string> t);


class gameState {
private:
    int indentationRatio = 0;
public:
    int currentRow = 0;
    int lastSpace = 0;
    bool dialogueContinue = true;
    std::string lastScene;
    std::vector<Button*> buttons;
    std::vector<std::string> lastDialogue;
    std::vector<std::string> fileContent;
    std::vector<std::string> scenes;
    std::vector<int> scenesRowsIndices;
    std::vector<std::string> choicesParsing(std::string &currentLine);
    std::string oneWord(std::string &currentLine);
    void searchForChoice(std::string t);
    void interpret();
};

void makeButtons(const std::vector<std::string> &t);