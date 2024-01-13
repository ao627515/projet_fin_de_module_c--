#include "cmanutentionnaire.h"
#include "centreprise.h"


const float CManutentionnaire::_BASE_SALAIRE_HORAIRE = 15.0;

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


float CManutentionnaire::calculerSalaireBase(){
     return _BASE_SALAIRE_HORAIRE * _nb_heures;
}

float CManutentionnaire::calculerSalaire(int nbHeureSupp)  {
    if (nbHeureSupp < 0) {
        throw std::invalid_argument("Le nombre d'heures supplémentaires ne peut être inférieur à 0");
    }

    float salaire = calculerSalaireBase();  // Initialisez avec le salaire de base

    if (nbHeureSupp > ParametresEntreprise::getHeureMajore()) {
        salaire += nbHeureSupp * ParametresEntreprise::getTauxHoraireMajore();
    } else {
        salaire += nbHeureSupp * ParametresEntreprise::getTauxHoraire();
    }

    return salaire;
}
