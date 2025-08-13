#pragma once

class IConstraint
{
public:
    virtual void propagate() = 0;
    virtual bool is_satisfied() const = 0;
    virtual bool is_violated() const = 0;
};