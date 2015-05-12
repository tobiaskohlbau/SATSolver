#include "Clause.h"

#include <sstream>

Clause::Clause()
{
}

Clause::Clause(std::vector<Literal> literals) :
    m_literals(literals)
{
}

Clause::~Clause()
{
}

std::vector<Literal> Clause::literals()
{
    return this->m_literals; 
}

void Clause::setLiterals(std::vector<Literal> literals)
{
    this->m_literals = literals; 
}

std::string Clause::string()
{
    std::stringstream out;
    unsigned int i = 0;

    out << "(";
    for (Literal literal : m_literals)
    {
        if ( i > 0)
            out << "|";
        out << literal.string();
        ++i;
    }
    out << ")";

    return out.str();
}
