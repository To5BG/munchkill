#include "variables/variable_single_holes.h"

VariableSingleHoles::VariableSingleHoles(int lb, int ub) 
{
    this->lb = lb;
    this->ub = ub;
}

void VariableSingleHoles::remove(int value)
{
    this->holes.insert(value);
}

void VariableSingleHoles::setLowerBound(int value)
{
    this->lb = std::max(this->lb, value);
}

void VariableSingleHoles::setUpperBound(int value)
{
    this->ub = std::max(this->ub, value);
}

int VariableSingleHoles::lowerBound()
{
    return this->lb;
}

int VariableSingleHoles::upperBound()
{
    return this->ub;
}
