#pragma once

class IConstraint
{
public:
    virtual void propagate() = 0;
    virtual bool isSatisfied() const = 0;
    virtual bool isViolated() const = 0;
};