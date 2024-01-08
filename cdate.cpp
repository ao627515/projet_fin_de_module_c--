#include "cdate.h"
#include "time.h"
#include "sstream"
#include "conio.h"
#include <cstdlib>

const std::array<std::string, 7> CDate::_DAYS = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const std::array<std::string, 12> CDate::_MONTHS = {
    "Janvier", "Février", "Mars", "Avril", "Mai", "Juin",
    "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"
};
/************************** CONSTRUCTEURS DEBUT *******************************************/

// Renvoie une CDate initialisé a 1/1/1970 (date par defaut)
CDate::CDate():_day(1), _month(1), _year(1970) {}

/*
 * Parametre day, month, year
 * Renvoie une date initialisé avec les paramètre
 * Sauf exception :
 * Si un paramètre est égal à 0 on revoie sa valeur courante
 */
CDate::CDate(int day, int month, int year){

    if(day == 0) day = currentDay();

    if(month == 0) month = currentMonth();

    if(year == 0) year = currentYear();

    if(dateIsValid(day, month, year)){
        _day = day;
        _month = month;
        _year = year;
    }else{
        defaultDate();
    }
}

/*
 *  Constructeur de copie
 *  Prend en paramètre une date
 *  Et initialise la nouvelle avec les menbres de celui en paramètre
 */
CDate::CDate(const CDate &date):_day(date._day), _month(date._month), _year(date._year){}

/*
 * Contructeur a date au formart string
 * Prend en paramètre une chaine qui represente une date
 * Règle chaque membre de la date doit être séparé par un séparateur
 * ex :  "1/1/1970", "1 8 2022", "12-2-2000", ...
 */
CDate::CDate(const std::string date){
    char sep = '\0';
    std::istringstream iss(date);

    if (!(iss >> _day >> sep >> _month >> sep >> _year) || !dateIsValid(_day, _month, _year) || (iss.get() != EOF)) {
        defaultDate();
    }

    if(!CDate::dateIsValid(_day, _month, _year)) defaultDate();
}

/************************** CONSTRUCTEURS FIN *******************************************/

/************************** METHODE NORMAL DEBUT*******************************************/

void CDate::defaultDate(){
    _day = 0;
    _month = 0;
    _year = 0;
}

void CDate::displayDate(){
    std::cout << _day << '/' << _month << '/' << _year << std::endl;
}

void CDate::addDays(int days) {

    int daysInMonth = CDate::daysInMonth(_month, _year);
    _day += days;

    /*
         * si le nombre de jours est négatif
         * on decrmente le mois et si apres cela le mois est < à 1 mon l'affecte 12 et incremente l'anné
         * On sous trait le nombre de jours ecoulé au nombre dans le mois
         * Et on recommence tant le mois est <= 0
         */
    while (_day <= 0) {
        _month--;

        if (_month < 1) {
            _month = 12;
            _year--;
        }

        daysInMonth = CDate::daysInMonth(_month, _year);
        _day += daysInMonth;
    }

    /*
     *  Si _day est supérieur au nombre de jours dans le mois
     *  On sous trait le nombre de jours ecoulé au nombre dans le mois
     *  on incremente le mois et si le mois est stric sup a 12 on l'initialise a 1 et on incremente l'anné
     *  On recupère le nombre de jours du mois apres son incrémentation
     */
    while (_day > daysInMonth) {
        _day -= daysInMonth;
        _month++;

        if (_month > 12) {
            _month = 1;
            _year++;
        }

        daysInMonth = CDate::daysInMonth(_month, _year);
    }

    if(!CDate::dateIsValid(_day, _month, _year)) defaultDate();
}

// void CDate::subtractDays(int days) {
//     struct tm timeinfo = {};
//     timeinfo.tm_mday = _day;
//     timeinfo.tm_mon = _month - 1;
//     timeinfo.tm_year = _year - 1900;

//     // Soustrait le nombre de jours
//     time_t timeInSeconds = mktime(&timeinfo) - days * 24 * 60 * 60;

