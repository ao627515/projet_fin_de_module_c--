#ifndef CTECHNICIEN_H
#define CTECHNICIEN_H

#include "cemployer.h"

class CTechnicien : public CEmployer
{
private:
    int _nb_unite_produite;
    static const float _GAIN_UNITE;
public:
    CTechnicien();
};

#endif // CTECHNICIEN_H
