#include "centreprise.h"

/*********************************** ParametresEntreprise ***********************************/
float ParametresEntreprise::plafondProtectionSociale = 5000.0;
float ParametresEntreprise::tauxHoraire = 0.02;
float ParametresEntreprise::tauxHoraireMajore = 0.025;
int ParametresEntreprise::ageRetraite = 65;
int ParametresEntreprise::heureMajore = 100;

// ->>>>>>>>> setteur
void ParametresEntreprise::setPlafondProtectionSociale(float plafond){
    ParametresEntreprise::plafondProtectionSociale = plafond;
}

void ParametresEntreprise::setTauxHoraire(float taux){
    throwInvalidArgumentIf(taux < 0, "Le taux horaire doit etre sup a 0");
    ParametresEntreprise::tauxHoraire = taux;
}

void ParametresEntreprise::setTauxHoraireMajore(float tauxMajore){
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

// ->>>>>>>>> getteur
float ParametresEntreprise::getPlafondProtectionSociale(){
    return ParametresEntreprise::plafondProtectionSociale;
}

float ParametresEntreprise::getTauxHoraire(){
    return ParametresEntreprise::tauxHoraire;
}

float ParametresEntreprise::getTauxHoraireMajore(){
    return ParametresEntreprise::tauxHoraireMajore;
}

int ParametresEntreprise::getAgeRetraite(){
    return ParametresEntreprise::ageRetraite;
}

int ParametresEntreprise::getHeureMajore(){
    return ParametresEntreprise::heureMajore;
}

/*********************************** ParametresEntreprise ***********************************/

CEntreprise::CEntreprise() {}



std::vector<std::shared_ptr<CEmployer>> CEntreprise::LIST_EMPLOYER = {};

// std::unordered_set<CEmployer, CEmployer::CEmployerHash> CEntreprise::LISTEMPLOYER;


std::vector<std::shared_ptr<CEmployer>> CEntreprise::getLIST_EMPLOYER(){
    return LIST_EMPLOYER;
}
void CEntreprise::setLIST_EMPLOYER(const CEmployer& emp){
    LIST_EMPLOYER.push_back(std::make_shared<CEmployer>(emp));
}