//     // Met à jour la date
//     struct tm* newTimeinfo = localtime(&timeInSeconds);
//     _day = newTimeinfo->tm_mday;
//     _month = newTimeinfo->tm_mon + 1;
//     _year = newTimeinfo->tm_year + 1900;
// }

void CDate::addMonth(int nb) {
    int before = _month;
    _month += nb;

    while (_month > 12) {
        _month -= 12;
        ++_year;
    }

    while (_month < 1) {
        _month += 12;
        --_year;
    }

    // Gère les cas ou le mois est incrementé ou décrémenté avec une date en fin de mois
    if(_day == 31
        || (_day == 29 &&  isLeapYear(_year))
        || (_day == 28 && !isLeapYear(_year))
        || (_day == 30 && _month != 2)
        || (_day == 29 && before == 2)
        || (_day == 28 && before ==2))
    {
        _day = daysInMonth(_month, _year);
    }

    if(!CDate::dateIsValid(_day, _month, _year)) defaultDate();
}

void CDate::addYear(int nb){
    _year += nb;

    // Conserve les regle de bixessetilité en cas d'incrementation ou de decrementation de l'année
    if(_month == 2 && (_day == 28 || _day == 29)) {
        _day = daysInMonth(_month, _year);
    }

    if(!CDate::dateIsValid(_day, _month, _year)) defaultDate();
}

/************************** METHODE NORMAL FIN *******************************************/

/************************** METHODE CONSTANT DEBUT*******************************************/
int CDate::lireJour() const{
    return _day;
}

int CDate::lireMois() const{
    return _month;
}

int CDate::lireAnnee() const{
    return _year;
}

CDate CDate::ajouterPeriode(int nb, const TYPE_PERIODE periode) const{
    CDate newDate = *this;
    if(nb != 0){
        switch(periode){
        case CDate::JOUR:
            newDate.addDays(nb);
            break;
        case CDate::SEMAINE:
            newDate.addDays(nb * 7);
            break;
        case CDate::MOIS:
            newDate.addMonth(nb);
            break;
        case CDate::ANNEE:
            newDate.addYear(nb);
            break;
        }
    }

    return newDate;
}

std::string CDate::formater(FORMAT format) {
    std::string str;
    return formater(str, format);
}

std::string CDate::formater(std::string& str, FORMAT format) const {
    std::ostringstream oss;

    struct tm timeinfo = {};
    timeinfo.tm_mday = _day;
    timeinfo.tm_mon = _month - 1;
    timeinfo.tm_year = _year - 1900;

    time_t timeInSeconds = mktime(&timeinfo);

    struct tm* date = localtime(&timeInSeconds);

    switch (format) {
    case MINIMAL:
        oss << *this;
        break;
    case COMPLET:
        oss << _DAYS[date->tm_wday] << ' ' << _day  << ' ' << _MONTHS[date->tm_mon] << ' ' << _year;
        break;
    case ABREGE:
        oss << _DAYS[date->tm_wday].substr(0, 3) << ' ' << _day << ' ' << _MONTHS[date->tm_mon].substr(0, 3) << ' ' << _year;
        break;
    default:
        oss << "Erreur";
        break;
    }

    return str = oss.str();
}

std::string CDate::trouverNomJour(std::string& str, FORMAT format) const {

    struct tm timeinfo = {};
    timeinfo.tm_mday = _day;
    timeinfo.tm_mon = _month - 1;
    timeinfo.tm_year = _year - 1900;

    time_t timeInSeconds = mktime(&timeinfo);

    struct tm* date = localtime(&timeInSeconds);

    switch (format) {
    case MINIMAL:
        str = "Erreur";
        break;
    case COMPLET:
        str = _DAYS[date->tm_wday];
        break;
    case ABREGE:
        str = _DAYS[date->tm_wday].substr(0, 3);
        break;
    default:
        str = "Erreur";
        break;
    }

    return str;
}

