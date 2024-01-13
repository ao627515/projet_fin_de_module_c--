#ifndef UTILS_H
#define UTILS_H

#include "cemployer.h"
#include "centreprise.h"
#include "cemployer.h"
#include "ctechnicien.h"
#include "cmanutentionnaire.h"
#include "ccommercial.h"

static void throwInvalidArgumentIf(bool condition, std::string msg){
    if (condition) {
        throw std::invalid_argument(msg);
    }
}

namespace utils {
    void insererEmploye (const CEmployer& emp);
    void insererEmploye (const std::shared_ptr<CEmployer>& emp);
    // std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& nom);
    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query,  bool sensibleCase = true);
    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query, AttCEmployerResearch nomAtt, bool sensibleCase = true);
    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query,const std::vector<std::shared_ptr<CEmployer>>& CONTAINER, bool sensibleCase = true);
    void supprimerEmploye(const std::string& matricule);
    const void listeRetraites();
    const void listeRetraites(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const float masseSalariale();
    const float masseSalariale(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const void calculerSalaireEmpl(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const void fonctionnaires();
    const void fonctionnaires(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const void conges();
    const void conges(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    int generateRandomIndex(int maxIndex, int min = 0);
    CEmployer generateRandomEmployer();
    void generateEmpolyer(const int nb);
    std::string randomFonction(bool std = true);
    CTechnicien generateRandomTechnicien();
    CCommercial generateRandomCommercial();
    CManutentionnaire generateRandomManutentionnaire();
    std::shared_ptr<CEmployer> generateRandomStdEmploye();
    void employerRandomInit(std::string& nom, std::string& prenom, std::string& adresse, CDate& dateNaissance, CDate& dateEmbauche, CEmployer::Statut& statut, int& heureSup);
}


#endif // UTILS_H
