//
// Created by Masoud Abdulhanan on 09.03.22.
//

#ifndef AUFGABE_AUFGABE_H
#define AUFGABE_AUFGABE_H
struct dateikarten{                 //Struktur (Liste wird angelegt)
    char firstname[100];
    char lastname[100];
    struct dateikarten *next;       //Pointer wird angelegt
};
void ClearBuffer(void);
void showMenu(void);
void evaluateChoice(int);
struct dateikarten * allocateMemory(void);
void addListItem(void);
void showDictionary(void);
void removeListItem(void);
void saveData(void);
void readDataFromFile(void);
void dataBearbeiten(void);
void listLoeschen(void);
#endif //AUFGABE_AUFGABE_H
