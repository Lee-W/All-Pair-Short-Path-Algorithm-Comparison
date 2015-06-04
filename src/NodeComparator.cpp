#include "NodeComparator.h"

bool NodeComparator::operator() (const Node& n1, const Node& n2)
{
    return n1.dis > n2.dis;
}
