#include <iostream>
#include "cdate.h"
#include "conio.h"
#include <cstdlib>
#include "sstream"

using namespace std;

const void pressAnyKeyToContinue(){
    cout << "Appuyer sur une touche pour continuer "; getch(), cout << flush;
}

const int choiceAndError(int min, int max){
    int option = 0;
    cout << "**************" << endl;
    cout << "Choix : "; cin >> option; cin.ignore();
    cout << "**************" << endl;

    if(option < min || option > max){
        cout << "=======================================================" << endl;
        cout << "Veuillez enter un nombre compris entre  "<< min <<" et " << max << endl;
        pressAnyKeyToContinue();
    }

    return option;
}

bool restartOrExist(){
    bool option = 0;
    bool min = 0, max = 1;

    do{
        cout << "1- Recomencer" << endl;
        cout << "0- Menu pricipal" << endl;
        option = choiceAndError(min, max);
        system("cls");
    }while(option < min || option > max);
    system("cls");
    return option;
}

const void dateFormatChoice(char numSep = '-', bool m = true, bool a = true, bool c = true){
    int x = 1;

    cout << "Sous quelle format souhaitez-vous afficher la date" << endl;
    if(m) cout << x << numSep << " Minimal ex : 1/1/1970" << endl, ++x;
    if(a) cout << x << numSep << " Abrege ex : jeu 1 jan 1970" << endl, ++x;
    if(c) cout << x << numSep << " Complet ex : jeudi 1 janvier 1970" << endl, ++x;
}

const void dateFormatPrint(string message, CDate date, CDate::FORMAT format, bool clear = true){
    cout << message << date.formater(format) << endl << endl;
    pressAnyKeyToContinue();
    if(clear) system("cls");
}


