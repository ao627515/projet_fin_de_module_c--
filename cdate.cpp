#include "cdate.h"
#include "time.h"
#include "sstream"

const std::array<std::string, 7> CDate::_DAYS = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const std::array<std::string, 12> CDate::_MONTHS = {
    "Janvier", "Février", "Mars", "Avril", "Mai", "Juin",
    "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"
};
/************************** CONSTRUCTEURS DEBUT *******************************************/
CDate::CDate():_day(1), _month(1), _year(1970) {}

CDate::CDate(int day, int month, int year){
    if(year != 0 && month != 0 && day != 0){
        if(dateIsValid(day, month, year)){
            _day = day;
            _month = month;
            _year = year;
        }else{
            defaultDate();
        }
    }else if(year == 0 && month != 0 && day != 0){
        time_t t = time(0);
        struct tm *currentTime = localtime(&t);

        int currentYear = currentTime->tm_year + 1900;

        if(dateIsValid(day, month, currentYear)){
            _day = day;
            _month = month;
            _year = currentYear;
        }else{
            defaultDate();
        }
    }else if(year == 0 && month == 0 && day != 0){
        time_t t = time(0);
        struct tm *currentTime = localtime(&t);

        int currentYear = currentTime->tm_year + 1900;
        int currentMonth = currentTime->tm_mon + 1;

        if(dateIsValid(day, currentMonth, currentYear)){
            _day = day;
            _month = currentMonth;
            _year = currentYear;
        }else{
            defaultDate();
        }
    }else if(year == 0 && month == 0 && day == 0){
        time_t t = time(0);
        struct tm *currentTime = localtime(&t);

        int currentYear = currentTime->tm_year + 1900;
        int currentMonth = currentTime->tm_mon + 1;
        int currentDay = currentTime->tm_mday;

        if(dateIsValid(currentDay, currentMonth, currentYear)){
            _day = currentDay;
            _month = currentMonth;
            _year = currentYear;
        }else{
            defaultDate();
        }
    }
}

CDate::CDate(const CDate &date):_day(date._day), _month(date._month), _year(date._year){}

CDate::CDate(const std::string date){
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
}
/************************** CONSTRUCTEURS FIN *******************************************/

/************************** METHODE NORMAL DEBUT*******************************************/

void CDate::defaultDate(){
    _day = 1;
    _month = 1;
    _year = 1970;
}

void CDate::displayDate(){
    std::cout << _day << '/' << _month << '/' << _year << std::endl;
}

void CDate::normalize() {
    if (!CDate::dateIsValid(_day, _month, _year)) {
        int daysInMonth = CDate::daysInMonth(_month, _year);

        // Si _day est négatif
        while (_day <= 0) {
            _month--;

            if (_month < 1) {
                _month = 12;
                _year--;
            }

            daysInMonth = CDate::daysInMonth(_month, _year);
            _day += daysInMonth;
        }

        // Si _day est supérieur au nombre de jours dans le mois
        while (_day > daysInMonth) {
            int m = _month - 1;
            if(m < 0) m = 12;
            if (_month == 2 && _day == 29 && !CDate::isLeapYear(_year)) {
                --_day;
            }else if(_day == CDate::daysInMonth(m, _year)){
                _day = CDate::daysInMonth(_month, _year);
            } else{
                _day -= daysInMonth;
                _month++;
            }

            if (_month > 12) {
                _month = 1;
                _year++;
            }

            daysInMonth = CDate::daysInMonth(_month, _year);
        }

        if(!CDate::dateIsValid(_day, _month, _year)) defaultDate();
    }
}

void CDate::addDays(int days) {
    struct tm timeinfo = {};
    timeinfo.tm_mday = _day;
    timeinfo.tm_mon = _month - 1; // Les mois commencent à 0
    timeinfo.tm_year = _year - 1900; // Année depuis 1900

    // Ajoute le nombre de jours
    time_t timeInSeconds = mktime(&timeinfo) + (days * 24 * 60 * 60);

    // Met à jour la date
    struct tm* newTimeinfo = localtime(&timeInSeconds);
    _day = newTimeinfo->tm_mday;
    _month = newTimeinfo->tm_mon + 1; // Les mois commencent à 0
    _year = newTimeinfo->tm_year + 1900; // Année depuis 1900
}

