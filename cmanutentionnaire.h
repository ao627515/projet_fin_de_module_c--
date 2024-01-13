#ifndef CMANUTENTIONNAIRE_H
#define CMANUTENTIONNAIRE_H

#include "cemployer.h"

class CManutentionnaire : public CEmployer
{
private:
    static const double _BASE_SALAIRE_HORAIRE;
    int _nb_heures;
public:
    CManutentionnaire();
};

#endif // CMANUTENTIONNAIRE_H
