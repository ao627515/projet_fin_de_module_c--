#ifndef CDATE_H
#define CDATE_H


class CDate
{
    private:
        int _day;
        int _month;
        int _year;

            // Methodes

        // Methode non static
        void defaultDate();


    public:
        // Constructeur
        CDate();
        CDate(int day, int month = 0, int year = 0);

        // Methode non static
        void displayDate();
        // Methode static
        static const bool yearIsValid(int year);
        static const bool isLeapYear(int year);
        static const bool monthIsValid(int month);
        static const bool dateIsValid(int day, int month, int year);



};

#endif // CDATE_H
