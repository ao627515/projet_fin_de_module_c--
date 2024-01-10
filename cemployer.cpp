#include "cemployer.h"
#include <random>
/*********************************** ParametresEntreprise ***********************************/
double ParametresEntreprise::plafondProtectionSociale = 5000.0;
double ParametresEntreprise::tauxHoraire = 0.02;
double ParametresEntreprise::tauxHoraireMajore = 0.025;
int ParametresEntreprise::ageRetraite = 65;
int ParametresEntreprise::heureMajore = 100;

// setteur
void ParametresEntreprise::setPlafondProtectionSociale(double plafond){
    ParametresEntreprise::plafondProtectionSociale = plafond;
}

void ParametresEntreprise::setTauxHoraire(double taux){
    throwInvalidArgumentIf(taux < 0, "Le taux horaire doit etre sup a 0");
    ParametresEntreprise::tauxHoraire = taux;
}

void ParametresEntreprise::setTauxHoraireMajore(double tauxMajore){
    throwInvalidArgumentIf(tauxMajore  < ParametresEntreprise::tauxHoraire,
                           "Le taux horaire majorer doit ere sup aux taux horaire : " + std::to_string(ParametresEntreprise::tauxHoraire));
    ParametresEntreprise::tauxHoraireMajore = tauxMajore;
}

void ParametresEntreprise::setAgeRetraite(int age){
    throwInvalidArgumentIf(age <= 0, "Le l'age de retraite doit etre sup a 0");
    ParametresEntreprise::ageRetraite = age;
}

void ParametresEntreprise::setHeureMajore(int h){
    throwInvalidArgumentIf(h <= 0, "le nombre d'heure suppl majoré doit etre sup a 0");
    ParametresEntreprise::heureMajore = h;
}

// getteur
double ParametresEntreprise::getPlafondProtectionSociale(){
    return ParametresEntreprise::plafondProtectionSociale;
}

double ParametresEntreprise::getTauxHoraire(){
    return ParametresEntreprise::tauxHoraire;
}

double ParametresEntreprise::getTauxHoraireMajore(){
    return ParametresEntreprise::tauxHoraireMajore;
}

int ParametresEntreprise::getAgeRetraite(){
    return ParametresEntreprise::ageRetraite;
}

int ParametresEntreprise::getHeureMajore(){
    return ParametresEntreprise::heureMajore;
}

/*********************************** ParametresEntreprise ***********************************/

/*********************************** CEmployer ***********************************/
//
std::set<std::string> CEmployer::usedMatricules;
// Constructeur
CEmployer::CEmployer(std::string matricule, std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                     CDate naissance, CDate embauche){

}

// methode constante
// std::string CEmployer::generateMatricule(){
//     const char charset[] = "0123456789ABCDEFGHIJKLMNLOPQRSTUVWXYZ";
//     const int length = 8;

//     std::string matricule;

//     // Générer un matricule unique
//     do {
//         matricule.clear();  // Réinitialiser la chaîne

//         for (int i = 0; i < length; ++i) {
//             matricule.push_back(charset[rand() % (sizeof(charset) - 1)]);
//         }
//     } while (usedMatricules.count(matricule) > 0);  // Vérifier l'unicité

//     // Ajouter le matricule à l'ensemble pour éviter la répétition
//     usedMatricules.insert(matricule);

//     return matricule;
// }


std::string CEmployer::generateMatricule() {
    // Utiliser std::random_device pour obtenir une graine aléatoire plus sécurisée
    std::random_device rd;
    std::mt19937 gen(rd());

    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charsetSize = sizeof(charset) - 1;

    const int matriculeLength = 8;  // Définissez la longueur de votre matricule

    std::uniform_int_distribution<int> distribution(0, charsetSize - 1);

    std::string matricule;
    matricule.reserve(matriculeLength);

    for (int i = 0; i < matriculeLength; ++i) {
        matricule.push_back(charset[distribution(gen)]);
    }

    // Vérifier si le matricule existe déjà, regénérer si nécessaire (pour éviter les doublons)
    while (usedMatricules.find(matricule) != usedMatricules.end()) {
        matricule.clear();
        for (int i = 0; i < matriculeLength; ++i) {
            matricule.push_back(charset[distribution(gen)]);
        }
    }

    // Ajouter le nouveau matricule à l'ensemble des matricules utilisés
    usedMatricules.insert(matricule);

    return matricule;
}


// setteur

// void CEmployer::setNom(std::string nom);
// void CEmployer::setPrenom(std::string prenom);
// void CEmployer::setFonction(std::string fonction);
// void CEmployer::setStatut(Statut statut);
// void CEmployer::setAdresse(std::string adresse);
// void CEmployer::setDateNaissance(CDate date_naiss);
// void CEmployer::setDateEmbauche(CDate date_embauche);
// void CEmployer::setSalaireBase(double salaireBase);
// void CEmployer::setParametresEntreprise(ParametresEntreprise params);


/*********************************** CEmployer ***********************************/
