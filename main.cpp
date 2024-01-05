#include <iostream>
#include "cdate.h"
#include "conio.h"
#include <cstdlib>

using namespace std;

const void pressAnyKeyToContinue(){
    cout << "Appuyer sur une touche pour continuer "; getch();
}

const int choiceAndError(int min, int max){
    int option = 0;
    cout << "**************" << endl;
    cout << "Choix : "; cin >> option;
    cout << "**************" << endl;

    if(option < min || option > max){
        cout << "=======================================================" << endl;
        cout << "Veuillez enter un nombre compris entre  "<< min <<" et " << max << endl;
        pressAnyKeyToContinue();
    }

    return option;
}

const void dateFormatChoice(char numSep = '-', bool m = true, bool a = true, bool c = true){
    int x = 1;

    cout << "Sous quelle format souhaitez-vous afficher la date" << endl;
    if(m) cout << x << numSep << " Minimal ex : 1/1/1970" << endl, ++x;
    if(a) cout << x << numSep << " Abrege ex : jeu 1 jan 1970" << endl, ++x;
    if(c) cout << x << numSep << " Complet ex : jeudi 1 janvier 1970" << endl, ++x;
}

const void dateFormatPrint(string message, CDate date, CDate::FORMAT format){
    cout << message << date.formater(format) << endl;
    pressAnyKeyToContinue();
    system("cls");
}

int mainMenu(){
    int option = 0;
    int min = 0, max = 8;
    do{
        cout << "Date" << endl;
        cout << "1- Afficher la date d'aujourd'hui" << endl;
        cout << "2- Ajouter une periode à une date" << endl;
        cout << "3- La difference de (j, m, a) entre 2 dates" << endl;
        cout << "4- Comparer 2 dates" << endl;
        cout << "5- Formater une date" << endl;
        cout << "6- Verifier si une annee est bissextile" << endl;
        cout << "7- Afficher le nombre de jours dans un mois donne" << endl;
        cout << "8- Verifier si une date est valide" << endl;
        cout << "0- Quitter" << endl;
        option = choiceAndError(min, max);
        system("cls");
    }while(option < min || option > max);

    return option;
}

void currentTIme(){
    int option = 0;
    bool exit = false;
    int min = 0, max = 3;

    string message = "Date d'aujourd'hui : ";

    do{
        do{
            cout << "\t\tAfficher la date d'aujourd'hui" << endl << endl;
            dateFormatChoice();
            cout << "0- Menu Precedent" << endl;
            option = choiceAndError(min, max);
            system("cls");
        }while(option < min || option > max);

        switch (option)
        {
        case 0:
            exit = true;
            break;
        case 1:
            dateFormatPrint(message, CDate::currentTime(), CDate::MINIMAL);
            break;
        case 2:
            dateFormatPrint(message, CDate::currentTime(), CDate::ABREGE);
            break;
        case 3:
            dateFormatPrint(message, CDate::currentTime(), CDate::COMPLET);
            break;
        }
    }while(!exit);
}

void addPeriode(){
    CDate date;

    cout << "Ajouter une periode à une date" << endl;

    cout << "Entrer une date : ", cin >> date;

}

int main()
{
    bool exit = false;
    int option = 0;
    // option = 1;

    // cout << "Date" << endl;
    // cout << "1- Afficher la date d'aujourd'hui" << endl;
    // cout << "2- Ajouter une periode à une date" << endl;
    // cout << "3- La difference de (j, m, a) entre 2 dates" << endl;
    // cout << "4- Comparer 2 dates" << endl;
    // cout << "5- Formater une date" << endl;
    // cout << "6- Verifier si une annee est bissextile" << endl;
    // cout << "7- Afficher le nombre de jours dans un mois donne" << endl;
    // cout << "8- Verifier si une date est valide" << endl;
    // cout << "0- Quitter" << endl;

    do{
        option = mainMenu();
        switch (option) {
        case 0:
            exit = true;
            break;
        case 1:
            currentTIme();
            break;
        case 2:
            currentTIme();
            break;
        }
    }while(!exit);

    return 0;
}
