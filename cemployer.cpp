#include "cemployer.h"

/*********************************** ParametresEntreprise ***********************************/
double ParametresEntreprise::plafondProtectionSociale = 5000.0;
double ParametresEntreprise::tauxHoraire = 0.02;
double ParametresEntreprise::tauxHoraireMajore = 0.025;
int ParametresEntreprise::ageRetraite = 65;
int ParametresEntreprise::heureMajore = 100;

//
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

//
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


