#ifndef CENTREPRISE_H
#define CENTREPRISE_H

#include "cemployer.h"
#include "vector"
#include "memory"
// #include "unordered_set"

class CEmployer;

class ParametresEntreprise {
private:
    ParametresEntreprise() = delete;
    static float plafondProtectionSociale;
    static float tauxHoraire;
    static float tauxHoraireMajore;
    static int ageRetraite;
    static int heureMajore;

public:
    //
    static void setPlafondProtectionSociale(float plafond);
    static void setTauxHoraire(float taux);
    static void setTauxHoraireMajore(float tauxMajore);
    static void setAgeRetraite(int age);
    static void setHeureMajore(int h);

    //
    static float getPlafondProtectionSociale();
    static float getTauxHoraire();
    static float getTauxHoraireMajore();
    static int getAgeRetraite();
    static int getHeureMajore();
};

class CEntreprise
{
private:
    static std::vector<std::shared_ptr<CEmployer>> LIST_EMPLOYER;
    // static std::unordered_set<CEmployer, CEmployer::CEmployerHash> LISTEMPLOYER;
public:
    CEntreprise();
    static std::vector<std::shared_ptr<CEmployer>> getLIST_EMPLOYER();
    static void setLIST_EMPLOYER(const CEmployer& emp);
    friend struct CEmployerHash;
    friend class CEmployer;
};


#endif // CENTREPRISE_H