std::string CDate::trouverNomMois(std::string& str, FORMAT format) const {

    struct tm timeinfo = {};
    timeinfo.tm_mday = _day;
    timeinfo.tm_mon = _month - 1;
    timeinfo.tm_year = _year - 1900;

    time_t timeInSeconds = mktime(&timeinfo);

    struct tm* date = localtime(&timeInSeconds);
    std::ostringstream oss;

    switch (format) {
    case MINIMAL:
        oss << _month;
        break;
    case COMPLET:
        oss << _MONTHS[date->tm_mon];
        break;
    case ABREGE:
        oss << _MONTHS[date->tm_mon].substr(0, 3);
        break;
    default:
        oss << "Erreur";
        break;
    }

    return str = oss.str();
}

bool CDate::dateIsValid() const{
    return CDate::dateIsValid(_day, _month, _year);
}

/************************** METHODE CONSTANT FIN *******************************************/

/************************** METHODE STATIC DEBUT *******************************************/

bool CDate::yearIsValid(int year){
    return year >= 1;
}

bool CDate::isLeapYear(int year) {
    // Une année bissextile est divisible par 4
    // Sauf si elle est également divisible par 100
    // Auquel cas, elle doit aussi être divisible par 400 pour être bissextile

    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool CDate::monthIsValid(int month){
    // renvoie true ou false si le moi est compris entre 1 et 12
    return month >= 0 && month <= 12;
}

bool CDate::dateIsValid(int day, int month, int year){
    return yearIsValid(year) && monthIsValid(month) && dayIsValid(day, month, year);
}

bool CDate::dayIsValid(int day, int month, int year){

    int daysInMonth = 31;

    // Si ce n'est pas un mois a 31 jours
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }else if (month == 2) {
        // si l'anné est bissextil et si on est en fevrier
        daysInMonth = isLeapYear(year) ? 29 : 28;
    }

    // si le jour n'est compris entre 1 et le nombre de jours maximal du mois passé en parametre
    return day < 1 || day > daysInMonth ? false : true;
}

int CDate::daysInMonth(int month, int year){
    if(month == 0) month = currentMonth();

    int daysInMonth = 31;
    // Si ce n'est pas un mois a 31 jours
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }else if (month == 2) {
        if(year == 0) year = currentYear();

        // si l'anné est bissextil et si on est en fevrier
        daysInMonth = CDate::isLeapYear(year) ? 29 : 28;
    }

    return daysInMonth;
}

int CDate::currentDay(){
    time_t t = time(0);
    return localtime(&t)->tm_mday;
}

int CDate::currentMonth(){
    time_t t = time(0);
    return localtime(&t)->tm_mon + 1;
}

int CDate::currentYear(){
    time_t t = time(0);
    return localtime(&t)->tm_year + 1900;
}

CDate CDate::currentTime() {
    time_t t = time(0);
    tm* currentDate = localtime(&t);

    return CDate(currentDate->tm_mday, currentDate->tm_mon + 1, currentDate->tm_year + 1900);
}

/************************** METHODE STATIC FIN *******************************************/

/************************** Surcharge D'OPERATEUR DEBUT*******************************************/

std::ostream& operator<<(std::ostream& os, const CDate& date){
    return  os  << date._day << '/' << date._month << '/' << date._year;
}

std::istream& operator>>(std::istream& is, CDate& date){
    std::string dateString;
    int d = 0, m = 0, y = 0;
    char sep = '\0';

    //  Lit la date entré et la stock dans dateString
    if(std::getline (is, dateString)){

        // Crée une variable de type istringstream nommé iss
        // Elle sera utilisé pour extraire le jours, mois, année et le séparateur
        std::istringstream iss(dateString);

        // On essaie d'extraire a la suite le jours, mois et année contenu dans iss
        /*
         * On extrait d'abord le jours et on l'affecte a d tout en verifiant si l'opération a reussie
         *
         * Ensuite on extrait le séparateur et l'affecte a sep
         * Dans le cas ou le sépararteur est un caractère d'espacement >> le saute
         * Donc on utilise iss.get() pour lire a le prochain caratère quelquel soit
         *
         * Enfin si on extrait le separateur on continue avec le mois puis extrait le dernier separateur, puis l'année
         *
         * Si la date ne corespond pas au format : jj|sep|mm|sep|aaaa, la date par defaut est pris 1/1/1970
         *
         */

        if(iss >> d){
            if( iss.get(sep)){
                iss >> m;

                if( iss.get(sep)){
                    iss >> y;
                }
            }
        }
    }

    if(CDate::dateIsValid(d, m, y)){
        date._day = d;
        date._month = m;
        date._year = y;
    }else{
        date.defaultDate();
    }

    return is;
}

