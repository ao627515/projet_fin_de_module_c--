#include "cemployer.h"
#include <random>
#include "iostream"
#include "centreprise.h"
#include "utils.h"


/*********************************** CEmployer ***********************************/

// ->>>>>>>>> atributs

const float CEmployer::_BASE = ParametresEntreprise::getBASE_SALAIRE();  // Partie fixe du salaire de base
const float CEmployer::_PART = ParametresEntreprise::getPART_SALAIRE();  // Partie variable du salaire de base

std::set<std::string> CEmployer::usedMatricules = {};


// ->>>>>>>>> Constructeur
CEmployer::CEmployer(){
    setNom("nom");
    setPrenom("prenom");
    setFonction("fonction");
    setAdresse("adresse");
    setSalaireBase(0);
    setDateNaissance(CDate());
    setDateEmbauche(CDate());
    setStatut(Statut::fonctionnaire);
    setHeureSup(0);
}

CEmployer::CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                     CDate naissance, CDate embauche)
    : _matricule{generateMatricule()}
{
    setNom(nom);
    setPrenom(prenom);
    setFonction(fonction);
    setAdresse(adresse);
    setSalaireBase(0);
    setDateNaissance(naissance);
    setDateEmbauche(embauche);
    setStatut(statut);
    setHeureSup(0);
}

CEmployer::CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                     std::string naissance, std::string embauche)
    : _matricule{generateMatricule()}
{
    setNom(nom);
    setPrenom(prenom);
    setFonction(fonction);
    setAdresse(adresse);
    setSalaireBase(0);
    setDateNaissance(CDate(naissance));
    setDateEmbauche(CDate(embauche));
    setStatut(statut);
    setHeureSup(0);
}

CEmployer::CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                     CDate naissance, CDate embauche, float salaireBase)
    : _matricule{generateMatricule()}
{
    setNom(nom);
    setPrenom(prenom);
    setFonction(fonction);
    setAdresse(adresse);
    setSalaireBase(salaireBase);
    setDateNaissance(naissance);
    setDateEmbauche(embauche);
    setStatut(statut);
    setHeureSup(0);
}

CEmployer::CEmployer(std::string nom, std::string prenom, std::string fonction, Statut statut, std::string adresse,
                     std::string naissance, std::string embauche, float salaireBase)
    : _matricule{generateMatricule()}
{
    setNom(nom);
    setPrenom(prenom);
    setFonction(fonction);
    setAdresse(adresse);
    setSalaireBase(salaireBase);
    setDateNaissance(CDate(naissance));
    setDateEmbauche(CDate(embauche));
    setStatut(statut);
    setHeureSup(0);
}


// ->>>>>>>>>>>>

size_t CEmployer::hashValue() const {
    // Utilisez les valeurs de hachage des membres pertinents pour le calcul du hachage
    return std::hash<std::string>()(_matricule) ^
           std::hash<std::string>()(_nom) ^
           std::hash<std::string>()(_prenom) ^
           std::hash<std::string>()(_fonction) ^
           std::hash<int>()(static_cast<int>(_statut)) ^
           std::hash<std::string>()(_adresse) ^
           _dateNaissance.hashValue() ^
           _dateEmbauche.hashValue() ^
           std::hash<float>()(_salaireBase) ^
           std::hash<int>()(_heureSup);
}


// ->>>>>>>>> methode constante
bool CEmployer::estAuxiliaire() const{ return _statut == CEmployer::auxiliaire; }

bool CEmployer::estFonctionnaire() const {return _statut == CEmployer::fonctionnaire; }

float CEmployer::calculerSalaire(int nbHeureSupp) {
    if (nbHeureSupp < 0) {
        throw std::invalid_argument("Le nombre d'heures supplémentaires ne peut être inférieur à 0");
    }

    float salaire = _salaireBase;  // Initialisez avec le salaire de base

    if (nbHeureSupp > ParametresEntreprise::getHeureMajore()) {
        salaire += nbHeureSupp * ParametresEntreprise::getTauxHoraireMajore();
    } else {
        salaire += nbHeureSupp * ParametresEntreprise::getTauxHoraire();
    }

    return salaire;
}