int mainMenu(){
    int option = 0;
    int min = 0, max = 8;
    do{
        cout << "Date" << endl;
        cout << "1- Afficher la date d'aujourd'hui" << endl;
        cout << "2- Ajouter une periode a une date" << endl;
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


CDate::TYPE_PERIODE choicePeriode(){
    int option = 0;
    int min = 0, max = 4;
    CDate::TYPE_PERIODE periode;

    do{
        cout << endl << "Quelle periode voullez-vous ajouter ?" << endl;
        cout << "1- Jour(s)" << endl;
        cout << "2- Semaine(s)" << endl;
        cout << "3- Mois" << endl;
        cout << "4- Anne(s)" << endl;
        option = choiceAndError(min, max);
        cout << endl;
    }while(option < min || option > max);

    switch (option) {
    case 1:
        periode = CDate::JOUR;
        break;
    case 2:
        periode = CDate::SEMAINE;
        break;
    case 3:
        periode = CDate::MOIS;
        break;
    case 4:
        periode = CDate::ANNEE;
        break;
    }

    return periode;
}

int getNbPeriode(CDate::TYPE_PERIODE periode){
    string ex = "ex (-10, 9)";
    int nbPeriode = 0;

    cout << "Combien de ";
    switch (periode) {
    case CDate::JOUR:
        cout << "jour(s) " << ex << " voullez-vous ajouter : ";
        break;
    case CDate::SEMAINE:
        cout << "semaine(s) " << ex << " voullez-vous ajouter : ";
        break;
    case CDate::MOIS:
        cout << "mois(s) " << ex << " voullez-vous ajouter : ";
        break;
    case CDate::ANNEE:
        cout << "anne(s) " << ex << " voullez-vous ajouter : ";
        break;
    }
    cin >> nbPeriode; cin.ignore();

    return nbPeriode;
}

void addPeriode(){
    int nbPeriode;
    CDate::TYPE_PERIODE periode;
    CDate date;
    bool continuous;
    string ex ="(ex -> 1/1/1970)";
    int option = 0;
    int min = 1, max = 3;
    string message = "";
    bool dateIsInvalid;
    bool dateIsBefore1970 ;

    do{

        do {
            cout << "\t\tAjouter une periode a une date" << endl << endl;
            cout << "NB : nous ne pouvons formater une date inf a 1/1/1970 " << endl << endl;
            cout << "Entrer une date " << ex << " : ";
            cin >> date;

            dateIsInvalid = date.dateIsValid();
            dateIsBefore1970 = date < "1/1/1970";

            if (!dateIsInvalid || dateIsBefore1970) {
                cout << "=======================================================" << endl;
                cout << "Date incorrecte. Veuillez entrer une date valide " << ex << endl;
                pressAnyKeyToContinue();
                system("cls");
            }
        } while (!dateIsInvalid || dateIsBefore1970);



        periode = choicePeriode();
        nbPeriode = getNbPeriode(periode);

        do{
            cout << endl;
            dateFormatChoice();
            option = choiceAndError(min, max);
            cout << endl;
        }while(option < min || option > max);

        switch (option)
        {
        case 1:
            dateFormatPrint(message, date.ajouterPeriode(nbPeriode, periode), CDate::MINIMAL, false);
            break;
        case 2:
            dateFormatPrint(message,  date.ajouterPeriode(nbPeriode, periode), CDate::ABREGE, false);
            break;
        case 3:
            dateFormatPrint(message,  date.ajouterPeriode(nbPeriode, periode), CDate::COMPLET, false);
            break;
        }
        cout << endl << endl;
        continuous = restartOrExist();
    }while(continuous);



}


void diffBetweenTwoDates(){
    CDate d1;
    CDate d2;
    string ex ="(ex -> 1/1/1970)";
    bool dateIsInvalid;
    int diff = 0;
    bool continuous;

    do{
        cout << "La difference (en j) entre 2 dates" << endl << endl;

        do{
            cout << "Date 1 : ", cin >> d1;

            dateIsInvalid = d1.dateIsValid();

            if (!dateIsInvalid) {
                cout << "=======================================================" << endl;
                cout << "Date incorrecte. Veuillez entrer une date valide " << ex << endl;
                pressAnyKeyToContinue();
                cout << endl << endl;
            }
        }while(!dateIsInvalid);

        cout << endl;
        do{
            cout << "Date 2 : ", cin >> d2;

            dateIsInvalid = d2.dateIsValid();

            if (!dateIsInvalid) {
                cout << "=======================================================" << endl;
                cout << "Date incorrecte. Veuillez entrer une date valide " << ex << endl;
                pressAnyKeyToContinue();
                cout << endl << endl;
            }
        }while(!dateIsInvalid);

        cout << endl ;

        if(d1 > d2){
            cout << "Il y a " << d1 - d2 << " jours de difference entre " << d2 << " et " << d1  << endl;
        }else if(d2 > d1){
            cout << "Il y a " << d2 - d1 << " jours de difference entre " << d1 << " et " << d2  << endl;
        }else{
            cout << "Il y a " << d2 - d1 << " jours de difference entre " << d1 << " et " << d2  << endl;
        }
        cout << endl;
        continuous = restartOrExist();
    }while(continuous);
}

void compareTwoDate() {
    CDate d1;
    CDate d2;
    string comp = "";
    string ex1 = "(ex -> 1/1/1970)";
    string ex2 = "(ex -> 1/1/2000)";
    string exOp = ">, <, >=, <=, ==, !=";
    bool dateIsInvalid;
    bool continuous;
    bool opIsValid;
    string op = "";

    do {
        cout << "Comparer 2 dates" << endl << endl;

        // Saisie et validation de la première date
        do {
            cout << "Saisir la premiere date " << ex1 << " : ";
            cin >> d1;

            dateIsInvalid = !d1.dateIsValid();

            if (dateIsInvalid) {
                cout << "=======================================================" << endl;
                cout << "Date incorrecte. Veuillez entrer une date valide " << ex1 << endl;
                pressAnyKeyToContinue();
                cout << endl << endl;
            }
        } while (dateIsInvalid);

        cout << endl;

        do{
            // Saisie de l'operateur de comparaison
            cout << "Saisir l'operateur de comparaison (" << exOp << ") : ";
            getline(cin, op);
            opIsValid = (op == ">" || op == "<" || op == ">=" || op == "<=" || op == "==" || op == "!=");
            if (!opIsValid) {
                cout << "=======================================================" << endl;
                cout << "Date incorrecte. Veuillez entrer une date valide " << ex2 << endl;
                pressAnyKeyToContinue();
                cout << endl << endl;
            }
        }while(!opIsValid);
        cout << endl;
        // Saisie et validation de la deuxième date
        do {
            cout << "Saisir la deuxieme date " << ex2 << " : ";
            cin >> d2;

            dateIsInvalid = !d2.dateIsValid();

            if (dateIsInvalid) {
                cout << "=======================================================" << endl;
                cout << "Date incorrecte. Veuillez entrer une date valide " << ex2 << endl;
                pressAnyKeyToContinue();
                cout << endl << endl;
            }
        } while (dateIsInvalid);


        // Comparaison des dates
        if (op == ">" || op == "<" || op == ">=" || op == "<=" || op == "==" || op == "!=") {

            bool result;

            if (comp == ">") {
                result = (d1 > d2);
            } else if (comp == "<") {
                result = (d1 < d2);
            } else if (comp == ">=") {
                result = (d1 >= d2);
            } else if (comp == "<=") {
                result = (d1 <= d2);
            } else if (comp == "==") {
                result = (d1 == d2);
            } else if (comp == "!=") {
                result = (d1 != d2);
            }

            string res = result ? "Vrai" : "Faux";


            cout << endl << "Resultat de la comparaison : " << d1 << " " << op << " " << d2 << " " << res << endl;
        }
        cout << endl;
        continuous = restartOrExist();
    } while (continuous);
}

int main()
{
    bool exit = false;
    int option = 0;

    // cout << "4- Comparer 2 dates" << endl;
    // cout << "5- Formater une date" << endl;
    // cout << "6- Verifier si une annee est bissextile" << endl;
    // cout << "7- Afficher le nombre de jours dans un mois donne" << endl;
    // cout << "8- Verifier si une date est valide" << endl;
    // cout << "0- Quitter" << endl;
    option = 4;
    do{
        // option = mainMenu();
        switch (option) {
        case 0:
            exit = true;
            break;
        case 1:
            currentTIme();
            break;
        case 2:
            addPeriode();
            break;
        case 3:
            diffBetweenTwoDates();
            break;
        case 4:
            compareTwoDate();
            break;
        }
    }while(!exit);

    return 0;
}
