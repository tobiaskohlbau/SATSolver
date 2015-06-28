#include "Clause.h"

#include <sstream>
#include <algorithm>

#include <iostream>

Clause::Clause()
{
}

Clause::Clause(const Clause &clause)
{
    for (auto literal : clause.literals())
    {
        m_literals.push_back(std::make_shared<Literal>(*literal));
    }

    for (auto literal : clause.literals(true))
    {
        m_removedLiterals.push_back(std::make_shared<Literal>(*literal));
    }
}

Clause::Clause(std::vector<std::shared_ptr<Literal>> literals) :
    m_literals(literals)
{
}


Clause::~Clause()
{
}

std::vector<std::shared_ptr<Literal>> Clause::literals(bool removed) const
{
    if (!removed)
    {
        return this->m_literals; 
    }
    else
    {
        return this->m_removedLiterals;
    }
        
}

void Clause::setLiterals(std::vector<std::shared_ptr<Literal>> literals)
{
    this->m_literals = literals; 
}

std::string Clause::string(bool removed)
{
    std::stringstream out;
    unsigned int i = 0;

    out << "(";
    for (auto literal : this->literals(removed))
    {
        if ( i > 0)
            out << "|";
        out << literal->string();
        ++i;
    }
    out << ")";

    return out.str();
}

void Clause::remove(Literal *literal)
{
    auto it = std::find_if(m_literals.begin(), m_literals.end(), [literal](std::shared_ptr<Literal> const &p) {
        return p.get() == literal;
    });
    if (it != m_literals.end())
    {
        m_removedLiterals.push_back(*it);
        m_literals.erase(it);
    }
}
