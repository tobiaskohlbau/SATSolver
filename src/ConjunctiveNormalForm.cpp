#include "ConjunctiveNormalForm.h"

#include <sstream>
#include <iostream>

ConjunctiveNormalForm::ConjunctiveNormalForm()
{
}

ConjunctiveNormalForm::ConjunctiveNormalForm(std::vector<std::shared_ptr<Clause>> clauses) :
    m_clauses(clauses)
{
}

ConjunctiveNormalForm::~ConjunctiveNormalForm()
{
}


std::vector<std::shared_ptr<Clause>> ConjunctiveNormalForm::clauses()
{
    return this->m_clauses; 
}

void ConjunctiveNormalForm::setClauses(std::vector<std::shared_ptr<Clause>> clauses)
{
   this->m_clauses = clauses; 
}

std::string ConjunctiveNormalForm::string()
{
    std::stringstream out;
    unsigned int i = 0;

    for (auto clause : this->m_clauses)
    {
        if (i > 0)
            out << "&";
        out << clause->string();
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

bool ConjunctiveNormalForm::empty()
{
    return false;
}

bool ConjunctiveNormalForm::emptyClause()
{
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
            }
        }
    }
}

int ConjunctiveNormalForm::getRightMost()
{
    return m_clauses.back()->literals().back()->net()->number();
}
