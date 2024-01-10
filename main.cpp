#include <iostream>
#include "cemployer.h"


using namespace std;

int main(int argc, char *argv[])
{

    try {
        CEmployerProgTest::test_setteur_getteur_construct();

    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