CDate CEmployer::dateRetraite() const{
    // age de l'employer
    int age = CDate::currentTime().lireAnnee() - _dateNaissance.lireAnnee();

    // nombre d'anné qu'il reste avant l'age de retraite
    int yearToWork = ParametresEntreprise::getAgeRetraite() - age;

    // on joute yearToWork a la date d'embauche pour avoir la date de retraite
    return _dateEmbauche.ajouterPeriode(yearToWork, CDate::ANNEE);
}

bool CEmployer::estAnneeRetraite(int annee) const{
    return annee == dateRetraite().lireAnnee();
}

void CEmployer::afficher() const {
    std::cout << "Matricule: " << getNumeroMatricule() << std::endl;
    std::cout << "Nom: " << getNom() << std::endl;
    std::cout << "Prenom: " << getPrenom() << std::endl;
    std::cout << "Fonction: " << getFonction() << std::endl;
    std::cout << "Statut: " << (getStatut() == CEmployer::fonctionnaire ? "Fonctionnaire" : "Auxiliaire") << std::endl;
    std::cout << "Adresse: " << getAdresse() << std::endl;
    std::cout << "Date de Naissance: " << getDateNaissance().formater(CDate::ABREGE) << std::endl;
    std::cout << "Date d'embauche: " << getDateEmbauche().formater(CDate::ABREGE)  << std::endl;
    std::cout << "Salaire de base: " << getSalaireBase() << std::endl;
}

int CEmployer::getAge() const {
    return CDate::currentTime().lireAnnee() - _dateNaissance.lireAnnee();
}

int CEmployer::anciennete() const {
    return CDate::currentTime().lireAnnee() - _dateEmbauche.lireAnnee();
}

int CEmployer::nbJoursDeConge(bool cadre) const {
    const int AGE_MINIMUM_CADRE_1 = 35;
    const int AGE_MINIMUM_CADRE_2 = 45;
    const int ANCIENNETE_MINIMUM_CADRE_1 = 3;
    const int ANCIENNETE_MINIMUM_CADRE_2 = 5;

    int nbDoff = 0;

    int moisAnciennete = _dateEmbauche.calculateMonthDifference(CDate::currentTime());

    if (moisAnciennete < 12) {
        nbDoff = 2;
    } else {
        nbDoff = 28;
    }

    if (cadre && getAge() >= AGE_MINIMUM_CADRE_1 && anciennete() > ANCIENNETE_MINIMUM_CADRE_1) {
        nbDoff += 2;
    }

    if (cadre && getAge() >= AGE_MINIMUM_CADRE_2 && anciennete() > ANCIENNETE_MINIMUM_CADRE_2) {
        nbDoff += 4;
    }

    return nbDoff;
}

void CEmployer::supprimerDansListe() const{
    // Utilisation d'un itérateur pour parcourir la liste
    auto it = CEntreprise::LIST_EMPLOYER.begin();

    // Parcourir la liste
    while (it != CEntreprise::LIST_EMPLOYER.end()) {
        // Vérifier si le nom correspond
        if ((*it)->getNumeroMatricule() == _matricule) {
            // Supprimer l'employé
            it = CEntreprise::LIST_EMPLOYER.erase(it);
        } else {
            // Passer à l'élément suivant
            ++it;
        }
    }
}

bool CEmployer::estRetraite() const{
    return  CDate::currentTime() > dateRetraite();
}

// ->>>>>>>>> methode normal
void CEmployer::augmenter(float pourcentage) {
    if (pourcentage < 0) {
        throw std::invalid_argument("Le pourcentage d'augmentation ne peut être négatif");
    }

    _salaireBase = _salaireBase + (_salaireBase * pourcentage);
}


// ->>>>>>>>> methode static

// methode constante
// std::string CEmployer::generateMatricule(){
//     const char charset[] = "0123456789ABCDEFGHIJKLMNLOPQRSTUVWXYZ";
//     const int length = 8;

//     std::string matricule;

//     // Générer un matricule unique
//     do {
//         matricule.clear();  // Réinitialiser la chaîne

