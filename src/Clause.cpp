#include "Clause.h"

#include <sstream>

Clause::Clause()
{
}

Clause::Clause(std::vector<std::shared_ptr<Literal>> literals) :
    m_literals(literals)
{
}

Clause::Clause(const Clause &clause) :
    m_literals(clause.literals())
{
}

Clause::~Clause()
{
}

std::vector<std::shared_ptr<Literal>> Clause::literals() const
{
    return this->m_literals; 
}

void Clause::setLiterals(std::vector<std::shared_ptr<Literal>> literals)
{
    this->m_literals = literals; 
}

std::string Clause::string()
{
    std::stringstream out;
    unsigned int i = 0;

    out << "(";
    for (auto literal : m_literals)
    {
        if ( i > 0)
            out << "|";
        out << literal->string();
        ++i;
    }
    out << ")";

    return out.str();
}