void CDate::subtractDays(int days) {
    struct tm timeinfo = {};
    timeinfo.tm_mday = _day;
    timeinfo.tm_mon = _month - 1;
    timeinfo.tm_year = _year - 1900;

    // Soustrait le nombre de jours
    time_t timeInSeconds = mktime(&timeinfo) - days * 24 * 60 * 60;

    // Met à jour la date
    struct tm* newTimeinfo = localtime(&timeInSeconds);
    _day = newTimeinfo->tm_mday;
    _month = newTimeinfo->tm_mon + 1;
    _year = newTimeinfo->tm_year + 1900;
}

void CDate::addMonth(int nb) {
    _month += nb;

    while (_month > 12) {
        _month -= 12;
        ++_year;
    }

    while (_month < 1) {
        _month += 12;
        --_year;
        normalize();
    }
}

void CDate::addYear(int nb){
    _year += nb;
    normalize();
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
            newDate._day += nb;
            break;
        case CDate::SEMAINE:
            newDate._day += (nb * 7);
            break;
        case CDate::MOIS:
            newDate.addMonth(nb);
            break;
        case CDate::ANNEE:
            newDate.addYear(nb);
            break;
        }

        newDate.normalize();
    }

    return newDate;
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
        break;
    }

    str = oss.str();  // Assignez la chaîne résultante à str

    return str;
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
        break;
    }

    return str;
}

/************************** METHODE CONSTANT FIN *******************************************/

/************************** METHODE STATIC DEBUT *******************************************/

const bool CDate::yearIsValid(int year){
    return year >= 1;
}

const bool CDate::isLeapYear(int year) {
    // Une année bissextile est divisible par 4
    // Sauf si elle est également divisible par 100
    // Auquel cas, elle doit aussi être divisible par 400 pour être bissextile

    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

const bool CDate::monthIsValid(int month){
    // renvoie true ou false si le moi est compris entre 1 et 12
    return month >= 0 && month <= 12;
}

const bool CDate::dateIsValid(int day, int month, int year){

    // verifier si le mois et l'année sont valide
    if(!monthIsValid(month) ||  !yearIsValid(year)) return false;

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

const int CDate::daysInMonth(int month, int year){
    if(month == 0){
        time_t t = time(0);
        struct tm *currentTime = localtime(&t);

        month = currentTime->tm_mon + 1;
    }

    int daysInMonth = 31;
    // Si ce n'est pas un mois a 31 jours
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }else if (month == 2) {
        if(year == 0){
            time_t t = time(0);
            struct tm *currentTime = localtime(&t);
            year = currentTime->tm_year + 1900;
        }
        // si l'anné est bissextil et si on est en fevrier
        daysInMonth = CDate::isLeapYear(year) ? 29 : 28;
    }

    return daysInMonth;
}
/************************** METHODE STATIC FIN *******************************************/

/************************** Surcharge D'OPERATEUR DEBUT*******************************************/
std::ostream& operator<<(std::ostream& os, const CDate& date){
    os  << date._day << '/' << date._month << '/' << date._year;
    return os;
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

bool CDate::operator!=(const CDate& date) const{
    return _year != date._year || _month != date._month || _day != date._day;
}

bool CDate::operator<(const CDate& date) const {
    if (_year < date._year) {
        return true;
    } else if (_year > date._year) {
        return false;
    }

    if (_month < date._month) {
        return true;
    } else if (_month > date._month) {
        return false;
    }

    return _day < date._day;
}

bool CDate::operator>(const CDate& date) const{
    if (_year < date._year) {
        return false;
    } else if (_year > date._year) {
        return true;
    }

    if (_month < date._month) {
        return false;
    } else if (_month > date._month) {
        return false;
    }

    return _day > date._day;
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

    result._day += days;

    result.normalize();

    return result;
}

CDate CDate::operator-(const int days) const{
    CDate result = *this;

    result._day -= days;

    result.normalize();

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

    double diffDayInSeconds = difftime(mktime(&thisDate), mktime(&otherDate));


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
