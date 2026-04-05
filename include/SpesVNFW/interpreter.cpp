#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <unordered_map>


enum class interpretorOperators{
    SCENE,
    BG,
    DIALOGUE,
    SHOW,
    TRANSITION,
    CHOICES,
    JUMPTOSCENE,
    CHOICE
};

std::unordered_map<std::string, interpretorOperators> um = {{"SCENE", interpretorOperators::SCENE},
                                                            {"BG", interpretorOperators::BG},
                                                            {"DIALOGUE", interpretorOperators::DIALOGUE},
                                                            {"SHOW", interpretorOperators::SHOW},
                                                            {"TRANSITION", interpretorOperators::TRANSITION},
                                                            {"CHOICES", interpretorOperators::CHOICES},
                                                            {"JUMPTOSCENE", interpretorOperators::JUMPTOSCENE},
                                                            {"CHOICE", interpretorOperators::CHOICE}};


int calculateIndent(std::string line){
    int g = 0;
    for(int i = 0; i < line.length(); i++){
        if(line.at(i) != ' '){
            break;
        }
        g++;
    }
    return g;
}

                                                        


void gameState::interpret(){
    if(fileContent.empty()) {
        std::ifstream script("script.spesDX");
        std::string line;
        int k = 0;
        while(getline(script, line)) {
            if(indentationRatio == 0){
                indentationRatio = calculateIndent(line);
            }
            fileContent.push_back(line);
            std::istringstream iss(line);
            std::string command;
            if(iss >> command){
                if(command == "SCENE"){
                    iss >> std::quoted(command);
                    scenes.push_back(command);
                    scenesRowsIndices.push_back(k);
                }
            }
            k++;
        }
    }

    currentRow++;

    if(currentRow >= fileContent.size()){
        return;
    }

    std::string currentLine = fileContent[currentRow - 1];
    int indent = calculateIndent(currentLine);
    if(indent%indentationRatio != 0){
        return;
    }
    
    if(indent < lastSpace){
        std::string c;
        currentRow--;
        while(true){
            currentRow++;
            currentLine = fileContent[currentRow-1];
            indent = calculateIndent(currentLine);
            if(indent >= lastSpace){
                continue;
            }
            std::istringstream is(currentLine);
            if(is >> c && c == "CHOICE"){
                continue;
            }

            if(indent < lastSpace){
                break;
            }
        }
    }
    
    std::istringstream iss(currentLine);
    std::string command;
    if(iss >> command){
        char c = command.back(); 
        if(c == '$'){
            command.pop_back(); 
        }
        
        if(um.find(command) != um.end()){
            interpretorOperators t = um[command];
            lastSpace = calculateIndent(currentLine);
            switch(t){
                case interpretorOperators::SCENE:
                    lastScene = oneWord(currentLine);
                    interpret();
                    break;
                case interpretorOperators::BG:
                    changeBackground(oneWord(currentLine));
                    if(c != '$'){
                        interpret();
                    }
                    break;
                case interpretorOperators::SHOW:
                    showCharacter(oneWord(currentLine));
                    if(c != '$'){
                        interpret();
                    }
                    break;
                case interpretorOperators::DIALOGUE:
                    lastDialogue = choicesParsing(currentLine);
                    displayDialogue(true);
                    break;
                case interpretorOperators::TRANSITION:
                    transitionAnimation(choicesParsing(currentLine));
                    break;
                case interpretorOperators::CHOICES:
                    makeButtons(choicesParsing(currentLine));
                    break;
                case interpretorOperators::JUMPTOSCENE:{
                    std::string scene = oneWord(currentLine);
                    int it = std::find(scenes.begin(), scenes.end(), scene) - scenes.begin();
                    currentRow = scenesRowsIndices[it];
                    interpret();
                    break;
                }
                case interpretorOperators::CHOICE:
                    interpret();
                    break;
            }
        }
    }
    
    

}





std::vector<std::string> gameState::choicesParsing(std::string &currentLine){
    std::string cur;
    std::istringstream iss(currentLine);
    std::vector<std::string> c;
    while (iss >> std::ws) {
        if (iss.peek() == '"') {
            iss >> std::quoted(cur);
            c.push_back(cur);
        } else {
            iss >> cur;
        }
    }

    return c;
}

std::string gameState::oneWord(std::string &currentLine){
    std::string c;
    std::istringstream iss(currentLine);
    while (iss >> std::ws) {
        if (iss.peek() == '"') {
            iss >> std::quoted(c);
            return c;
        } else {
            std::string skip;
            iss >> skip;
        }
    }
    return nullptr;
}

void gameState::searchForChoice(std::string t){
    while(currentRow <= fileContent.size()){

        currentRow++;
        std::string currentLine = fileContent[currentRow - 1];

        std::cout << currentLine << "\n";
        
        std::istringstream iss(currentLine);
        std::string command;
        if(iss >> command){
            if(um.find(command) != um.end()){
                interpretorOperators k = um[command];
                if(k == interpretorOperators::CHOICE){
                    if(oneWord(currentLine) == t){
                        std::cout << "Choice '" << t << "'found succussfully\n";
                        lastSpace += indentationRatio;
                        interpret();
                        return;
                    }
                }
            }

        }
    }

    std::cerr << "Choice '" << t << "' not found in fileContent.\n";
}