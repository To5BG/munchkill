#pragma once

class IConstraint
{
public:
    virtual void propagate() = 0;
};