bool CDate::operator==(const CDate& date) const{
    return _year == date._year && _month == date._month && _day == date._day;
}

bool CDate::operator==(const std::string date) const{
    CDate d = date;

    return _year == d._year && _month == d._month && _day == d._day;
}

bool CDate::operator!=(const CDate& date) const{
    return _year != date._year || _month != date._month || _day != date._day;
}

bool CDate::operator<(const CDate& date) const {
    return (_year < date._year) ||
           (_year == date._year && _month < date._month) ||
           (_year == date._year && _month == date._month && _day < date._day);
}

bool CDate::operator<(const std::string date) const {
    CDate d = date;
    return *this < d;
}

bool CDate::operator>(const CDate& date) const {
    return (_year > date._year) ||
           (_year == date._year && _month > date._month) ||
           (_year == date._year && _month == date._month && _day > date._day);
}

bool CDate::operator<=(const CDate& date) const{
    return operator<(date) || operator==(date);
}

bool CDate::operator>=(const CDate& date) const{
    return operator>(date) || operator==(date);
}

CDate& CDate::operator=(const CDate& date) {
    // Vérifie si on n'essaie pas de s'affecter à soi-même
    if (this != &date) {
        // Copie les membres de l'autre objet
        _day = date._day;
        _month = date._month;
        _year = date._year;
    }
    // Retourne l'objet modifié par référence
    return *this;
}

CDate& CDate::operator=(const std::string date){
    int d = 0, m = 0, y = 0;
    char sep = '\0';

    std::istringstream iss(date);

    if(iss >> d){
        if( iss.get(sep)){
            iss >> m;

            if( iss.get(sep)){
                iss >> y;
            }
        }
    }

    if(CDate::dateIsValid(d, m, y)){
        _day = d;
        _month = m;
        _year = y;
    }else{
        defaultDate();
    }

    return *this;
}

CDate CDate::operator+(const int days) const{
    CDate result = *this;
    result.addDays(days);
    return result;
}

CDate CDate::operator-(const int days) const{
    CDate result = *this;
    result.addDays(days);
    return result;
}

int  CDate::operator-(const CDate& date) const{
    struct tm thisDate = {};
    thisDate.tm_mday = _day;
    thisDate.tm_mon = _month - 1;
    thisDate.tm_year = _year - 1900;

    struct tm otherDate = {};
    otherDate.tm_mday = date._day;
    otherDate.tm_mon = date._month - 1;
    otherDate.tm_year = date._year - 1900;

    time_t thisDateInSecond = mktime(&thisDate);
    time_t otherDateInSecond = mktime(&otherDate);
    double diffDayInSeconds = difftime(thisDateInSecond, otherDateInSecond);

    return static_cast<int>(diffDayInSeconds / (60 * 60 * 24));
}

CDate& CDate::operator+=(const int days){
    return *this = *this + days;
}

CDate& CDate::operator-=(const int days){
    return *this = *this - days;
}

// Operateur préIncrémentation
CDate& CDate::operator++(){
    return *this = *this + 1;
}

// Opérateur préDrécrémentation
CDate& CDate::operator--(){
    return *this = *this - 1;
}

// Opérateur posIncrémentation
CDate CDate::operator++(int){
    CDate tmp = *this;
    ++(*this);
    return tmp;
}

// Opérateur posDécrémentation
CDate CDate::operator--(int){
    CDate tmp = *this;
    --(*this);
    return tmp;
}

/************************** Surcharge D'OPERATEUR FIN *******************************************/

/************************** Fonction thematique *******************************************/
namespace CDateProgTest
{
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

