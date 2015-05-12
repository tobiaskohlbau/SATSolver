#include "Clause.h"

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
};

void Clause::setLiterals(std::vector<Literal> literals)
{
    this->m_literals = literals; 
};
