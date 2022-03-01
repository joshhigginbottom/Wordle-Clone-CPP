#include <iostream>
#include <fstream>
#include <stdlib.h> // srand
#include <vector>
#include "json.hpp"

//using namespace std;
std::string check_guess(std::string word, std::string guess){

    std::string result = "";
    std::string word_copy = word;
    
    for(int i=0; i < word.size(); i++){
        result = result + " ";
    } 
    
    for(int i=0; i < guess.size(); i++){
        if(guess[i] == word[i]){
            result[i] = 'O';
            word_copy[i] = ' ';
        }
    }

    bool found;

    for(int i=0; i < guess.size() ;i++){

        found = false;

        for(int j=0; j < word.size() ;j++){
            if(guess[i] == word_copy[j]){
                result[i] = 'Q';
                found = true;
            }
        }
        if(!found && word_copy[i] != ' '){
            result[i] = 'X';
        }
    }

    return result;
}

void get_words(){
    std::ifstream i("words.json");
    nlohmann::json j;
    i >> j;
    std::cout << j["Words"]["A"];
}

int play_wordle(){
    
    std::string word = "pound";
    std::string result;
    std::string guess;
    int tries = 4;


    
    while(tries > 0){

        bool win = true;

        std::cout << "Make a guess: ";
        std::cin >> guess;
        //guess_vector = string_to_vector(guess);

        if(word.size() != guess.size()){
            char str[256];
            snprintf(str, sizeof str, "%zu", word.size());

            std::cout << "Word is " << str << " letters long" << std::endl;
            continue;
        }

        result = check_guess(word, guess);
        for(auto letter: guess){
            std::cout << letter;
        }
        std::cout << std::endl;
        
        for(auto letter: result){
            std::cout << letter;
            if(letter != 'O'){
                win = false;
            }
        }
        std::cout << std::endl;

        if(win){
            std::cout << "You win!" << std::endl;
            return 0;
        }
        tries--;

        //srand(time(NULL));
        //int amount = rand() % 100;
    }

    std::cout << "You Lose!" << std::endl;

    return 0;
}

int main(){
    //Play_Wordle();
    get_words();
}