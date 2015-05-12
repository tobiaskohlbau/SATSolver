#include "Gate.h"

#include <iostream>

Gate::Gate()
{
}

Gate::Gate(Type type, std::vector<Net> nets) :
    m_type(type)
{
    switch (type)
    {
    case Type::UNKNOWN:
        std::cout << "unknown";
        break;
    case Type::AND:
        std::cout << "and";
        break;
    case Type::OR:
        std::cout << "or";
        break;
    case Type::INV:
        std::cout << "inv";
        break;
    case Type::XOR:
        std::cout << "xor";
        break;
    case Type::ZERO:
        std::cout << "zero";
        break;
    case Type::ONE:
        std::cout << "one";
        break;
    }
}

Gate::~Gate()
{
}


void Gate::setType(Type type)
{
    this->m_type = type; 
}

void Gate::setIONets(std::vector<Net> nets)
{
    this->m_ioNets = nets; 
}
