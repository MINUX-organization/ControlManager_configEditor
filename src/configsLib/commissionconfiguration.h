#ifndef COMMISSIONCONFIGURATION_H
#define COMMISSIONCONFIGURATION_H

#include "interpretator.h"

namespace ConfigsLib
{

class CommissionConfiguration : public Interpretator
{
public:
    CommissionConfiguration(const std::string & filePath);
    ~CommissionConfiguration();

    int time();
    int timeInterval();


};

}

#endif // COMMISSIONCONFIGURATION_H
