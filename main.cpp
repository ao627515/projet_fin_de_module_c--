#include <iostream>
#include "cemployer.h"


using namespace std;

int main(int argc, char *argv[])
{

    try {
           CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000.0);

        cout << emp.estFonctionnaire() << endl;
        cout << emp.estAuxiliaire() << endl;

    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
