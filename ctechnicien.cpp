#include "ctechnicien.h"
#include "centreprise.h"


const float CTechnicien::_GAIN_UNITE = ParametresEntreprise::getGAIN_UNITE();


CTechnicien::CTechnicien() : CEmployer(), _nb_unite_produite(0) {}

CTechnicien::CTechnicien(std::string nom, std::string prenom, Statut statut, std::string adresse,
                                     CDate naissance, CDate embauche, int nb_unite_produite) : CEmployer(nom, prenom, "technicien", statut, adresse, naissance, embauche), _nb_unite_produite(nb_unite_produite)
{
    //
}

CTechnicien::CTechnicien(std::string nom, std::string prenom, Statut statut, std::string adresse,
                                     std::string naissance, std::string embauche, int nb_unite_produite) : CEmployer(nom, prenom, "technicien", statut, adresse, naissance, embauche), _nb_unite_produite(nb_unite_produite)
{
    //
}


float CTechnicien::calculerSalaireBase(){
    return _BASE + _nb_unite_produite * _PART *  _GAIN_UNITE;
}

float CTechnicien::calculerSalaire(int nbHeureSupp)  {
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
