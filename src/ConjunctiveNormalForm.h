#ifndef CONJUNCTIVENORMALFORM_H_
#define CONJUNCTIVENORMALFORM_H_

#include "Clause.h"
#include "Literal.h"

#include <vector>

class ConjunctiveNormalForm
{
    public:
        ConjunctiveNormalForm();
        ConjunctiveNormalForm(std::vector<Clause> clauses);
        ~ConjunctiveNormalForm();

        std::vector<Clause> function();
        void setFunction(std::vector<Clause> clauses);

        void addClause(Clause clause);
        void addClausesFromLiterals(std::vector<Literal> literals);
        void addClausesFromCNF(ConjunctiveNormalForm cnf);

        std::string string();
    private:
        std::vector<Clause> m_clauses;
};

#endif /* CONJUNCTIVENORMALFORM_H_ */