//         for (int i = 0; i < length; ++i) {
//             matricule.push_back(charset[rand() % (sizeof(charset) - 1)]);
//         }
//     } while (usedMatricules.count(matricule) > 0);  // Vérifier l'unicité

//     // Ajouter le matricule à l'ensemble pour éviter la répétition
//     usedMatricules.insert(matricule);

//     return matricule;
// }

std::string CEmployer::generateMatricule() {
    // Utiliser std::random_device pour obtenir une graine aléatoire plus sécurisée
    std::random_device rd;
    std::mt19937 gen(rd());

    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int charsetSize = sizeof(charset) - 1;

    const int matriculeLength = 8;  // Définissez la longueur de votre matricule

    std::uniform_int_distribution<int> distribution(0, charsetSize - 1);

    std::string matricule;
    matricule.reserve(matriculeLength);

    for (int i = 0; i < matriculeLength; ++i) {
        matricule.push_back(charset[distribution(gen)]);
    }

    // Vérifier si le matricule existe déjà, regénérer si nécessaire (pour éviter les doublons)
    while (usedMatricules.find(matricule) != usedMatricules.end()) {
        matricule.clear();
        for (int i = 0; i < matriculeLength; ++i) {
            matricule.push_back(charset[distribution(gen)]);
        }
    }

    // Ajouter le nouveau matricule à l'ensemble des matricules utilisés
    usedMatricules.insert(matricule);

    return matricule;
}

// float CEmployer::calculerSalaireBase(){
//     return _salaireBase;
// }


// ->>>>>>>>> setteur
void CEmployer::setNom(std::string nom){ _nom = nom; }

void CEmployer::setPrenom(std::string prenom){ _prenom = prenom; }

void CEmployer::setFonction(std::string fonction){ _fonction = fonction; }

void CEmployer::setStatut(Statut statut){ _statut = statut; }

void CEmployer::setAdresse(std::string adresse){ _adresse = adresse; }

void CEmployer::setDateNaissance(CDate date_naiss){
    throwInvalidArgumentIf(date_naiss == "0/0/0000", "date Incorecte !");
    _dateNaissance = date_naiss;
}

void CEmployer::setDateNaissance(std::string date_naiss){
    CDate d(date_naiss);
    throwInvalidArgumentIf(d == "0/0/0000", "date Incorecte !");
    _dateNaissance = d;
}

void CEmployer::setDateEmbauche(CDate date_embauche){
    throwInvalidArgumentIf(date_embauche == "0/0/0000", "date Incorecte !");
    _dateEmbauche = date_embauche;
}

void CEmployer::setDateEmbauche(std::string date_embauche){
    CDate d(date_embauche);
    throwInvalidArgumentIf(d == "0/0/0000", "date Incorecte !");
    _dateEmbauche = d;
}

void CEmployer::setSalaireBase(float salaireBase){
    throwInvalidArgumentIf(salaireBase < 0, "Salaire de base inf a 0 !");
    _salaireBase = salaireBase;
}

void CEmployer::setHeureSup(int hSup) {
    throwInvalidArgumentIf(hSup < 0, "Le nombre d'heure sup doit etre > 0");
    _heureSup = hSup;
}

// ->>>>>>>>> Getteur
std::string CEmployer::getNumeroMatricule() const { return _matricule;}
std::string CEmployer::getNom() const {return _nom;}
std::string CEmployer::getPrenom() const { return _prenom;}
std::string CEmployer::getFonction() const { return _fonction;}
// CEmployer::Statut CEmployer::getStatut() const { return _statut == fonctionnaire ? "Fonctionnaire" : "Auxiliaire"; }
CEmployer::Statut CEmployer::getStatut() const { return _statut;}
std::string CEmployer::getAdresse() const { return _adresse;}
CDate CEmployer::getDateNaissance() const {return _dateNaissance;}
CDate CEmployer::getDateEmbauche() const { return _dateEmbauche;}
float CEmployer::getSalaireBase() const {return _salaireBase;}
int CEmployer::getHeureSup() const { return _heureSup; }

/*********************************** CEmployer ***********************************/

