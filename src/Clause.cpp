#include "Clause.h"

#include <sstream>

Clause::Clause()
{
}

Clause::Clause(const Clause &clause) :
    m_removed(clause.removed())
{
    std::vector<std::shared_ptr<Literal>> literals;
    for (auto literal : clause.literals(true))
    {
        literals.push_back(std::make_shared<Literal>(*literal));
    }
    m_literals = literals;
}

Clause::Clause(std::vector<std::shared_ptr<Literal>> literals) :
    m_literals(literals),
    m_removed(false)
{
}


Clause::~Clause()
{
}

std::vector<std::shared_ptr<Literal>> Clause::literals(bool removed) const
{
    if (removed)
    {
        return this->m_literals; 
    }
    else
    {
        std::vector<std::shared_ptr<Literal>> literals;
        for (auto literal : m_literals)
        {
            if (!literal->removed())
                literals.push_back(literal);
        }
        return literals;
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
    for (auto literal : m_literals)
    {
        if (!literal->removed() || removed)
        {
            if ( i > 0)
                out << "|";
            out << literal->string();
            ++i;
        }
    }
    out << ")";

    return out.str();
}

bool Clause::removed() const
{
    return m_removed;
}

void Clause::remove()
{
    this->m_removed = true;
}
