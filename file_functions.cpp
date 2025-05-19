#include "file_functions.h"
#include <fstream>
#include <cstring>
#include <cctype>


#define MAX_WORDS 1000000

#define MAX_WORD_LENGTH 64

struct WordCount {
    char word[MAX_WORD_LENGTH];
    int count;
};


int CompareWords(const void* a, const void* b) {
    const WordCount* wc1 = (const WordCount*)a;
    const WordCount* wc2 = (const WordCount*)b;
    return strcmp(wc1->word, wc2->word);
}


int CompareCounts(const void* a, const void* b) {
    const WordCount* wc1 = (const WordCount*)a;
    const WordCount* wc2 = (const WordCount*)b;
    return wc2->count - wc1->count;
}

void CountWords(const char* fileName) {
    
    if (!fileName) return;

    
    FILE* inputFile = fopen(fileName, "r");
    if (!inputFile) {
        perror("Ошибка открытия входного файла");
        return;
    }

    
    char outputFileName[256];
    snprintf(outputFileName, sizeof(outputFileName), "count_%s", fileName);

    
    WordCount words[MAX_WORDS];
    int wordCount = 0;

    
    char currentWord[MAX_WORD_LENGTH];
    int wordLength = 0;
    char c;

    
    while ((c = fgetc(inputFile)) != EOF) {
        if (isalpha(c)) {
            
            if (wordLength < MAX_WORD_LENGTH - 1) {
                currentWord[wordLength++] = tolower(c);
            }
        } else if (wordLength > 0) {
            
            currentWord[wordLength] = '\0';
            wordLength = 0;

            
            int found = -1;
            for (int i = 0; i < wordCount; ++i) {
                if (strcmp(words[i].word, currentWord) == 0) {
                    found = i;
                    break;
                }
            }

            
            if (found >= 0) {
                words[found].count++;
            } else if (wordCount < MAX_WORDS) {
                strcpy(words[wordCount].word, currentWord);
                words[wordCount].count = 1;
                wordCount++;
            }
        }
    }

    fclose(inputFile);

    
    qsort(words, wordCount, sizeof(WordCount), CompareWords);

    
    qsort(words, wordCount, sizeof(WordCount), CompareCounts);

    
    FILE* outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Ошибка открытия выходного файла");
        return;
    }

    for (int i = 0; i < wordCount; ++i) {
        fprintf(outputFile, "%s\t%d\n", words[i].word, words[i].count);
    }

    fclose(outputFile);
}
