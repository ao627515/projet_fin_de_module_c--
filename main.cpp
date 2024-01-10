#include <iostream>
#include "cemployer.h"


using namespace std;

int main(int argc, char *argv[])
{

    try {
        CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000);

        emp.afficher();

    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
