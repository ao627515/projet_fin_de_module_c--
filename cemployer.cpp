#include "cemployer.h"
#include <random>
#include "iostream"
/*********************************** ParametresEntreprise ***********************************/
float ParametresEntreprise::plafondProtectionSociale = 5000.0;
float ParametresEntreprise::tauxHoraire = 0.02;
float ParametresEntreprise::tauxHoraireMajore = 0.025;
int ParametresEntreprise::ageRetraite = 65;
int ParametresEntreprise::heureMajore = 100;

// ->>>>>>>>> setteur
void ParametresEntreprise::setPlafondProtectionSociale(float plafond){
    ParametresEntreprise::plafondProtectionSociale = plafond;
}

void ParametresEntreprise::setTauxHoraire(float taux){
    throwInvalidArgumentIf(taux < 0, "Le taux horaire doit etre sup a 0");
    ParametresEntreprise::tauxHoraire = taux;
}

void ParametresEntreprise::setTauxHoraireMajore(float tauxMajore){
    throwInvalidArgumentIf(tauxMajore  < ParametresEntreprise::tauxHoraire,
                           "Le taux horaire majorer doit ere sup aux taux horaire : " + std::to_string(ParametresEntreprise::tauxHoraire));
    ParametresEntreprise::tauxHoraireMajore = tauxMajore;
}

void ParametresEntreprise::setAgeRetraite(int age){
    throwInvalidArgumentIf(age <= 0, "Le l'age de retraite doit etre sup a 0");
    ParametresEntreprise::ageRetraite = age;
}

void ParametresEntreprise::setHeureMajore(int h){
    throwInvalidArgumentIf(h <= 0, "le nombre d'heure suppl majoré doit etre sup a 0");
    ParametresEntreprise::heureMajore = h;
}

// ->>>>>>>>> getteur
float ParametresEntreprise::getPlafondProtectionSociale(){
    return ParametresEntreprise::plafondProtectionSociale;
}

float ParametresEntreprise::getTauxHoraire(){
    return ParametresEntreprise::tauxHoraire;
}

float ParametresEntreprise::getTauxHoraireMajore(){
    return ParametresEntreprise::tauxHoraireMajore;
}

int ParametresEntreprise::getAgeRetraite(){
    return ParametresEntreprise::ageRetraite;
}

int ParametresEntreprise::getHeureMajore(){
    return ParametresEntreprise::heureMajore;
}

/*********************************** ParametresEntreprise ***********************************/

/*********************************** CEmployer ***********************************/

// ->>>>>>>>> atributs
std::set<std::string> CEmployer::usedMatricules;

// ->>>>>>>>> Constructeur
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
}

// ->>>>>>>>> methode constante
bool CEmployer::estAuxiliaire() const{ return _statut == CEmployer::auxiliaire; }

bool CEmployer::estFonctionnaire() const {return _statut == CEmployer::fonctionnaire; }

float CEmployer::calculerSalaire(int nbHeureSupp) const {
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
    std::cout << "Date de Naissance: " << getDateNaissance() << std::endl;
    std::cout << "Date d'embauche: " << getDateEmbauche() << std::endl;
    std::cout << "Salaire de base: " << getSalaireBase() << std::endl;
}

int CEmployer::getAge() const {
    return CDate::currentTime().lireAnnee() - _dateNaissance.lireAnnee();
}

int CEmployer::ancienneté() const {
    return CDate::currentTime().lireAnnee() - _dateEmbauche.lireAnnee();
}

int CEmployer::nbJoursDeConge(bool cadre) const{

    /*
        Déterminer le nombre de jours de congé d'un employé.
        le calcul des jours de congés payés s’effectue de la manière suivante :
            si une personne est entrée dans l’entreprise depuis moins d’un an, elle a droit à deux jours
            de congés par mois de présence (au minimum 1 mois), sinon à 28 jours au moins.

            Si cette personne est un cadre et si elle est âgée d’au moins 35 ans et si son ancienneté est supérieure à 3 ans, il lui est accordé 2jours supplémentaires.

            Si elle est cadre et si elle est âgée d’au moins 45 ans et si son ancienneté est supérieure à 5 ans, il lui est accordé 4 jours supplémentaires,
                en plus des 2 accordés pour plus de 35 ans. .
     */
    // number of days off
    int nbDoff = 0;

    // si une personne est entrée dans l’entreprise depuis moins d’un an, elle a droit à deux jours
    // de congés par mois de présence (au minimum 1 mois), sinon à 28 jours au moins.

    int nbDaysElpased = CDate::currentTime() - _dateEmbauche;
    if( nbDaysElpased <= 0) {
        int j = 0;
        int m = 0, a = 0;
        m = _dateEmbauche.lireMois();
        a = _dateEmbauche.lireAnnee();
        int dayInMonth = CDate::daysInMonth(m, a);
        while(nbDaysElpased > dayInMonth){
            nbDaysElpased -= dayInMonth;
            m++;
            if(m > 12) a++;
            dayInMonth = CDate::daysInMonth(m, a);
        }
    }

    // Si cette personne est un cadre et si elle est âgée d’au moins 35 ans et si son ancienneté est supérieure à 3 ans,
    if(cadre && getAge() >= 35 && ancienneté() > 3) nbDoff += 2;

    if(cadre && getAge() >= 45 && ancienneté() > 5) nbDoff += 5;


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
    throwInvalidArgumentIf(salaireBase <= 0, "Salaire de base inf a 0 !");
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

/*********************************** ProgTest ***********************************/
void CEmployerProgTest::test_setteur_getteur_construct(){

    CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000.0);

    // Utilisation des getters
    std::cout << "Matricule: " << emp.getNumeroMatricule() << std::endl;
    std::cout << "Nom: " << emp.getNom() << std::endl;
    std::cout << "Prenom: " << emp.getPrenom() << std::endl;
    std::cout << "Fonction: " << emp.getFonction() << std::endl;
    std::cout << "Statut: " << (emp.getStatut() == CEmployer::fonctionnaire ? "Fonctionnaire" : "Auxiliaire") << std::endl;
    std::cout << "Adresse: " << emp.getAdresse() << std::endl;
    std::cout << "Date de Naissance: " << emp.getDateNaissance() << std::endl;
    std::cout << "Date d'embauche: " << emp.getDateEmbauche() << std::endl;
    std::cout << "Salaire de base: " << emp.getSalaireBase() << std::endl;

    // Utilisation des setters
    emp.setNom("NouveauNom");
    emp.setPrenom("NouveauPrenom");
    emp.setFonction("NouvelleFonction");
    emp.setStatut(CEmployer::auxiliaire);
    emp.setAdresse("NouvelleAdresse");
    emp.setDateNaissance("01/01/1990");
    emp.setDateEmbauche("01/01/2022");
    emp.setSalaireBase(60000.0);

    // Affichage après modification
    std::cout << "\nAprès modification :\n";
    std::cout << "Nom: " << emp.getNom() << std::endl;
    std::cout << "Prenom: " << emp.getPrenom() << std::endl;
    std::cout << "Fonction: " << emp.getFonction() << std::endl;
    std::cout << "Statut: " << (emp.getStatut() == CEmployer::fonctionnaire ? "Fonctionnaire" : "Auxiliaire") << std::endl;
    std::cout << "Adresse: " << emp.getAdresse() << std::endl;
    std::cout << "Date de Naissance: " << emp.getDateNaissance() << std::endl;
    std::cout << "Date d'embauche: " << emp.getDateEmbauche() << std::endl;
    std::cout << "Salaire de base: " << emp.getSalaireBase() << std::endl;
}
/*********************************** ProgTest ***********************************/
