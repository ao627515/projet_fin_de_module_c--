#include "ccommercial.h"
#include "centreprise.h"
#include "utils.h"

CCommercial::CCommercial(): CEmployer(), _CA(0) {}

CCommercial::CCommercial(std::string nom, std::string prenom, Statut statut, std::string adresse,
                         CDate naissance, CDate embauche, float CA) : CEmployer(nom, prenom, "commercial", statut, adresse, naissance, embauche), _CA(CA)
{
    //
}

CCommercial::CCommercial(std::string nom, std::string prenom, Statut statut, std::string adresse,
                         std::string naissance, std::string embauche, float CA) : CEmployer(nom, prenom, "commercial", statut, adresse, naissance, embauche), _CA(CA)
{
    //
}


float CCommercial::getSalaireBase() const{
    return _BASE + _CA * _PART;
}

float CCommercial::calculerSalaire(int nbHeureSupp)  {
    if (nbHeureSupp < 0) {
        throw std::invalid_argument("Le nombre d'heures supplémentaires ne peut être inférieur à 0");
    }

    float salaire = getSalaireBase();  // Initialisez avec le salaire de base

    if (nbHeureSupp > ParametresEntreprise::getHeureMajore()) {
        salaire += nbHeureSupp * ParametresEntreprise::getTauxHoraireMajore();
    } else {
        salaire += nbHeureSupp * ParametresEntreprise::getTauxHoraire();
    }

    return salaire;
}

float CCommercial::getCA(){
    return _CA;
}
void CCommercial::setCA(float CA){
    throwInvalidArgumentIf(CA < 0, "Argument invalid");
    _CA = CA;
}
