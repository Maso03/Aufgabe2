//
// Created by Masoud Abdulhanan on 09.03.22.
//
#include "stdio.h"
#include "Aufgabe.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

struct dateikarten * first = NULL;          //Pointer first und current angelegt
struct dateikarten * current = NULL;

void dataBearbeiten(void){
    int choice;
    do {
        showMenu();
        choice = getchar();
        ClearBuffer();
        evaluateChoice(choice);

    }while (choice != '8');

}

void showMenu(void){
    puts("--------------------");
    puts("Was wollen Sie machen?");
    puts("(1) Element hinzufügen");
    puts("(2) Element löschen");
    puts("(3) Liste anzeigen lassen");
    puts("(4) Liste sortieren");
    puts("(5) Liste zurücksetzen und löschen");
    puts("(6) Liste laden");
    puts("(7) Liste speichern");
    puts("(8) Programm beenden");
    puts("----------------------");
}

void evaluateChoice(int choice){
    switch (choice) {
        case '1':
            puts("Element hinzufügen");
            addListItem();
            break;
        case '2':
            puts("Element löschen");
            removeListItem();
            break;
        case '3':
            puts("Liste anzeigen");
            showDictionary();
            break;
        case '4':
            puts("Liste sortieren");
            break;
        case '5':
            puts("Liste löschen");
            listLoeschen();
            break;
        case '6':
            puts("Liste laden");
            readDataFromFile();
            break;
        case '7':
            puts("Liste speichern");
            saveData();
            break;
        case '8':
            puts("Programm beendet!");
            break;
        default:
            puts("Unsinnige Eingabe, bitte Zahlen von 1-8 eingeben!");
            break;
    }
}

void ClearBuffer(void){
    while(getchar() !='\n'){

    }
}

struct dateikarten * allocateMemory(void){                      // Speicher freigeben, Liste anlegen
    struct dateikarten * pDatei = (struct dateikarten *) malloc(sizeof(struct dateikarten));

    if (!pDatei){                                           //Wenn Speicher voll, beenden
        puts("Speicher voll! Malloc packt es nicht");
        exit(1);
    }
    return pDatei;              // Rückgabe des Speicherplatzes
}

void addListItem(void){
    if (first == NULL){         //Wenn kein Element vorhanden ist
        first = allocateMemory();
        current = first;
    }
    else {              // Element bereits vorhanden
        current = first;
        while (current->next){          //Bringt Current an das Ende der verketteten Liste
            current = current->next;
        }
        current->next = allocateMemory();   // Speicher für das neue Element muss freigegeben werden!
        current = current->next;            //Current auf das Neue zeigen
    }
    printf("Vorname: ");
    scanf("%s", current->firstname);        // Eingabe des Vornamen
    ClearBuffer();              //Eingabe leeren
    printf("Nachname: ");
    scanf("%s", current->lastname);         // Eingabe des Nachnamens
    ClearBuffer();              //Eingabe leeren

    current->next = NULL; // Ende des neuen Elements muss NULL sein
    puts("Person wurde erfolgreich hinzugefügt!");
    saveData();
}

void showDictionary(void){
    if (first == NULL){                     // Wenn nichts existiert
        puts("Es wurden keine Personen angelegt!");
        return;
    }
    int index =1;
    current = first;

    puts("Hier ist deine Liste:");

    while (current != NULL){                // Wird ausgegeben, solange etwas existiert
        printf("Nr.%d: %s %s\n", index++, current->firstname, current->lastname);
        current = current->next;                // Current wird auf das nächste Element gezeigt
    }
}

void removeListItem(void){
    if(first == NULL){
        puts("Keine Personen zum entfernen gefunden!");
        return;
    }
    struct dateikarten * prev = NULL;
    int removeItem;
    int count = 1;

    eingabe:

    puts("Welcher Eintrag soll gelöscht werden?");  //Welcher Eintrag? Liste nochmal anzeigen lassen
    showDictionary();
    scanf("%d", &removeItem); //Eingabe wird erwartet
    int choice = getchar();
    ClearBuffer();


    if(removeItem < count){     // Fehlerabfrage bzw. Fehler abzufangen, falls Nutzer Zahl <=0 eingibt
        puts("Zahl > 0 eingeben!");
        goto eingabe;
    }
    if (choice != '\n'){
        puts("Zahl eingeben!");
        goto eingabe;
    }

    current = first;

    while (count < removeItem){     // 1<2, wenn 2 Item entfernt werden soll
        prev = current;             // Das Vorherige zeigt auf current gesetzt, zeigen beide auf den ersten Pointer, zeigt auf das erste Item
        current = current->next;    // Current wird auf das nächste Item gesetzt, current zeigt auf den Eintrag der zu entfernen ist z.B. 2
        count++;

        if (current == NULL){       // Wenn current NULL, existiert kein 2tes Element, existiert nur, wenn current nicht NULL ist
            puts("Dieser Eintrag wurde nicht gefunden!");
            return;
        }
    }
    if (prev == NULL) {         // Wenn das vorherige pointer NULL ist
        first = current->next;    // Der zweite Eintrag, ist der erste Listeneintrag, First zeigt nun auf das nächste Element
    }
    else {
        prev->next = current->next;     // Prev von nächsten wird auf das zu entfernende Element gesetzt
    }
    free(current);

    puts("Der Nutzer wurde erfolgreich entfernt!");
    saveData();
}

void saveData(void){
    FILE *fp = NULL;

    fp = fopen("data.txt", "w");
    if (fp == NULL){
        puts("Die Datei konnte nicht geöffnet werden! Das Speichern ist fehlgeschlagen!");
        exit(1);
    }
    current = first;
    while (current){
        fprintf(fp, "%s %s\n", current->firstname, current->lastname);
        current = current->next;
    }
    fclose(fp);

    puts("Die Benutzer wurden gespeichert!");
}

void readDataFromFile(void){
    FILE *fp = NULL;
    char temp[51];

    fp = fopen("data.txt", "r");

    if(fp == NULL){
        puts("Keine Personen gefunden!");
        return;     //Kehrt zurück, da keine Datei existiert
    }

    if (fscanf(fp, "%s", temp) != EOF) {
        first = allocateMemory();
        current = first;
        strcpy(current->firstname, temp);
        fscanf(fp, "%s", temp);
        strcpy(current->lastname, temp);
        current->next = NULL;

        while (fscanf(fp, "%s", temp) != EOF){
            current->next = allocateMemory();
            current = current->next;
            strcpy(current->firstname, temp);
            fscanf(fp, "%s", temp);
            strcpy(current->lastname, temp);
            current->next = NULL;
        }
    }

    fclose(fp);
    puts("Die Datei wurde erfolgreich geladen!");
}

void listLoeschen(void){
    while(first)
    {
        current = first;
        first = first->next;
        free(current);
    }
    saveData();
}



