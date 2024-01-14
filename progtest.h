#ifndef PROGTEST_H
#define PROGTEST_H

#include "cdate.h"
#include "centreprise.h"

namespace ProgTest {
    namespace Menu {
        const void pressAnyKeyToContinue();
        const int choiceAndError(int min, int max);
        bool restartOrExist();
    } // namespace Menu

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
    } // namespace CDateTest

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
        void progTest(CEntreprise entreprise, bool cemployerProgTest = false);
    } // namespace CEmployerTest

    namespace  CEntrepriseTest{
        void afficherEntreprise(const CEntreprise& entreprise);
        void afficherMenu();
        void menuModifier();
        void modifierEntreprise(CEntreprise& entreprise);
        void progTest();
        void progTestSwitch(int choix, CEntreprise& entreprise);

        namespace IT2Entreprise {
            void afficherMenu();
            void progTest();
        } // namespace IT2Entreprise

        namespace ModifierAtt {
            void finModification();
            void nom(CEntreprise& entreprise);
            void adresse(CEntreprise& entreprise);
        } // namespace ModifierAtt

    } // namespace CEntrepriseTest

} // namespace ProgTest

#endif // PROGTEST_H
