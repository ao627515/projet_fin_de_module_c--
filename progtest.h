#ifndef PROGTEST_H
#define PROGTEST_H

#include "cdate.h"
#include "centreprise.h"

namespace ProgTest {
    namespace Menu {
        const void pressAnyKeyToContinue();
        const int choiceAndError(int min, int max);
        bool restartOrExist();
    }

    namespace CDateTest {
        const void dateFormatChoice(char numSep = '-', bool m = true, bool a = true, bool c = true);
        const void dateFormatPrint(std::string message, CDate date, CDate::FORMAT format, bool clear = true);
        int mainMenu();
        void currentTIme();
        CDate::TYPE_PERIODE choicePeriode();
        int getNbPeriode(CDate::TYPE_PERIODE periode);
        void addPeriode();
        void diffBetweenTwoDates();
        void compareTwoDate();
        void formatDate();
        void isLeapYear();
        int progTest();
    }

        namespace CEmployerTest{
            void afficherMenu();
            void ajouterEmploye(CEntreprise& entreprise);
            void rechercherEmploye(CEntreprise& entreprise);
            void supprimerEmploye(CEntreprise& entreprise);
            void listerPersonnel(CEntreprise& entreprise);
            void listerRetraites(CEntreprise& entreprise);
            void masseSalarialeMensuelle(CEntreprise& entreprise);
            void miseEnConges(CEntreprise& entreprise);
            void test_setteur_getteur_construct();
            void progTest();
        }
}

#endif // PROGTEST_H
