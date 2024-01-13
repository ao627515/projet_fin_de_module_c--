#ifndef CEMPLOYER_H
#define CEMPLOYER_H

#include "string"
#include "cdate.h"
#include "set"
#include "centreprise.h"

// Déclaration avancée de CEntreprise
// class CEntreprise;

enum class AttCEmployerResearch {MATRICULE, NOM, PRENOM, FONCTION, ADRESSE, DATE_NAISSANCE, DATE_EMBAUCHE, SALAIRE_BASE, HEURE_SUP};

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
        int _heureSup;
        static std::set<std::string> usedMatricules;
        size_t hashValue() const ;

    protected:
        static const float _BASE;
        static const float _PART;

    public:
        // static std::set<std::string> usedMatricules;
        friend struct CEmployerHash;
        CEmployer();
        CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                 CDate naissance, CDate embauche);
        CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                  std::string naissance, std::string embauche);
        CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                  CDate naissance, CDate embauche, float salaireBase);
        CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                  std::string naissance, std::string embauche, float salaireBase);

        // virtual float calculerSalaireBase();
        void augmenter(float pourcentage = 0.05);
        void supprimerDansListe(CEntreprise& entreprise) const;
        bool estAuxiliaire() const;
        bool estFonctionnaire() const;
        // virtual float calculerSalaireBase();
        virtual float calculerSalaire(int nbHeureSupp = 0);
        CDate dateRetraite() const;
        bool estAnneeRetraite(int annee) const;
        bool estRetraite() const;
        void afficher() const;
        int nbJoursDeConge(bool cadre = false) const;
        float cotisationRetraite() const;
        float cotisationProtectionSociale(float plafond) const;
        static std::string generateMatricule();
        int anciennete() const;

        // Accesseurs
        int getAge() const;
        std::string getNumeroMatricule() const;
        std::string getNom() const;
        std::string getPrenom() const;
        std::string getFonction() const;
        // std::string getStatut() const;
        CEmployer::Statut getStatut() const;
        std::string getAdresse() const;
        CDate getDateNaissance() const;
        CDate getDateEmbauche() const;
        virtual float getSalaireBase() const;
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
};

struct CEmployerHash {
    size_t operator()(const CEmployer& emp) const {
        return emp.hashValue();
    }
};

#endif // CEMPLOYER_H
