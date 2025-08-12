#include "propagation/propagator_queue.h"
#include "constraints/constraint.h"

void PropagatorQueue::enqueue(IConstraint *propagator)
{
    if (propagator && in_queue.find(propagator) == in_queue.end())
    {
        queue.push(propagator);
        in_queue.insert(propagator);
    }
}

IConstraint *PropagatorQueue::dequeue()
{
    if (queue.empty())
    {
        return nullptr;
    }

    IConstraint *propagator = queue.front();
    queue.pop();
    in_queue.erase(propagator);

    return propagator;
}

bool PropagatorQueue::empty() const
{
    return queue.empty();
}

void PropagatorQueue::clear()
{
    while (!queue.empty())
    {
        queue.pop();
    }
    in_queue.clear();
}

size_t PropagatorQueue::size() const
{
    return queue.size();
}
