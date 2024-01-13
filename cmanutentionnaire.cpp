#include "cmanutentionnaire.h"
#include "centreprise.h"
#include "utils.h"


const float CManutentionnaire::_BASE_SALAIRE_HORAIRE = ParametresEntreprise::getBASE_SALAIRE_HORAIRE();

CManutentionnaire::CManutentionnaire() : CEmployer(), _nb_heures(0) {}

CManutentionnaire::CManutentionnaire(std::string nom, std::string prenom, Statut statut, std::string adresse,
                         CDate naissance, CDate embauche, int nb_heures) : CEmployer(nom, prenom, "manutentionnaire", statut, adresse, naissance, embauche), _nb_heures(nb_heures)
{
    //
}

CManutentionnaire::CManutentionnaire(std::string nom, std::string prenom, Statut statut, std::string adresse,
                         std::string naissance, std::string embauche, int nb_heures) : CEmployer(nom, prenom, "manutentionnaire", statut, adresse, naissance, embauche), _nb_heures(nb_heures)
{
    //
}


float CManutentionnaire::getSalaireBase() const{
     return _BASE_SALAIRE_HORAIRE * _nb_heures;
}

float CManutentionnaire::calculerSalaire(int nbHeureSupp)  {
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

void CManutentionnaire::setNbHeure(int h){
    throwInvalidArgumentIf(h < 0, "Argument invalid");
    _nb_heures = h;
}

int CManutentionnaire::getNbHeure() { return _nb_heures; }
