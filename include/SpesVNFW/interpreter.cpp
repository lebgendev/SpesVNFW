#include "interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>


enum class interpretorOperators{
    SCENE,
    BG,
    DIALOGUE,
    SHOW,
    TRANSITION,
    CHOICES
};

std::unordered_map<std::string, interpretorOperators> um = {{"SCENE", interpretorOperators::SCENE},
                                                            {"BG", interpretorOperators::BG},
                                                            {"DIALOGUE", interpretorOperators::DIALOGUE},
                                                            {"SHOW", interpretorOperators::SHOW},
                                                            {"TRANSITION", interpretorOperators::TRANSITION},
                                                            {"CHOICES", interpretorOperators::CHOICES}};

                                                        


void gameState::interpret(){
    if(fileContent.empty()) {
        std::ifstream script("script.spesDX");
        std::string line;
        while(getline(script, line)) {
            fileContent.push_back(line);
        }
    }

    currentRow++;

    std::string currentLine = fileContent[currentRow - 1];
    
    std::istringstream iss(currentLine);
    std::string command;
    if(iss >> command){
        char c = command.back(); 
        if(c == '$'){
            command.pop_back(); 
        }
        
        if(um.find(command) != um.end()){
            interpretorOperators t = um[command];
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
                    displayDialogue();
                    break;
                case interpretorOperators::TRANSITION:
                    transitionAnimation(choicesParsing(currentLine));
                    break;
                case interpretorOperators::CHOICES:
                    makeButtons(choicesParsing(currentLine));
                    break;
            }
        }
    }

    

    std::cout << currentLine << "\n";
    
    

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
            std::cout << c << "\n";
            return c;
        } else {
            std::string skip;
            iss >> skip;
        }
    }
    return nullptr;
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
