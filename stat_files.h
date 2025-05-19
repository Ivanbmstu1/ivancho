#ifndef STAT_FILES_H
#define STAT_FILES_H

struct StatFileInfo {
    int* _letters;      
    char* _fileName;    

    StatFileInfo();                             
    StatFileInfo(const char* fileName);         
    ~StatFileInfo();                            

    void printStats() const;                    
};


void GetCountLetters(StatFileInfo* fileInfo, const char* fileName);

#endif // STAT_FILES_H
