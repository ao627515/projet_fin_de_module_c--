#include <iostream>
#include "cemployer.h"


using namespace std;

int main(int argc, char *argv[])
{

    // try {
        cout << ParametresEntreprise::getAgeRetraite() << endl;

        ParametresEntreprise::setAgeRetraite(15);

        cout << ParametresEntreprise::getAgeRetraite() << endl;

        ParametresEntreprise::setAgeRetraite(0);
        ParametresEntreprise::setAgeRetraite(1);
        cout << ParametresEntreprise::getAgeRetraite() << endl;
        cout << ParametresEntreprise::getAgeRetraite() << endl;
    // } catch (std::invalid_argument e) {
    //     cout << "Erreur : " << e.what();
    // }
    return 0;
}
