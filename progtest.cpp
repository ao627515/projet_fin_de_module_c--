#include "progtest.h"
#include "iostream"
#include "conio.h"
#include "cemployer.h"
#include "utils.h"



namespace ProgTest{
    namespace Menu {
        using namespace std;

        const void pressAnyKeyToContinue(){
            cout << endl << "Appuyer sur une touche pour continuer "; getch(), cout << flush, cout << endl;
        }

        const int choiceAndError(int min, int max){
            int option = 0;
            cout << "**************" << endl;
            cout << "Choix : "; cin >> option; cin.ignore();
            cout << "**************" << endl;

            if(option < min || option > max){
                cout << "=======================================================" << endl;
                cout << "Veuillez enter un nombre compris entre  "<< min <<" et " << max << endl;
                Menu::pressAnyKeyToContinue();
            }

            return option;
        }

        bool restartOrExist(){
            bool option = 0;
            bool min = 0, max = 1;

            do{
                cout << "1- Recomencer" << endl;
                cout << "0- Menu pricipal" << endl;
                option = Menu::choiceAndError(min, max);
                system("cls");
            }while(option < min || option > max);
            system("cls");
            return option;
        }
    }
    namespace CDateTest
    {
        using namespace std;



        const void dateFormatChoice(char numSep, bool m, bool a, bool c){
            int x = 1;

            cout << "Sous quelle format souhaitez-vous afficher la date" << endl << endl;
            if(m) cout << x << numSep << " Minimal ex : 1/1/1970" << endl, ++x;
            if(a) cout << x << numSep << " Abrege ex : jeu 1 jan 1970" << endl, ++x;
            if(c) cout << x << numSep << " Complet ex : jeudi 1 janvier 1970" << endl, ++x;
        }

        const void dateFormatPrint(string message, CDate date, CDate::FORMAT format, bool clear){
            cout << message << date.formater(format) << endl ;
            Menu::pressAnyKeyToContinue();
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
                option = Menu::choiceAndError(min, max);
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
                    option = Menu::choiceAndError(min, max);
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
                option = Menu::choiceAndError(min, max);
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
                        Menu::pressAnyKeyToContinue();
                        system("cls");
                    }
                } while (!dateIsInvalid || dateIsBefore1970);



                periode = choicePeriode();
                nbPeriode = getNbPeriode(periode);

