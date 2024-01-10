#include <iostream>
#include "cemployer.h"


using namespace std;

int main(int argc, char *argv[])
{

    try {
        for(int i =0; i < 10 ; i++){
            cout << "matricule : " << CEmployer::generateMatricule() << endl;
        }

        cout << "Listes : " ;
        for (const auto& elem : CEmployer::usedMatricules) {
            std::cout << elem << " - ";
        }
    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
