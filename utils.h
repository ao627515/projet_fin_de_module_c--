#ifndef UTILS_H
#define UTILS_H

#include "cemployer.h"
#include "centreprise.h"


namespace utils {
    void insererEmploye (const CEmployer& emp);
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
    int generateRandomIndex(int maxIndex);
    CEmployer generateRandomEmployer();
    void generateEmpolyer(const int nb);
}


#endif // UTILS_H
