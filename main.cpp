#include <iostream>
#include "progtest.h"


using namespace std;

int main(int argc, char *argv[])
{

    try {
        ProgTest::CEmployerTest::progTest();
    } catch (std::invalid_argument e) {
        cout << "Erreur : " << e.what();
    }
    return 0;
}
