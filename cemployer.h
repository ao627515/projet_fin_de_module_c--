#ifndef CEMPLOYER_H
#define CEMPLOYER_H

#include "string"
#include "cdate.h"
#include "set"

static void throwInvalidArgumentIf(bool condition, std::string msg){
    if (condition) {
        throw std::invalid_argument(msg);
    }
}

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

class CEmployer {
    public:
        enum Statut {fonctionnaire, auxiliaire};

    private:
        const std::string _matricule;
        std::string _nom;
        std::string _prenom;
        std::string _fonction;
        Statut _statut;
        std::string _adresse;
        CDate _dateNaissance;
        CDate _dateEmbauche;
        float _salaireBase;
        int heureSup;
        // ne pas oublier
        // static std::set<std::string> usedMatricules;


    public:
        static std::set<std::string> usedMatricules;
        CEmployer() = delete;
        CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                 CDate naissance, CDate embauche, float salaireBase);
        CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                  std::string naissance, std::string embauche, float salaireBase);

        void augmenter(float pourcentage = 0.05);
        bool estAuxiliaire() const;
        bool estFonctionnaire() const;
        float calculerSalaire(int nbHeureSupp = 0) const;
        CDate dateRetraite() const;
        bool estAnneeRetraite(int annee) const;
        void afficher() const;
        int nbJoursDeConge(bool cadre = false) const;
        float cotisationRetraite() const;
        float cotisationProtectionSociale(float plafond) const;
        static std::string generateMatricule();

        // Accesseurs
        std::string getNumeroMatricule() const;
        std::string getNom() const;
        std::string getPrenom() const;
        std::string getFonction() const;
        // std::string getStatut() const;
        CEmployer::Statut getStatut() const;
        std::string getAdresse() const;
        CDate getDateNaissance() const;
        CDate getDateEmbauche() const;
        float getSalaireBase() const;
        int getHeureSup() const;

        // Modificateurs
        void setNom(std::string nom);
        void setPrenom(std::string prenom);
        void setFonction(std::string fonction);
        void setStatut(Statut statut);
        void setAdresse(std::string adresse);
        void setDateNaissance(CDate date_naiss);
        void setDateEmbauche(CDate date_embauche);
        void setDateNaissance(std::string date_naiss);
        void setDateEmbauche(std::string date_embauche);
        void setSalaireBase(float salaireBase);
        void setHeureSup(int nbHeureSup);

        // test
};

namespace CEmployerProgTest {
void test_setteur_getteur_construct();
}
#endif // CEMPLOYER_H