    const void dateFormatChoice(char numSep, bool m, bool a, bool c){
        int x = 1;

        cout << "Sous quelle format souhaitez-vous afficher la date" << endl << endl;
        if(m) cout << x << numSep << " Minimal ex : 1/1/1970" << endl, ++x;
        if(a) cout << x << numSep << " Abrege ex : jeu 1 jan 1970" << endl, ++x;
        if(c) cout << x << numSep << " Complet ex : jeudi 1 janvier 1970" << endl, ++x;
    }

    const void dateFormatPrint(string message, CDate date, CDate::FORMAT format, bool clear){
        cout << message << date.formater(format) << endl ;
        pressAnyKeyToContinue();
        if(clear) system("cls");
    }


    int mainMenu(){
        int option = 0;
        int min = 0, max = 6;
        do{
            cout << "Date" << endl;
            cout << "1- Afficher la date d'aujourd'hui" << endl;
            cout << "2- Ajouter une periode a une date" << endl;
            cout << "3- La difference de (j, m, a) entre 2 dates" << endl;
            cout << "4- Comparer 2 dates" << endl;
            cout << "5- Formater une date" << endl;
            cout << "6- Verifier si une annee est bissextile" << endl;
            // cout << "7- Afficher le nombre de jours dans un mois donne" << endl;
            // cout << "8- Verifier si une date est valide" << endl;
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
            cout << endl << "Quelle periode voullez-vous ajouter ?" << endl << endl;
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

    void formatDate(){
        CDate d;
        bool dateIsInvalid;
        bool continuous = false;
        bool dateIsBefore1970;
        int option = 0, min = 0, max = 2;
        string ex ="(ex -> 1/1/1970)";
        string message = "Date formater -> ";

        do{
            cout << "Formater une date" << endl << endl;
            do {
                cout << "NB : nous ne pouvons formater une date inf a 1/1/1970 " << endl << endl;
                cout << "Entrer une date " << ex << " : ";
                cin >> d;

                dateIsInvalid = d.dateIsValid();
                dateIsBefore1970 = d < "1/1/1970";

                if (!dateIsInvalid || dateIsBefore1970) {
                    cout << "=======================================================" << endl;
                    cout << "Date incorrecte. Veuillez entrer une date valide " << ex << endl;
                    pressAnyKeyToContinue();
                    cout << endl << endl;
                }
            } while (!dateIsInvalid || dateIsBefore1970);


            do{
                cout << endl;
                dateFormatChoice('-', false);
                cout << "0- Menu Precedent" << endl;
                option = choiceAndError(min, max);
                cout << endl;
            }while(option < min || option > max);


            switch (option)
            {
            case 0:
                continuous = true;
                break;
            case 1:
                dateFormatPrint(message, d, CDate::MINIMAL);
                break;
            case 2:
                dateFormatPrint(message, d, CDate::ABREGE);
                break;
            case 3:
                dateFormatPrint(message, d, CDate::COMPLET);
                break;
            }
            if(!continuous){
                continuous = restartOrExist();
            }
        }while(!continuous);
    }

    void isLeapYear(){
        int y;
        bool continuous = false;
        bool dateIsBefore1970;

        do{
            cout << "Verifier si une annee est bissextile" << endl << endl;

            cout << "Enter l'annee : ", cin >> y, cin.ignore();

            cout << endl;

            if(CDate::isLeapYear(y)){
                cout << y << " est une annee bissextile" << endl ;
            }else {
                cout << y << " n'est pas une annee bissextile" << endl;
            }

            cout << endl;

            continuous = restartOrExist();

        }while(!continuous);
    }

    int progTest()
    {
        bool exit = false;
        int option = 0;

        // option = 6;
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
                addPeriode();
                break;
            case 3:
                diffBetweenTwoDates();
                break;
            case 4:
                compareTwoDate();
                break;
            case 5:
                formatDate();
                break;
            case 6:
                isLeapYear();
                break;
            }
        }while(!exit);

        return 0;
    }
}
/************************** Fonction thematique *******************************************/
