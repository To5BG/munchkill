#pragma once

#include "variables/variable.h"
#include <unordered_set>

class VariableSingleHoles : public IVariable
{

private:
    int lb, ub;
    std::unordered_set<int> holes;

public:
    VariableSingleHoles(int lb, int ub);

    virtual void remove(int value);
    virtual void setLowerBound(int value);
    virtual void setUpperBound(int value);
    virtual int lowerBound();
    virtual int upperBound();
};