#ifndef CCOMMERCIAL_H
#define CCOMMERCIAL_H

#include "cemployer.h"

class CCommercial : public CEmployer
{
private:
    float _CA;
public:
    CCommercial();
    CCommercial(std::string nom, std::string prenom, Statut statut, std::string adresse,
                CDate naissance, CDate embauche, float CA = 0);
    CCommercial(std::string nom, std::string prenom, Statut statut, std::string adresse,
                std::string naissance, std::string embauche, float CA = 0);
    float getCA();
    void setCA(float CA);
    float getSalaireBase() const override;
    float calculerSalaire(int nbHeureSupp) override;


};

#endif // CCOMMERCIAL_H
