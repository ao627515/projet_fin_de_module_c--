#ifndef CDATE_H
#define CDATE_H

#include "iostream"
#include "string"
#include "array"

class CDate
{
    private:
        int _day;
        int _month;
        int _year;

        static const std::array<std::string, 7> _DAYS ;
        static const std::array<std::string, 12> _MONTHS;

            // Methodes

        // Methode non static
        void defaultDate();
        // void normalize();

    public:
        enum TYPE_PERIODE { JOUR, SEMAINE, MOIS, ANNEE };
        enum FORMAT {MINIMAL, COMPLET, ABREGE};

        // Constructeur
        CDate();
        CDate(int day, int month = 0, int year = 0);
        CDate(const CDate &date);
        CDate(const std::string date);

        // Methode constante
        int lireJour() const;
        int lireMois() const;
        int lireAnnee() const;
        CDate ajouterPeriode(int nb, const TYPE_PERIODE periode) const;
        std::string formater(std::string& str, FORMAT format) const;
        std::string trouverNomJour(std::string& str, FORMAT format) const;
        std::string trouverNomMois(std::string& str, FORMAT format) const;

        // Methode normal
        void displayDate();
        void addDays(int days);
        void subtractDays(int days);
        void addMonth(int nb);
        void addYear(int nb);


        // Methode static
        static const bool yearIsValid(int year);
        static const bool isLeapYear(int year);
        static const bool monthIsValid(int month);
        static const bool dateIsValid(int day, int month, int year);
        static const int daysInMonth(int month = 0, int year = 0);
        static const int currentDay();
        static const int currentMonth();
        static const int currentYear();


        // Surcharge des operateur
        friend std::ostream& operator<<(std::ostream& os, const CDate& date);
        friend std::istream& operator>>(std::istream& is, CDate& date);
        bool operator==(const CDate& date) const;
        bool operator!=(const CDate& date) const;
        bool operator<(const CDate& date) const;
        bool operator>(const CDate& date) const;
        bool operator<=(const CDate& date) const;
        bool operator>=(const CDate& date) const;
        CDate& operator=(const  CDate& date);
        CDate& operator=(const  std::string date);
        CDate operator+(const int days) const;
        CDate operator-(const int days) const;
        int  operator-(const CDate& date) const;
        CDate& operator+=(const int days);
        CDate& operator-=(const int days);
        CDate& operator++();
        CDate& operator--();
        CDate operator++(int);
        CDate operator--(int);
};

#endif // CDATE_H
