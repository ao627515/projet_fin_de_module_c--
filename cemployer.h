#ifndef CEMPLOYER_H
#define CEMPLOYER_H

#include "string"
#include "cdate.h"

static void throwInvalidArgumentIf(bool condition, std::string msg){
    if (condition) {
        throw std::invalid_argument(msg);
    }
}

class ParametresEntreprise {
    private:
        ParametresEntreprise() = delete;
        static double plafondProtectionSociale;
        static double tauxHoraire;
        static double tauxHoraireMajore;
        static int ageRetraite;
        static int heureMajore;
    public:
        //
        static void setPlafondProtectionSociale(double plafond);
        static void setTauxHoraire(double taux);
        static void setTauxHoraireMajore(double tauxMajore);
        static void setAgeRetraite(int age);
        static void setHeureMajore(int h);

        //
        static double getPlafondProtectionSociale();
        static double getTauxHoraire();
        static double getTauxHoraireMajore();
        static int getAgeRetraite();
        static int getHeureMajore();
};

class CEmployer {
    public:
        enum Statut {fonctionnaire, auxiliaire};

    private:
        std::string _numeroMatricule;
        std::string _nom;
        std::string _prenom;
        std::string _fonction;
        Statut statut;
        std::string _adresse;
        CDate _dateNaissance;
        CDate _dateEmbauche;
        double _salaireBase;
        ParametresEntreprise _parametresEntreprise;

    public:
        CEmployer() = delete;
        CEmployer(std::string matricule, std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                 CDate naissance, CDate embauche);

        void augmenter(float pourcentage = 0.05);
        bool estAuxiliaire() const;
        double calculerSalaire(int nbHeureSupp = 0) const;
        CDate dateRetraite() const;
        bool estAnneeRetraite(int annee) const;
        void afficher() const;
        int nbJoursDeConge(bool cadre = false) const;
        double cotisationRetraite() const;
        double cotisationProtectionSociale(double plafond) const;

        // Accesseurs
        std::string getNumeroMatricule() const;
        std::string getNom() const;
        std::string getPrenom() const;
        std::string getFonction() const;
        Statut getStatut() const;
        std::string getAdresse() const;
        CDate getDateNaissance() const;
        CDate getDateEmbauche() const;
        double getSalaireBase() const;
        ParametresEntreprise getParametresEntreprise() const;

        // Modificateurs
        void setNumeroMatricule(std::string matricule);
        void setNom(std::string nom);
        void setPrenom(std::string prenom);
        void setFonction(std::string fonction);
        void setStatut(Statut statut);
        void setAdresse(std::string adresse);
        void setDateNaissance(CDate date_naiss);
        void setDateEmbauche(CDate date_embauche);
        void setSalaireBase(double salaireBase);
        void setParametresEntreprise(ParametresEntreprise params);
};
#endif // CEMPLOYER_H
