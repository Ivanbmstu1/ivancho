#include "stat_files.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>


StatFileInfo::StatFileInfo() : _letters(new int[256]()), _fileName(nullptr) {}


StatFileInfo::StatFileInfo(const char* fileName) : _letters(new int[256]()) {
    _fileName = new char[strlen(fileName) + 1];
    strcpy(_fileName, fileName);
}


StatFileInfo::~StatFileInfo() {
    delete[] _letters;
    delete[] _fileName;
}


void StatFileInfo::printStats() const {
    std::cout << "Частотность букв в файле '" << _fileName << "':\n";
    for (int i = 0; i < 256; ++i) {
        if (_letters[i] > 0 && isalpha(i)) {
            std::cout << "'" << static_cast<char>(i) << "': " << _letters[i] << "\n";
        }
    }
}


void GetCountLetters(StatFileInfo* fileInfo, const char* fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << fileName << "'\n";
        return;
    }

    
    memset(fileInfo->_letters, 0, 256 * sizeof(int));

    
    char ch;
    while (file.get(ch)) {
        if (isalpha(ch)) {
            fileInfo->_letters[static_cast<unsigned char>(tolower(ch))]++;
        }
    }

    file.close();

    
    delete[] fileInfo->_fileName;
    fileInfo->_fileName = new char[strlen(fileName) + 1];
    strcpy(fileInfo->#include "stat_files.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>


StatFileInfo::StatFileInfo() : _letters(new int[256]()), _fileName(nullptr) {}


StatFileInfo::StatFileInfo(const char* fileName) : _letters(new int[256]()) {
    _fileName = new char[strlen(fileName) + 1];
    strcpy(_fileName, fileName);
}


StatFileInfo::~StatFileInfo() {
    delete[] _letters;
    delete[] _fileName;
}


void StatFileInfo::printStats() const {
    std::cout << "Частотность букв в файле '" << _fileName << "':\n";
    for (int i = 0; i < 256; ++i) {
        if (_letters[i] > 0 && isalpha(i)) {
            std::cout << "'" << static_cast<char>(i) << "': " << _letters[i] << "\n";
        }
    }
}


void GetCountLetters(StatFileInfo* fileInfo, const char* fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << fileName << "'\n";
        return;
    }

    
    memset(fileInfo->_letters, 0, 256 * sizeof(int));

    
    char ch;
    while (file.get(ch)) {
        if (isalpha(ch)) {
            fileInfo->_letters[static_cast<unsigned char>(tolower(ch))]++;
        }
    }

    file.close();

    
    delete[] fileInfo->_fileName;
    fileInfo->_fileName = new char[strlen(fileName) + 1];
    strcpy(fileInfo->_fileName, fileName);
}_fileName, fileName);
}
