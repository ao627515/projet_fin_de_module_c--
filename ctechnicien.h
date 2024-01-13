#ifndef CTECHNICIEN_H
#define CTECHNICIEN_H

#include "cemployer.h"

class CTechnicien : public CEmployer
{
private:
    int _nb_unite_produite;
    static const float _GAIN_UNITE;
public:
    CTechnicien();
    CTechnicien(std::string nom, std::string prenom, Statut statut, std::string adresse,
                             CDate naissance, CDate embauche, int nb_unite_produite);
    CTechnicien(std::string nom, std::string prenom, Statut statut, std::string adresse,
                std::string naissance, std::string embauche, int nb_unite_produite);
    float calculerSalaireBase();
    float calculerSalaire(int nbHeureSupp) override;
};

#endif // CTECHNICIEN_H
