#include <iostream>
#include "cdate.h"

using namespace std;

int main()
{
    // CDate d1;
    // d1.displayDate(); // -> 1/1/1970 v

    // CDate d2(14,7,2003);
    // d2.displayDate(); // -> 14/7/2003 v

    // CDate d3(14,7) ;
    // d3.displayDate(); // -> 14/7/2023 v

    // CDate d4(14);
    // d4.displayDate(); // -> 14/12/2023 v

    // CDate d5(0);
    // d5.displayDate(); // -> 30/12/2023 v

    // CDate d6(d2);
    // d6.displayDate(); // -> 14/7/2003 v

    // CDate d7 = d1;
    // d7.displayDate();  // -> 1/1/1970 v

    // CDate d8(12, 11, 2012);
    // cout << d8.lireJour() << endl; //renvoie 12 v
    // cout << d8.lireMois() << endl; //renvoie 11 v
    // cout << d8.lireAnnee() << endl; //renvoie 2012 v

    // CDate d9(26, 11, 2003);
    // cout << d9 << endl; // -> 26/11/2003 v

    // CDate d10;
    // cout << "Entrer une date : ";
    // cin >> d10;
    // cout << d10 << endl;

    // cout << (d1 == d7) << endl; // true
    // cout << (d1 == d2) << endl; // false

    // cout << (d1 != d7) << endl; // false
    // cout << (d1 != d2) << endl; // true

    // cout << (d1 < d7) << endl; // false
    // cout << (d1 < d2) << endl; // true

    // cout << (d1 > d7) << endl; // false
    // cout << (d1 > d2) << endl; // false
    // cout << (d2 > d1) << endl; // true

    // cout << (d1 >= d7) << endl; // true
    // cout << (d1 >= d2) << endl; // false
    // cout << (d2 >= d1) << endl; // true

    // cout << (d1 <= d7) << endl; // true
    // cout << (d1 <= d2) << endl; // true
    // cout << (d2 <= d1) << endl; // false


    // cout << d3 << endl;
    // d2 = d1;
    // cout << d3 << endl;

    // cout << d1 << endl;
    // d1 = d1 + 1000;
    // cout << d1 << endl;

    // cout << d7 << endl;
    // d7.addDays(1000);
    // cout << d7 << endl;

    // cout << d7 << endl;
    // d7 += 31;
    // cout << d7 << endl;

    // cout << d2 << endl;
    // d2 -= 13;
    // cout << d2 << endl;

    // cout << d7 << endl;
    // ++d7;
    // cout << d7 << endl;
    // --d7;
    // cout << d7 << endl;
    // d2 = d7++;
    // cout << d2 << endl;
    // cout << d7 << endl;
    // d2 = d7--;
    // cout << d2 << endl;
    // cout << d7 << endl;

    // d2 = "30/1/2023";
    // d1 = "1/1/2023";
    // cout << d2 << endl;
    // cout << d1 << endl;
    // int a = d2 - d1;
    // cout << a << endl;

    // CDate d(12, 11, 2012);
    // cout << d.ajouterPeriode(10, CDate ::JOUR) << endl; // renvoie la date 22/11/2012
    // cout << d.ajouterPeriode(2, CDate ::SEMAINE) << endl; // //renvoie la date 26/11/2012
    // cout << d.ajouterPeriode(10, CDate ::MOIS) << endl; // renvoie la date 12/9/2013
    // cout << d.ajouterPeriode(-10, CDate ::ANNEE) << endl; // //renvoie la date 12/11/2002
    // cout << d << endl;
    // CDate d(31, 5, 2012);
    // cout << d.ajouterPeriode(1, CDate ::MOIS) << endl; //renvoie la date 30/6/2012

    // CDate d(29, 2, 2000);
    // cout << d.ajouterPeriode(-3, CDate ::ANNEE) << endl; // renvoie la date 28/2/1997
    // cout << d.ajouterPeriode(3, CDate ::ANNEE) << endl; // renvoie la date 28/2/2003

    // CDate d(12, 11, 2012);
    // string s, j, m;
    // cout << d.formater(s, CDate ::MINIMAL) << endl; //renvoie et place dans s, 12/11/2012
    // cout << s << endl;
    // cout << d.formater(s, CDate ::ABREGE) << endl; //renvoie et place dans s, Lun 12 Nov 2012
    // cout << s << endl;
    // cout << d.formater(s, CDate ::COMPLET) << endl;//renvoie et place dans s,Lundi 12 Novembre 2012
    // cout << s << endl;

    // cout << d.trouverNomJour(j, CDate ::MINIMAL) << endl; //renvoie et place dans j, Erreur
    // cout << j << endl;
    // cout << d.trouverNomJour(j, CDate ::ABREGE) << endl; //renvoie et place dans j,Lun
    // cout << j << endl;
    // cout << d.trouverNomJour(j, CDate ::COMPLET) << endl; //renvoie et place dans j, Lundi
    // cout << j << endl;

    // cout << d.trouverNomMois(m, CDate ::MINIMAL) << endl; //renvoie et place dans m, 11
    // cout << m << endl;
    // cout << d.trouverNomMois(m, CDate :: ABREGE) << endl; //renvoie et place dans m, Nov
    // cout << m << endl;
    // cout <<  d.trouverNomMois(m, CDate :: COMPLET) << endl; //renvoie et place dans m, Novembre
    // cout << m << endl;


    return 0;
}
