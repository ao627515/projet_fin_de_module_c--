#include "cdate.h"
#include "time.h"
#include "iostream"


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

    bool response = true;

    // verifier si le mois et l'année sont valide
    if(!monthIsValid(month) ||  !yearIsValid(year)) response = false;

    int daysInMonth = 31;

    // Si ce n'est pas un mois a 31 jours
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    }else if (month == 2) {
        // si l'anné est bissextil et si on est en fevrier
        daysInMonth = isLeapYear(year) ? 29 : 28;
    }

    // si le jour n'est compris entre 1 et le nombre de jours maximal du mois passé en parametre
    if(day < 1 || day > daysInMonth) response = false;

    return response;
}

/************************** METHODE STATIC FIN *******************************************/
