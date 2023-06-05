#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Функція, яка перевіряє, чи є символ голосним
bool isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Функція, яка перевіряє, чи слово починається і закінчується на приголосну літеру
bool startsAndEndsWithConsonant(const string& word) {
    if (word.empty()) {
        return false;
    }
    char firstChar = tolower(word[0]);
    char lastChar = tolower(word[word.length() - 1]);
    return (!isVowel(firstChar) && !isVowel(lastChar) && isalpha(lastChar));
}

// Функція, яка знаходить найдовше слово в тексті
string findLongestWord(const string& text) {
    string longestWord;
    string word;
    for (char c : text) {
        if (isalpha(c) || c == '\'') {
            word += c;
        }
        else {
            if (word.length() > longestWord.length()) {
                longestWord = word;
            }
            word = "";
        }
    }
    if (word.length() > longestWord.length()) {
        longestWord = word;
    }
    return longestWord;
}

// Функція, яка знаходить слова, які починаються і закінчуються на приголосну літеру
void findWordsStartingAndEndingWithConsonant(const string& text, vector<string>& result) {
    string word;
    for (char c : text) {
        if (isalpha(c) || c == '\'') {
            word += c;
        }
        else {
            if (startsAndEndsWithConsonant(word)) {
                result.push_back(word);
            }
            word = "";
        }
    }
    if (startsAndEndsWithConsonant(word)) {
        result.push_back(word);
    }
}

int main() {
    ifstream inputFile("text.txt");
    if (!inputFile) {
        cout << "Failed to open the input file." << endl;
        return 1;
    }

    // Зчитування тексту з файлу
    string text((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Знаходження найдовшого слова
    string longestWord = findLongestWord(text);
    cout << "Longest word: " << longestWord << endl;

    // Знаходження слів, які починаються і закінчуються на приголосну літеру
    vector<string> wordsStartingAndEndingWithConsonant;
    findWordsStartingAndEndingWithConsonant(text, wordsStartingAndEndingWithConsonant);

    // Запис слів у файл "output.txt"
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cout << "Failed to open the output file." << endl;
        return 1;
    }
    for (const string& word : wordsStartingAndEndingWithConsonant) {
        outputFile << word << endl;
    }

    // Обчислення відсотка слів, які починаються і закінчуються на приголосну літеру, порівняно до всього тексту
    double percentage = static_cast<double>(wordsStartingAndEndingWithConsonant.size()) / text.length() * 100;
    cout << "Percentage: " << percentage << "%" << endl;

    return 0;
}