                do{
                    cout << endl;
                    dateFormatChoice();
                    option = Menu::choiceAndError(min, max);
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
                continuous = Menu::restartOrExist();
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
                        Menu::pressAnyKeyToContinue();
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
                        Menu::pressAnyKeyToContinue();
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
                continuous = Menu::restartOrExist();
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
                        Menu::pressAnyKeyToContinue();
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
                        Menu::pressAnyKeyToContinue();
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
                        Menu::pressAnyKeyToContinue();
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
                continuous = Menu::restartOrExist();
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
                        Menu::pressAnyKeyToContinue();
                        cout << endl << endl;
                    }
                } while (!dateIsInvalid || dateIsBefore1970);


                do{
                    cout << endl;
                    dateFormatChoice('-', false);
                    cout << "0- Menu Precedent" << endl;
                    option = Menu::choiceAndError(min, max);
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
                    continuous = Menu::restartOrExist();
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

                continuous = Menu::restartOrExist();

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

    namespace CEmployerTest {
        using namespace std;
        void afficherMenu() {
            std::cout << "0. Quitter\n"
                      << "1. Ajout d'un employe\n"
                      << "2. Recherche d'un employe\n"
                      << "3. Suppression d'un employe\n"
                      << "4. Liste du personnel\n"
                      << "5. Liste des retraites\n"
                      << "6. Masse salariale mensuelle\n"
                      << "7. Mise en conges\n";
        }

        void ajouterEmploye(CEntreprise& entreprise){
            std::string nom, prenom, fonction, adresse, dateNaissance, dateEmbauche;
            float salaireBase;
            CEmployer::Statut statut;

            do{
                cout << endl;
                // Saisie des informations de l'employé
                std::cout << "Nom de l'employe: ";
                std::getline(std::cin, nom);

                std::cout << "Prenom de l'employe: ";
                std::getline(std::cin, prenom);

                std::cout << "Fonction de l'employe: ";
                std::getline(std::cin, fonction);

                std::cout << "Statut de l'employe (0: fonctionnaire, 1: auxiliaire): ";
                int statutInput;
                std::cin >> statutInput;
                statut = static_cast<CEmployer::Statut>(statutInput);

                std::cin.ignore();  // Ignorer le retour à la ligne

                std::cout << "Adresse de l'employe: ";
                std::getline(std::cin, adresse);

                std::cout << "Date de naissance de l'employe (jj/mm/aaaa): ";
                std::getline(std::cin, dateNaissance);

                std::cout << "Date d'embauche de l'employe (jj/mm/aaaa): ";
                std::getline(std::cin, dateEmbauche);

                std::cout << "Salaire de base de l'employe: ";
                std::cin >> salaireBase;

                // Création de l'objet CEmployer
                CEmployer nouvelEmploye(nom, prenom, fonction, statut, adresse, dateNaissance, dateEmbauche, salaireBase);
                utils::insererEmploye(nouvelEmploye, entreprise);

                ProgTest::Menu::pressAnyKeyToContinue();
                std::cout << std::endl;

            }while (ProgTest::Menu::restartOrExist());

        }

        void rechercherEmploye(CEntreprise& entreprise) {

            do{
                std::string nom;
                bool employeTrouve = false;
                std::cout << "\nEntrez le nom de l'employe a rechercher : ";
                std::cin >> nom;


                auto res = utils::rechercherEmploye(nom, AttCEmployerResearch::NOM, entreprise, false);

                if(!res.empty()) employeTrouve =  true;

                std::cout << std::endl;
                for(const auto& emp : res){
                    emp->afficher();
                    std::cout << std::endl;
                }


                if (!employeTrouve) {
                    std::cout << "Aucun employe trouve avec le matricule " << nom << ".\n";
                    ProgTest::Menu::pressAnyKeyToContinue();
                    std::cout << std::endl;
                }else{
                    ProgTest::Menu::pressAnyKeyToContinue();
                    std::cout << std::endl;
                }

            }while(ProgTest::Menu::restartOrExist());
        }

        void supprimerEmploye(CEntreprise& entreprise) {

            do{
                std::string matricule;
                bool employeTrouve = false;
                bool confirm;

                std::cout << "\nEntrez le matricule de l'employe a rechercher : ";
                std::cin >> matricule;

                auto res = utils::rechercherEmploye(matricule, AttCEmployerResearch::MATRICULE, entreprise);

                if(!res.empty()) employeTrouve =  true;

                std::cout << std::endl;
                for(const auto& emp : res){
                    emp->afficher();
                    std::cout << std::endl;
                }

                if (!employeTrouve) {
                    std::cout << "Aucun employe trouve avec le matricule " << matricule << ".\n";
                    ProgTest::Menu::pressAnyKeyToContinue();
                    std::cout << std::endl;
                }else{
                    std::cout << "Voullez-vous vraiment supprimer les donnees de cette employe ? : 0 -> Non | 1 - Oui : ";
                    cin >> confirm, cin.ignore();
                    utils::supprimerEmploye(matricule, entreprise);
                    std::cout << std::endl;
                    if(confirm){
                        std::cout << "Supression reussi  !"  << std::endl << std::endl;
                    }
                }

            }while(ProgTest::Menu::restartOrExist());
        }

        void listerPersonnel(CEntreprise& entreprise) {
            cout << endl << "Liste du personnel" << endl << endl;

            for(const auto& emp : entreprise.getLIST_EMPLOYER()){
                emp->afficher();
                cout << endl;
            }

            ProgTest::Menu::pressAnyKeyToContinue();
        }

        void listerRetraites(CEntreprise& entreprise) {
            bool empty = true;
            cout << endl << "Liste des retraite" << endl << endl;

            for(const auto& emp : entreprise.getLIST_EMPLOYER()){
                if(emp->estRetraite()){
                    empty = false;
                    emp->afficher();
                    cout << endl;
                }
            }

            if(empty) cout << "Aucun retraite trouve" << endl;

            ProgTest::Menu::pressAnyKeyToContinue();
        }

        void masseSalarialeMensuelle(CEntreprise& entreprise) {
            cout << endl << "La masse Salariale Mensuelle est de : " << utils::masseSalariale(entreprise) << endl;

            ProgTest::Menu::pressAnyKeyToContinue();
        }

        void  miseEnConges(CEntreprise& entreprise) {
            utils::conges(entreprise);
            ProgTest::Menu::pressAnyKeyToContinue();
        }

        void progTest() {
            CEntreprise entreprise("ODG-Enterprise", "Sillicon vallet");
            CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000);
            utils::insererEmploye(emp, entreprise);
            utils::generateEmpolyer(10, entreprise);
            int choix;
            do {
                afficherMenu();
                choix = ProgTest::Menu::choiceAndError(0, 7);

                switch (choix) {
                case 0:
                    std::cout << "Au revoir!\n";
                    break;
                case 1:
                    ajouterEmploye(entreprise);
                    break;
                case 2:
                    rechercherEmploye(entreprise);
                    break;
                case 3:
                    supprimerEmploye(entreprise);
                    break;
                case 4:
                    listerPersonnel(entreprise);
                    break;
                case 5:
                    listerRetraites(entreprise);
                    break;
                case 6:
                    masseSalarialeMensuelle(entreprise);
                    break;
                case 7:
                    miseEnConges(entreprise);
                    break;
                default:
                    std::cout << "Choix invalide. Veuillez saisir un nombre entre 0 et 7.\n";
                    break;
                }

            } while (choix != 0);
        }

        void test_setteur_getteur_construct(){

            CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000.0);

            // Utilisation des getters
            std::cout << "Matricule: " << emp.getNumeroMatricule() << std::endl;
            std::cout << "Nom: " << emp.getNom() << std::endl;
            std::cout << "Prenom: " << emp.getPrenom() << std::endl;
            std::cout << "Fonction: " << emp.getFonction() << std::endl;
            std::cout << "Statut: " << (emp.getStatut() == CEmployer::fonctionnaire ? "Fonctionnaire" : "Auxiliaire") << std::endl;
            std::cout << "Adresse: " << emp.getAdresse() << std::endl;
            std::cout << "Date de Naissance: " << emp.getDateNaissance() << std::endl;
            std::cout << "Date d'embauche: " << emp.getDateEmbauche() << std::endl;
            std::cout << "Salaire de base: " << emp.getSalaireBase() << std::endl;

            // Utilisation des setters
            emp.setNom("NouveauNom");
            emp.setPrenom("NouveauPrenom");
            emp.setFonction("NouvelleFonction");
            emp.setStatut(CEmployer::auxiliaire);
            emp.setAdresse("NouvelleAdresse");
            emp.setDateNaissance("01/01/1990");
            emp.setDateEmbauche("01/01/2022");
            emp.setSalaireBase(60000.0);

            // Affichage après modification
            std::cout << "\nAprès modification :\n";
            std::cout << "Nom: " << emp.getNom() << std::endl;
            std::cout << "Prenom: " << emp.getPrenom() << std::endl;
            std::cout << "Fonction: " << emp.getFonction() << std::endl;
            std::cout << "Statut: " << (emp.getStatut() == CEmployer::fonctionnaire ? "Fonctionnaire" : "Auxiliaire") << std::endl;
            std::cout << "Adresse: " << emp.getAdresse() << std::endl;
            std::cout << "Date de Naissance: " << emp.getDateNaissance() << std::endl;
            std::cout << "Date d'embauche: " << emp.getDateEmbauche() << std::endl;
            std::cout << "Salaire de base: " << emp.getSalaireBase() << std::endl;
        }
    }
}
