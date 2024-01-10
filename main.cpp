#include <iostream>
#include "cemployer.h"


using namespace std;

int main(int argc, char *argv[])
{

    try {
           CEmployer emp("Ouedraogo", "Abdoul", "PDF", CEmployer::fonctionnaire, "Ouagadougou", "26/11/2000", "10/1/2024", 50000);

        cout << "salaire : " << emp.calculerSalaire() << endl;
        cout << "salaire : " << emp.calculerSalaire(10) << endl;
        cout << "salaire : " << emp.calculerSalaire(100) << endl;
        cout << "salaire : " << emp.calculerSalaire(150) << endl;
    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
