#include "ConjunctiveNormalForm.h"

#include <sstream>
#include <iostream>

ConjunctiveNormalForm::ConjunctiveNormalForm()
{
}

ConjunctiveNormalForm::ConjunctiveNormalForm(const ConjunctiveNormalForm &cnf) 
{
    std::vector<std::shared_ptr<Clause>> clauses;
    for (auto clause : cnf.clauses(true))
    {
        clauses.push_back(std::make_shared<Clause>(*clause));
    }
    m_clauses = clauses;
}

ConjunctiveNormalForm::ConjunctiveNormalForm(std::vector<std::shared_ptr<Clause>> clauses) :
    m_clauses(clauses)
{
}

ConjunctiveNormalForm::~ConjunctiveNormalForm()
{
}


std::vector<std::shared_ptr<Clause>> ConjunctiveNormalForm::clauses(bool removed) const
{
    if (removed)
    {
        return this->m_clauses; 
    }
    else
    {
        std::vector<std::shared_ptr<Clause>> clauses;
        for (auto clause : m_clauses)
        {
            if (!clause->removed())
                clauses.push_back(clause);
        }
        return clauses;
    }
}

void ConjunctiveNormalForm::setClauses(std::vector<std::shared_ptr<Clause>> clauses)
{
   this->m_clauses = clauses; 
}

std::string ConjunctiveNormalForm::string(bool removed)
{
    std::stringstream out;
    unsigned int i = 0;

    for (auto clause : this->m_clauses)
    {
        if (!clause->removed() || removed)
        {
            if (i > 0)
                out << "&";
            out << clause->string(removed);
            ++i;
        }
    }

    return out.str();
}
void ConjunctiveNormalForm::addClause(Clause clause)
{
    this->m_clauses.push_back(std::make_shared<Clause>(clause));
}

void ConjunctiveNormalForm::addClausesFromLiterals(std::vector<Literal> literals)
{
    std::vector<std::shared_ptr<Literal>> sharedLiterals;
    for (auto literal : literals)
    {
        sharedLiterals.push_back(std::make_shared<Literal>(literal));
    }
    this->addClause(Clause(sharedLiterals));
}

void ConjunctiveNormalForm::addClausesFromCNF(ConjunctiveNormalForm cnf)
{
    std::vector<std::shared_ptr<Clause>> function = cnf.clauses();
    m_clauses.insert(m_clauses.end(), function.begin(), function.end());
}

bool ConjunctiveNormalForm::empty()
{
    int active = m_clauses.size();
    for (auto clause : m_clauses)
    {
        if (clause->removed())
            --active;
    }
    return active == 0;
}

bool ConjunctiveNormalForm::emptyClause()
{
    for (auto clause : m_clauses)
    {
        if (clause->literals().size() == 0)
            return true;
    }
    return false;
}

void ConjunctiveNormalForm::setVariable(int number, int value)
{
    for (auto clause : m_clauses)
    {
        for (auto literal : clause->literals())
        {
            if (literal->net()->number() == number)
            {
                literal->setValue(value);

                if (literal->inverted() && value == 1)
                    literal->remove();
                else if (literal->inverted() && value == 0)
                    clause->remove();
                else if (value == 1)
                    clause->remove();
                else if (value == 0)
                    literal->remove();
            }
        }
    }
}

int ConjunctiveNormalForm::getRightMost()
{
    std::vector<std::shared_ptr<Clause>> clauses;
    for (auto clause : m_clauses)
    {
        if (!clause->removed())
            clauses.push_back(clause);
    }
    std::vector<std::shared_ptr<Literal>> literals = clauses.back()->literals();
    for (auto it = literals.rbegin(); it != literals.rend(); ++it)
    {
        if ((*it)->value() == -1)
            return (*it)->net()->number();
    }
    return 0;
}
