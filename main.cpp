#include <iostream>
#include "cemployer.h"
#include "progtest.h"
#include "utils.h"
#include "centreprise.h"

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

void ajouterEmploye(){
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
        cout << endl;
        // Création de l'objet CEmployer
        CEmployer nouvelEmploye(nom, prenom, fonction, statut, adresse, dateNaissance, dateEmbauche, salaireBase);
        utils::insererEmploye(nouvelEmploye);

        ProgTest::Menu::pressAnyKeyToContinue();
        std::cout << std::endl;

    }while (ProgTest::Menu::restartOrExist());

}

void rechercherEmploye() {

    do{
        std::string nom;
        bool employeTrouve = false;
        std::cout << "\nEntrez le nom de l'employe a rechercher : ";
        std::cin >> nom;


        auto res = utils::rechercherEmploye(nom, AttCEmployerResearch::NOM);

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

void supprimerEmploye(){

    do{
        std::string matricule;
        bool employeTrouve = false;
        bool confirm;

        std::cout << "\nEntrez le matricule de l'employe a rechercher : ";
        std::cin >> matricule;

        auto res = utils::rechercherEmploye(matricule, AttCEmployerResearch::MATRICULE);

        if(!res.empty()) employeTrouve =  true;

        std::cout << std::endl;
        for(const auto& emp : res){
            emp->afficher();
            std::cout << std::endl;
        }

        if (!employeTrouve) {
            std::cout << "Aucun employe trouve avec le matricule " << matricule << ".\n";
             std::cout << std::endl;
            ProgTest::Menu::pressAnyKeyToContinue();
            std::cout << std::endl;
        }else{
            std::cout << "Voullez-vous vraiment supprimer les donnees de cette employe ? : 0 -> Non | 1 - Oui : ";
            cin >> confirm, cin.ignore();
            utils::supprimerEmploye(matricule);
            std::cout << std::endl << "supression reussi  "  << std::endl;
        }

    }while(ProgTest::Menu::restartOrExist());
}




int main(int argc, char *argv[])
{

    try {

        CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000);
        utils::insererEmploye(emp);
        // utils::generateEmpolyer(10);

        int choix;
        do {
            afficherMenu();
            choix = ProgTest::Menu::choiceAndError(0, 7);

            switch (choix) {
            case 0:
                std::cout << "Au revoir!\n";
                break;
            case 1:
                ajouterEmploye();
                break;
            case 2:
                rechercherEmploye();
                break;
            case 3:
                supprimerEmploye();
                break;
            case 4:
                // listerPersonnel();
                break;
            case 5:
                // listerRetraites();
                break;
            case 6:
                // masseSalarialeMensuelle();
                break;
            case 7:
                // miseEnConges();
                break;
            default:
                std::cout << "Choix invalide. Veuillez saisir un nombre entre 0 et 7.\n";
                break;
            }

        } while (choix != 0);

    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
