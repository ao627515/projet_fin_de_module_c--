#ifndef CMANUTENTIONNAIRE_H
#define CMANUTENTIONNAIRE_H

#include "cemployer.h"

class CManutentionnaire : public CEmployer
{
private:
    static const float _BASE_SALAIRE_HORAIRE;
    int _nb_heures;
public:
    CManutentionnaire();
    CManutentionnaire(std::string nom, std::string prenom, Statut statut, std::string adresse,
                      CDate naissance, CDate embauche, int nb_heures);
    CManutentionnaire(std::string nom, std::string prenom, Statut statut, std::string adresse,
                      std::string naissance, std::string embauche, int nb_heures);

    float calculerSalaireBase();
    float calculerSalaire(int nbHeureSupp) override;
};

#endif // CMANUTENTIONNAIRE_H
