#include <iostream>
#include <fstream>
#include <vector>

char UpperToLower(char upperCharacter) {
    char lowerCharacter = upperCharacter + 32;
    return lowerCharacter;
}

std::vector<char> ReadFile(std::string FILE_NAME) {
    std::ifstream dataFS;
    std::vector<char> charactersVector;
    char currentCharacter;

    dataFS.open(FILE_NAME);

    if (!dataFS.is_open()) {
        throw std::runtime_error("cannot open input file " + FILE_NAME);
    }

    dataFS >> currentCharacter;
    while (!dataFS.eof()) {
        charactersVector.push_back(currentCharacter);
        dataFS >> currentCharacter;
    }

    dataFS.close();
    return charactersVector;
}

std::vector<char> GetInput() {
    std::vector<char> charactersVector;
    char currentCharacter;

    while (std::cin >> currentCharacter) {
        charactersVector.push_back(currentCharacter);
    }

    return charactersVector;
}

std::vector<int> MakeAlphabetVector(std::vector<char>& charactersVector) {
    std::vector<int> alphabetCount(26);
    char currentCharacter;
    int alphabetPosition;

    for (int i = 0; i < charactersVector.size(); i++) {
        currentCharacter = charactersVector.at(i);
        if ((currentCharacter >= 65) && (currentCharacter <= 90)) {
            currentCharacter = UpperToLower(currentCharacter);
        }
        if ((currentCharacter >= 97) && (currentCharacter <= 122)) {
            alphabetPosition = currentCharacter - 97;
            alphabetCount.at(alphabetPosition) += 1;
        }
    }

    return alphabetCount;
}

void MostFrequentVowel(std::vector<int>& alphabetCount) {
    int largestCount = 0;
    int largestPosition = 0;
    bool isVowel;
    const std::vector<int> vowelPositions = {0,4,8,14,20};
    std::vector<int> results(2);
    
    // Find most regular vowel and its position in the alphabet
    for (int i = 0; i < alphabetCount.size(); ++i) {
        isVowel = false;
        for (int j = 0; j < vowelPositions.size(); ++j) {
            if (i == vowelPositions.at(j)) {
                isVowel = true;
            }
        }
        if (isVowel && (alphabetCount.at(i) > largestCount)) {
            largestCount = alphabetCount.at(i);
            largestPosition = i;
        }
    }
    
    std::cout << "Most frequent vowel: " << static_cast<char>(largestPosition+97) << " (" << largestCount << " times)" << std::endl;
}

void MostFrequentConsonant(std::vector<int>& alphabetCount) {
    int largestCount = 0;
    int largestPosition = 1;
    bool isConsonant;
    const std::vector<int> vowelPositions = {0,4,8,14,20};
    std::vector<int> results(2);
    
    // Find most regular consonant and its position in the alphabet
    for (int i = 0; i < alphabetCount.size(); ++i) {
        isConsonant = true;
        for (int j = 0; j < vowelPositions.size(); ++j) {
            if (i == vowelPositions.at(j)) {
                isConsonant = false;
            }
        }
        if (isConsonant && (alphabetCount.at(i) > largestCount)) {
            largestCount = alphabetCount.at(i);
            largestPosition = i;
        }
    }
    std::cout << "Most frequent consonant: " << static_cast<char>(largestPosition+97) << " (" << largestCount << " times)" << std::endl;
}

void MostFrequentLetter(std::vector<int>& alphabetCount) {
    int largestCount = 0;
    int largestPosition = 0;
    std::vector<int> results(2);
    
    // Find most regular letter and its position in the alphabet
    for (int i = 0; i < alphabetCount.size(); ++i) {
        if (alphabetCount.at(i) > largestCount) {
            largestCount = alphabetCount.at(i);
            largestPosition = i;
        }
    }
    
    std::cout << "Most frequent letter, overall: " << static_cast<char>(largestPosition+97) << " (" << largestCount << " times)" << std::endl;
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            // Get Input Stream From User
            std::vector<char> charactersVector = GetInput();

            // Get Alphabet Vector
            std::vector<int> alphabetCount = MakeAlphabetVector(charactersVector);

            // Count Characters
            MostFrequentVowel(alphabetCount);
            MostFrequentConsonant(alphabetCount);
            MostFrequentLetter(alphabetCount);
        }
        else if (argc == 2) {
            // Get Input Stream From File
            const std::string FILE_NAME = argv[1];
            std::vector<char> charactersVector = ReadFile(FILE_NAME);

            // Get Alphabet Vector
            std::vector<int> alphabetCount = MakeAlphabetVector(charactersVector);

            // Count Characters
            MostFrequentVowel(alphabetCount);
            MostFrequentConsonant(alphabetCount);
            MostFrequentLetter(alphabetCount);
        }
        else {
            // Error With Parameter List
            throw std::runtime_error("cannot handle parameter list");
        }

        return 0;
    }
    catch (std::runtime_error& e) {
        std::cout << e.what();
        return 1;
    }
    catch (...) {
        return 1;
    }
}