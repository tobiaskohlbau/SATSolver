#include "ConjunctiveNormalForm.h"

#include <sstream>

ConjunctiveNormalForm::ConjunctiveNormalForm()
{
}

ConjunctiveNormalForm::ConjunctiveNormalForm(std::vector<Clause> clauses) :
    m_clauses(clauses)
{
}

ConjunctiveNormalForm::~ConjunctiveNormalForm()
{
}


std::vector<Clause> ConjunctiveNormalForm::function()
{
    return this->m_clauses; 
}

void ConjunctiveNormalForm::setFunction(std::vector<Clause> clauses)
{
    this->m_clauses = clauses; 
}

std::string ConjunctiveNormalForm::string()
{
    std::stringstream out;
    unsigned int i = 0;

    for (Clause clause : this->m_clauses)
    {
        if (i > 0)
            out << "&";
        out << clause.string();
        ++i;
    }

    return out.str();
}
void ConjunctiveNormalForm::addClause(Clause clause)
{
    this->m_clauses.push_back(clause);
}

void ConjunctiveNormalForm::addClausesFromLiterals(std::vector<Literal> literals)
{
    this->addClause(Clause(literals));
}

void ConjunctiveNormalForm::addClausesFromCNF(ConjunctiveNormalForm cnf)
{
    std::vector<Clause> function = cnf.function();
    m_clauses.insert(m_clauses.end(), function.begin(), function.end());
}
