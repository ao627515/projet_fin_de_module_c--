#include "utils.h"
#include <algorithm>
#include <random>

namespace utils {

    void insererEmploye (const CEmployer& emp){
        CEntreprise::setLIST_EMPLOYER(emp);
    }

    // std::vector<std::shared_ptr<CEmployer>> rechercherEmployeAtt(const std::string& query, const std::string& nomAtt) {
    //     // query est l'element a rechercher
    //     // nomAtt = nomAttributMembre , nom de l'element membre de CEmployer sur la quelle on fait la recherche
    //     std::vector<std::shared_ptr<CEmployer>> result;

    //     for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
    //         // Vérifie si le nom de l'employé correspond au nom recherché
    //         if (emp->getNom() == nom) {
    //             result.push_back(emp);
    //         }
    //     }

    //     return result;
    // }

    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query, AttCEmployerResearch nomAtt, bool sensibleCase) {
        std::vector<std::shared_ptr<CEmployer>> result;

        // Copier la chaîne query dans une nouvelle chaîne pour la recherche insensible à la casse
        std::string queryLowerCase = query;
        if(!sensibleCase) std::transform(queryLowerCase.begin(), queryLowerCase.end(), queryLowerCase.begin(), ::tolower);

        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            // Récupérer la valeur de l'attribut spécifié et le convertir en minuscules
            std::string attributValue;

            switch (nomAtt) {
            case AttCEmployerResearch::MATRICULE:
                attributValue = emp->getNumeroMatricule();
                break;
            case AttCEmployerResearch::NOM:
                attributValue = emp->getNom();
                break;
            case AttCEmployerResearch::PRENOM:
                attributValue = emp->getPrenom();
                break;
            case AttCEmployerResearch::ADRESSE:
                attributValue = emp->getAdresse();
                break;
            case AttCEmployerResearch::DATE_NAISSANCE:
                attributValue = emp->getDateNaissance().toString();
                break;
            case AttCEmployerResearch::DATE_EMBAUCHE:
                attributValue = emp->getDateEmbauche().toString();
                break;
            case AttCEmployerResearch::FONCTION:
                attributValue = emp->getFonction();
                break;
            case AttCEmployerResearch::SALAIRE_BASE:
                attributValue = std::to_string(emp->getSalaireBase());
                break;
            case AttCEmployerResearch::HEURE_SUP:
                attributValue = std::to_string(emp->getHeureSup());
                break;
            }
            // Ajoutez d'autres attributs si nécessaire

            // Convertir la valeur de l'attribut en minuscules pour une recherche insensible à la casse
            if(!sensibleCase) std::transform(attributValue.begin(), attributValue.end(), attributValue.begin(), ::tolower);

            // Vérifier si la sous-chaîne query existe dans la valeur de l'attribut
            if (attributValue.find(queryLowerCase) != std::string::npos) {
                result.push_back(emp);
            }
        }

        return result;
    }

    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query,  bool sensibleCase) {
        std::vector<std::shared_ptr<CEmployer>> result;

        // Copiez la chaîne query dans une nouvelle chaîne avant d'appliquer std::transform
        std::string queryLowerCase = query;
        std::transform(queryLowerCase.begin(), queryLowerCase.end(), queryLowerCase.begin(), ::tolower);

        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            // Convertir les chaînes en minuscules pour une recherche insensible à la casse
            std::string matricule = emp->getNumeroMatricule();
            std::string nom = emp->getNom();
            std::string prenom = emp->getPrenom();
            std::string fonction = emp->getFonction();
            CEmployer::Statut statut = emp->getStatut();
            std::string adresse = emp->getAdresse();
            std::string dateNaissance = emp->getDateNaissance().toString();
            std::string dateEmbauche = emp->getDateEmbauche().toString();
            float salaireBase = emp->getSalaireBase();
            int heureSup = emp->getHeureSup();

            if(!sensibleCase){
                std::transform(matricule.begin(), matricule.end(), matricule.begin(), ::tolower);
                std::transform(nom.begin(), nom.end(), nom.begin(), ::tolower);
                std::transform(prenom.begin(), prenom.end(), prenom.begin(), ::tolower);
                std::transform(fonction.begin(), fonction.end(), fonction.begin(), ::tolower);
                std::transform(adresse.begin(), adresse.end(), adresse.begin(), ::tolower);
                std::transform(dateNaissance.begin(), dateNaissance.end(), dateNaissance.begin(), ::tolower);
                std::transform(dateEmbauche.begin(), dateEmbauche.end(), dateEmbauche.begin(), ::tolower);
            }

            // Vérifier si la sous-chaîne query existe dans l'une des propriétés de l'employé
            if (matricule.find(queryLowerCase) != std::string::npos ||
                nom.find(queryLowerCase) != std::string::npos ||
                prenom.find(queryLowerCase) != std::string::npos ||
                fonction.find(queryLowerCase) != std::string::npos ||
                std::to_string(static_cast<int>(statut)).find(queryLowerCase) != std::string::npos ||
                adresse.find(queryLowerCase) != std::string::npos ||
                dateNaissance.find(queryLowerCase) != std::string::npos ||
                dateEmbauche.find(queryLowerCase) != std::string::npos ||
                std::to_string(salaireBase).find(queryLowerCase) != std::string::npos ||
                std::to_string(heureSup).find(queryLowerCase) != std::string::npos) {
                result.push_back(emp);
            }
        }

        return result;
    }

    std::vector<std::shared_ptr<CEmployer>> rechercherEmploye(const std::string& query,const std::vector<std::shared_ptr<CEmployer>>& CONTAINER, bool sensibleCase) {
        std::vector<std::shared_ptr<CEmployer>> result;

        // Copiez la chaîne query dans une nouvelle chaîne avant d'appliquer std::transform
        std::string queryLowerCase = query;
        std::transform(queryLowerCase.begin(), queryLowerCase.end(), queryLowerCase.begin(), ::tolower);

        for (const auto& emp : CONTAINER) {
            // Convertir les chaînes en minuscules pour une recherche insensible à la casse
            std::string matricule = emp->getNumeroMatricule();
            std::string nom = emp->getNom();
            std::string prenom = emp->getPrenom();
            std::string fonction = emp->getFonction();
            CEmployer::Statut statut = emp->getStatut();
            std::string adresse = emp->getAdresse();
            std::string dateNaissance = emp->getDateNaissance().toString();
            std::string dateEmbauche = emp->getDateEmbauche().toString();
            float salaireBase = emp->getSalaireBase();
            int heureSup = emp->getHeureSup();

            if(!sensibleCase){
                std::transform(matricule.begin(), matricule.end(), matricule.begin(), ::tolower);
                std::transform(nom.begin(), nom.end(), nom.begin(), ::tolower);
                std::transform(prenom.begin(), prenom.end(), prenom.begin(), ::tolower);
                std::transform(fonction.begin(), fonction.end(), fonction.begin(), ::tolower);
                std::transform(adresse.begin(), adresse.end(), adresse.begin(), ::tolower);
                std::transform(dateNaissance.begin(), dateNaissance.end(), dateNaissance.begin(), ::tolower);
                std::transform(dateEmbauche.begin(), dateEmbauche.end(), dateEmbauche.begin(), ::tolower);
            }

            // Vérifier si la sous-chaîne query existe dans l'une des propriétés de l'employé
            if (matricule.find(queryLowerCase) != std::string::npos ||
                nom.find(queryLowerCase) != std::string::npos ||
                prenom.find(queryLowerCase) != std::string::npos ||
                fonction.find(queryLowerCase) != std::string::npos ||
                std::to_string(static_cast<int>(statut)).find(queryLowerCase) != std::string::npos ||
                adresse.find(queryLowerCase) != std::string::npos ||
                dateNaissance.find(queryLowerCase) != std::string::npos ||
                dateEmbauche.find(queryLowerCase) != std::string::npos ||
                std::to_string(salaireBase).find(queryLowerCase) != std::string::npos ||
                std::to_string(heureSup).find(queryLowerCase) != std::string::npos) {
                result.push_back(emp);
            }
        }

        return result;
    }

    void supprimerEmploye(const std::string& matricule) {
        std::vector<std::shared_ptr<CEmployer>> vec = rechercherEmploye(matricule, AttCEmployerResearch::MATRICULE);
        vec[0]->supprimerDansListe();
    }

    const void listeRetraites() {
        int currentYear = CDate::currentYear();
        bool foundRetirees = false;
        std::cout << "Liste des employes devant prendre leur retraite en " << currentYear << " :" << std::endl;

        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            foundRetirees = true;
            // Vérifier si l'employé prend sa retraite cette année
            if (emp->dateRetraite().lireAnnee() == currentYear) {
                // Afficher les détails de l'employé
                emp->afficher();
                std::cout << std::endl;
            }
        }

        if (!foundRetirees) {
            std::cout << "Aucun employe ne prendra sa retraite en " << currentYear << "." << std::endl;
        }
    }

    const void listeRetraites(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER) {
        int currentYear = CDate::currentYear();
        bool foundRetirees = false;
        std::cout << "Liste des employes devant prendre leur retraite en " << currentYear << " :" << std::endl;

        for (const auto& emp : CONTAINER) {
            foundRetirees = true;
            // Vérifier si l'employé prend sa retraite cette année
            if (emp->dateRetraite().lireAnnee() == currentYear) {
                // Afficher les détails de l'employé
                emp->afficher();
                std::cout << std::endl;
            }
        }

        if (!foundRetirees) {
            std::cout << "Aucun employe ne prendra sa retraite en " << currentYear << "." << std::endl;
        }
    }

    const float masseSalariale() {
        float totalSalaire = 0.0;

        // Boucle à travers la liste des employés
        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            // Ajouter le salaire de chaque employé
            totalSalaire += emp->calculerSalaire();
        }

        return totalSalaire;
    }

    const float masseSalariale(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER) {
        float totalSalaire = 0.0;

        // Boucle à travers la liste des employés
        for (const auto& emp : CONTAINER) {
            // Ajouter le salaire de chaque employé
            totalSalaire += emp->calculerSalaire();
        }

        return totalSalaire;
    }

    const void calculerSalaireEmpl() {
        float masseSalariale = 0.0;

        // Boucle à travers la liste des employés
        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            // Calculer le salaire de l'employé pour le mois en cours
            float salaireMensuel = emp->calculerSalaire();

            // Ajouter le salaire de l'employé à la masse salariale totale
            masseSalariale += salaireMensuel;

            // Afficher les détails de l'employé et son salaire

            std::cout << "Salaire du mois : " << salaireMensuel << " euros" << std::endl;
            std::cout << std::endl;
        }

        // Afficher la masse salariale totale
        std::cout << "Masse salariale mensuelle totale : " << masseSalariale << " euros" << std::endl;
    }

    const void calculerSalaireEmpl(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER) {
        float masseSalariale = 0.0;

        // Boucle à travers la liste des employés
        for (const auto& emp : CONTAINER) {
            // Calculer le salaire de l'employé pour le mois en cours
            float salaireMensuel = emp->calculerSalaire();

            // Ajouter le salaire de l'employé à la masse salariale totale
            masseSalariale += salaireMensuel;

            // Afficher les détails de l'employé et son salaire

            std::cout << "Salaire du mois : " << salaireMensuel << " euros" << std::endl;
            std::cout << std::endl;
        }

        // Afficher la masse salariale totale
        std::cout << "Masse salariale mensuelle totale : " << masseSalariale << " euros" << std::endl;
    }

    const void fonctionnaires() {
        int totalEmployes = CEntreprise::getLIST_EMPLOYER().size();
        int fonctionnairesCount = 0;

        std::cout << "Liste des fonctionnaires :" << std::endl;

        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            if (emp->estFonctionnaire()) {
                // L'employé est un fonctionnaire
                fonctionnairesCount++;

                // Afficher les détails du fonctionnaire
                emp->afficher();
                std::cout << std::endl;
            }
        }

        // Afficher la proportion de fonctionnaires par rapport à l'ensemble des employés
        float proportionFonctionnaires = (totalEmployes > 0) ? (static_cast<float>(fonctionnairesCount) / totalEmployes) * 100 : 0.0;
        std::cout << "Proportion de fonctionnaires : " << proportionFonctionnaires << "%" << std::endl;
    }

    const void fonctionnaires(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER) {
        int totalEmployes = CONTAINER.size();
        int fonctionnairesCount = 0;

        std::cout << "Liste des fonctionnaires :" << std::endl;

        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            if (emp->estFonctionnaire()) {
                // L'employé est un fonctionnaire
                fonctionnairesCount++;

                // Afficher les détails du fonctionnaire
                emp->afficher();
                std::cout << std::endl;
            }
        }

        // Afficher la proportion de fonctionnaires par rapport à l'ensemble des employés
        float proportionFonctionnaires = (totalEmployes > 0) ? (static_cast<float>(fonctionnairesCount) / totalEmployes) * 100 : 0.0;
        std::cout << "Proportion de fonctionnaires : " << proportionFonctionnaires << "%" << std::endl;
    }

    const void conges() {
        std::cout << "Liste des employes avec leurs jours de conges :" << std::endl;

        for (const auto& emp : CEntreprise::getLIST_EMPLOYER()) {
            // Récupérer le nombre de jours de congés de l'employé
            int joursConges = emp->nbJoursDeConge();

            // Afficher les détails de l'employé avec le nombre de jours de congés
            // std::cout << "Matricule : " << emp->getNumeroMatricule() << std::endl;
            // std::cout << "Nom : " << emp->getNom() << std::endl;
            // std::cout << "Prenom : " << emp->getPrenom() << std::endl;
            emp->afficher();
            std::cout << "Nombre de jours de conges : " << joursConges << std::endl;
            std::cout << std::endl;
        }
    }

    const void conges(const std::vector<std::shared_ptr<CEmployer>>& CONTAINER) {
        std::cout << "Liste des employes avec leurs jours de conges :" << std::endl;

        for (const auto& emp : CONTAINER) {
            // Récupérer le nombre de jours de congés de l'employé
            int joursConges = emp->nbJoursDeConge();
            emp->afficher();
            std::cout << "Nombre de jours de conges : " << joursConges << std::endl;
            std::cout << std::endl;
        }
    }

    int generateRandomIndex(int maxIndex) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, maxIndex - 1);
        return dis(gen);
    }

    CEmployer generateRandomEmployer() {
        std::vector<std::string> noms = {
            "Smith", "Johnson", "Williams", "Jones", "Brown",
            "Davis", "Miller", "Wilson", "Moore", "Taylor",
            "Anderson", "Thomas", "Jackson", "White", "Harris",
            "Martin", "Thompson", "Garcia", "Martinez", "Robinson",
            "Clark", "Rodriguez", "Lewis", "Lee", "Walker",
            "Hall", "Allen", "Young", "Hernandez", "King",
            "Wright", "Lopez", "Hill", "Scott", "Green",
            "Adams", "Baker", "Gonzalez", "Nelson", "Carter",
            "Mitchell", "Perez", "Roberts", "Turner", "Phillips",
            "Campbell", "Parker", "Evans", "Edwards", "Collins"
        };

        std::vector<std::string> prenoms = {
            "Emma", "Liam", "Olivia", "Noah", "Ava",
            "Isabella", "Sophia", "Jackson", "Lucas", "Aiden",
            "Mia", "Harper", "Evelyn", "Abigail", "Amelia",
            "Benjamin", "Elijah", "Lucas", "Mason", "Logan",
            "Ethan", "Oliver", "Aiden", "Muhammad", "James",
            "Alexander", "Sebastian", "Jack", "William", "Daniel",
            "Carter", "Jayden", "Matthew", "Wyatt", "Henry",
            "Joseph", "Samuel", "David", "Benjamin", "Andrew",
            "John", "Gabriel", "Julian", "Julia", "Lily",
            "Grace", "Ella", "Chloe", "Charlotte", "Sofia"
        };

        std::vector<std::string> fonctions = {
            "Ingenieur logiciel", "Developpeur web", "Architecte systeme", "Analyste financier",
            "Infirmier/infirmiere", "Enseignant/enseignante", "Chef de projet", "Designer graphique",
            "Analyste de donnees", "Conseiller/conseillere financier", "Medecin generaliste", "Pharmacien/pharmacienne",
            "Chef cuisinier/chef cuisiniere", "Journaliste", "Avocat/avocate", "Assistant/assistante administratif",
            "Technicien/technicienne de laboratoire", "electricien/electricienne", "Plombier/plombiere", "Agent immobilier/agent immobiliere",
            "Analyste de marche", "Agent de voyage", "Psychologue clinicien/psychologue clinicienne", "Traducteur/traductrice",
            "Ingenieur en genie civil", "Decorateur/decoratrice d'interieur", "Geologue", "Agent de police",
            "Pilote de ligne", "Artiste musical/artiste musicale", "Coach sportif/coach sportive", "economiste",
            "Physiotherapeute", "Veterinaire", "Responsable des ressources humaines", "Conseiller/conseillere en communication",
            "Responsable marketing", "Technicien/technicienne de maintenance", "Chef de chantier", "Analyste en securite informatique",
            "Animateur/animatrice radio", "Agriculteur/agricultrice", "Sapeur-pompier/sapeuse-pompiere", "Agent de securite",
            "Expert comptable", "Juge", "Entrepreneur/entrepreneuse", "Responsable qualite", "Conseiller/conseillere en voyage"
        };

        std::vector<std::string> adresses = {
            "123 Main Street, Cityville, State, 12345",
            "456 Oak Avenue, Townsville, State, 56789",
            "789 Elm Boulevard, Villageton, State, 98765",
            "321 Maple Lane, Hamletville, State, 54321",
            "654 Pine Road, Suburbia, State, 13579",
            "987 Cedar Street, Boroughburg, State, 24680",
            "234 Birch Avenue, Metropolis, State, 86420",
            "876 Redwood Drive, Megatown, State, 97531",
            "543 Spruce Court, Capital City, State, 80246",
            "210 Sequoia Circle, Lakeside, State, 64128",
            "876 Willow Way, Mountainview, State, 35971",
            "345 Juniper Street, Rivertown, State, 12478",
            "678 Oakwood Lane, Harbor City, State, 53792",
            "123 Pinecrest Road, Oceantown, State, 64921",
            "456 Sycamore Avenue, Valleyville, State, 75319",
            "789 Cedar Lane, Laketown, State, 28467",
            "321 Elmwood Boulevard, Groveton, State, 97531",
            "654 Aspen Drive, Hilltop, State, 81346",
            "987 Cedarwood Court, Meadowville, State, 56234",
            "234 Birch Lane, Highland, State, 69781",
            "876 Redwood Avenue, Lakeshore, State, 25413",
            "543 Pinehurst Drive, Brookside, State, 18672",
            "210 Maplewood Court, Hillside, State, 93527",
            "876 Oakhurst Lane, Riverside, State, 41629",
            "345 Cedarwood Road, Sunset City, State, 75834",
            "678 Birchwood Avenue, Oceanview, State, 59382",
            "123 Elmwood Drive, Countryside, State, 35784",
            "456 Maplehurst Road, Seaville, State, 64201",
            "789 Pineview Lane, Summitville, State, 21934",
            "321 Cedarhurst Avenue, Lakefront, State, 86573",
            "654 Oakridge Court, Riverview, State, 50293",
            "987 Birchwood Circle, Meadowland, State, 71486",
            "234 Pinegrove Boulevard, Uptown, State, 36895",
            "876 Sycamore Lane, Hillcrest, State, 92157",
            "543 Elmridge Road, Waterside, State, 48512",
            "210 Redwood Court, Shoreline, State, 63924",
            "876 Pinecrest Lane, Riverside, State, 75238",
            "345 Oakwood Avenue, Valleyview, State, 29645",
            "678 Birchhurst Drive, Crestview, State, 51372",
            "123 Maplehill Lane, Lakeside, State, 84751",
            "456 Cedarhurst Road, Hilltop, State, 36492",
            "789 Pineview Drive, Brookside, State, 95237",
            "321 Elmridge Boulevard, Valleyville, State, 61948",
            "654 Maplewood Lane, Highland, State, 73826",
            "987 Redwood Circle, Meadowland, State, 20594",
            "234 Sycamore Avenue, Uptown, State, 47183",
            "876 Oakhurst Lane, Countryside, State, 52869",
            "543 Pinegrove Road, Oceanview, State, 68317"
        };

        // Utilisation des listes prealablement definies
        std::string nom = noms[generateRandomIndex(noms.size())];
        std::string prenom = prenoms[generateRandomIndex(prenoms.size())];
        std::string fonction = fonctions[generateRandomIndex(fonctions.size())];
        std::string adresse = adresses[generateRandomIndex(adresses.size())];

        // Generation d'autres attributs aleatoires (à adapter selon votre classe CEmployer)
        // CDate dateNaissance(1990 + generateRandomIndex(30), 1 + generateRandomIndex(12), 1 + generateRandomIndex(28));
        // CDate dateEmbauche(2010 + generateRandomIndex(10), 1 + generateRandomIndex(12), 1 + generateRandomIndex(28));
        // Génération d'autres attributs aléatoires (à adapter selon votre classe CEmployer)
        int anneeNaissance = 1990 + generateRandomIndex(30);
        int moisNaissance = 1 + generateRandomIndex(12);
        int jourNaissance = 1 + generateRandomIndex(28);
        CDate dateNaissance(jourNaissance, moisNaissance, anneeNaissance);

        int anneeEmbauche = anneeNaissance + generateRandomIndex(10);
        int moisEmbauche = 1 + generateRandomIndex(12);
        int jourEmbauche = 1 + generateRandomIndex(28);
        CDate dateEmbauche(jourEmbauche, moisEmbauche, anneeEmbauche);
        CEmployer::Statut statut = generateRandomIndex(2) ?  CEmployer::fonctionnaire :  CEmployer::auxiliaire;

        // Assurez-vous que la date de naissance est antérieure à la date d'embauche
        if (dateNaissance > dateEmbauche) {
            std::swap(dateNaissance, dateEmbauche);
        }
        float salaireBase = 30000.0f + static_cast<float>(generateRandomIndex(20000));
        // int heureSup = generateRandomIndex(20);

        // Creation de l'employe
        CEmployer employe(nom, prenom, fonction, statut, adresse, dateNaissance, dateEmbauche, salaireBase);

        // Retour de l'employe genere
        return employe;
    }

    void generateEmpolyer(const int nb){
        for(int i = 0; i < nb; i++){
            CEmployer emp = generateRandomEmployer();
            insererEmploye(emp);
        }
    }
}

