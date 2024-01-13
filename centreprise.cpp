#include "centreprise.h"

CEntreprise::CEntreprise() {}



std::vector<std::shared_ptr<CEmployer>> CEntreprise::LIST_EMPLOYER = {};

// std::unordered_set<CEmployer, CEmployer::CEmployerHash> CEntreprise::LISTEMPLOYER;


std::vector<std::shared_ptr<CEmployer>> CEntreprise::getLIST_EMPLOYER(){
    return LIST_EMPLOYER;
}
void CEntreprise::setLIST_EMPLOYER(const CEmployer& emp){
    LIST_EMPLOYER.push_back(std::make_shared<CEmployer>(emp));
}
