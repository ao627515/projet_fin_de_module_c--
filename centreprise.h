#ifndef CENTREPRISE_H
#define CENTREPRISE_H

#include "cemployer.h"
#include "vector"
#include "memory"
// #include "unordered_set"

class CEmployer;

class CEntreprise
{
private:
    static std::vector<std::shared_ptr<CEmployer>> LIST_EMPLOYER;
    // static std::unordered_set<CEmployer, CEmployer::CEmployerHash> LISTEMPLOYER;
public:
    CEntreprise();
    static std::vector<std::shared_ptr<CEmployer>> getLIST_EMPLOYER();
    static void setLIST_EMPLOYER(const CEmployer& emp);
    friend struct CEmployerHash;
    friend class CEmployer;
};


#endif // CENTREPRISE_H
