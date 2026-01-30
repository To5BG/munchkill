#pragma once

#include <iterator>

template <typename T>
class DomainIterator
{
private:
    const T *var;
    int _curr;

    void next()
    {
        while (_curr < var->upper_bound() && !var->is_valid(_curr))
            _curr++;
    }

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = const int *;
    using reference = int;

    DomainIterator(const T *v, int start) : var(v), _curr(start)
    {
        next();
    }

    reference operator*() const { return _curr; }

    pointer operator->() const { return &_curr; }

    DomainIterator &operator++()
    {
        _curr++;
        next();
        return *this;
    }

    DomainIterator operator++(int)
    {
        DomainIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const DomainIterator &other) const
    {
        return var == other.var && _curr == other._curr;
    }

    bool operator!=(const DomainIterator &other) const
    {
        return !(*this == other);
    }
};

// Auto-generate begin/end for each variable that implements Iterable
template <typename Derived>
class Iterable
{
public:
    auto begin() const
    {
        return DomainIterator<Derived>(static_cast<const Derived *>(this),
                                       static_cast<const Derived *>(this)->lower_bound());
    }

    auto end() const
    {
        return DomainIterator<Derived>(static_cast<const Derived *>(this),
                                       static_cast<const Derived *>(this)->upper_bound() + 1);
    }

    std::vector<int> domain() const
    {
        const Derived *self = static_cast<const Derived *>(this);
        std::vector<int> values;
        values.reserve(self->upper_bound() - self->lower_bound() + 1); // preallocation
        for (int x : *this)
            values.push_back(x);
        return values;
    }
};