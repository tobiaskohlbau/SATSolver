#include "ConjunctiveNormalForm.h"

ConjunctiveNormalForm::ConjunctiveNormalForm()
{
}

ConjunctiveNormalForm::ConjunctiveNormalForm(std::vector<Clause> clauses) :
    m_clauses(clauses)
{
};

ConjunctiveNormalForm::~ConjunctiveNormalForm()
{
}


std::vector<Clause> ConjunctiveNormalForm::clauses()
{
    return m_clauses; 
};

void ConjunctiveNormalForm::setClauses(std::vector<Clause> clauses)
{
    this->m_clauses = clauses; 
};
