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
    void insererEmploye (const CEmployer& emp,  CEntreprise& entreprise);
    void insererEmploye (const std::shared_ptr<CEmployer>& emp, CEntreprise& entreprise);
    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query, CEntreprise& entreprise,  bool sensibleCase = true);
    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query, AttCEmployerResearch nomAtt, CEntreprise& entreprise, bool sensibleCase = true);
    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query,const std::vector<std::shared_ptr<CEmployer>>& CONTAINER, bool sensibleCase = true);
    void supprimerEmploye(const std::string& matricule, CEntreprise& entreprise);
    const void listeRetraites(CEntreprise& entreprise);
    const void listeRetraites(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const float masseSalariale(CEntreprise& entreprise);
    const float masseSalariale(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const void calculerSalaireEmpl(CEntreprise& entreprise);
    const void calculerSalaireEmpl(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const void fonctionnaires(CEntreprise& entreprise);
    const void fonctionnaires(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    const void conges(CEntreprise& entreprise);
    const void conges(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER);
    int generateRandomIndex(int maxIndex, int min = 0);
    CEmployer generateRandomEmployer();
    void generateEmpolyer(const int nb, CEntreprise& entreprise);
    std::string randomFonction(bool std = true);
    CTechnicien generateRandomTechnicien();
    CCommercial generateRandomCommercial();
    CManutentionnaire generateRandomManutentionnaire();
    std::shared_ptr<CEmployer> generateRandomStdEmploye();
    void employerRandomInit(std::string& nom, std::string& prenom, std::string& adresse, CDate& dateNaissance, CDate& dateEmbauche, CEmployer::Statut& statut, int& heureSup);
}


#endif // UTILS_H
