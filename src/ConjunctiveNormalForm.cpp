#include "ConjunctiveNormalForm.h"

#include <sstream>
#include <iostream>
#include <algorithm>

ConjunctiveNormalForm::ConjunctiveNormalForm()
{
}

ConjunctiveNormalForm::ConjunctiveNormalForm(const ConjunctiveNormalForm &cnf) 
{
    for (auto clause : cnf.clauses())
    {
        m_clauses.push_back(std::make_shared<Clause>(*clause));
    }

    for (auto clause : cnf.clauses(true))
    {
        m_removedClauses.push_back(std::make_shared<Clause>(*clause));
    }

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
    if (!removed)
    {
        return this->m_clauses; 
    }
    else
    {
        return this->m_removedClauses;
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

    for (auto clause : this->clauses(removed))
    {
        if (i > 0)
            out << "&";
        out << clause->string(removed);
        ++i;
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

void ConjunctiveNormalForm::remove(Clause *clause)
{
    auto it = std::find_if(m_clauses.begin(), m_clauses.end(), [&clause](std::shared_ptr<Clause> const &p) {
        return p.get() == clause;
    });
    if (it != m_clauses.end())
    {
        m_removedClauses.push_back(*it);
        m_clauses.erase(it);
        m_clauses.shrink_to_fit();
    }
}

void ConjunctiveNormalForm::removeLiteralsByNumber(unsigned int number)
{
    for (auto clause : m_clauses)
    {
        for (auto literal : clause->literals())
        {
            if (literal->netNumber() == number)
                clause->remove(literal.get());
        }
    }
}

void ConjunctiveNormalForm::removeClauseByLiteral(Literal *literal)
{
    for (auto clause : m_clauses)
    {
        for (auto lit : clause->literals())
        {
            if (lit.get() == literal)
                this->remove(clause.get());
        }
    }
}

bool ConjunctiveNormalForm::empty()
{
    return m_clauses.size() == 0;
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

void ConjunctiveNormalForm::setVariable(unsigned int number, int value)
{
    auto clauses = m_clauses;
    auto removedClauses = m_removedClauses;
    clauses.insert(clauses.end(), removedClauses.begin(), removedClauses.end());
    for (auto clause : clauses)
    {
        auto literals = clause->literals();
        auto removedLiterals = clause->literals(true);
        literals.insert(literals.end(), removedLiterals.begin(), removedLiterals.end());
        for (auto literal : literals)
        {
            if (literal->netNumber() == number)
            {
                literal->setValue(value);

                if (literal->inverted() && value == 1)
                    clause->remove(literal.get());
                else if (literal->inverted() && value == 0)
                    this->remove(clause.get());
                else if (value == 1)
                    this->remove(clause.get());
                else if (value == 0)
                    clause->remove(literal.get());
            }
        }
    }
}

int ConjunctiveNormalForm::getRightMost()
{
    std::vector<std::shared_ptr<Literal>> literals = m_clauses.back()->literals();
    for (auto it = literals.rbegin(); it != literals.rend(); ++it)
    {
        if ((*it)->value() == -1)
            return (*it)->netNumber();
    }
    return 0;
}
