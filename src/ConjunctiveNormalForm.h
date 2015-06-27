#ifndef CONJUNCTIVENORMALFORM_H_
#define CONJUNCTIVENORMALFORM_H_

#include "Clause.h"
#include "Literal.h"

#include <vector>
#include <memory>

class ConjunctiveNormalForm
{
    public:
        ConjunctiveNormalForm();
        ConjunctiveNormalForm(std::vector<std::shared_ptr<Clause>> clauses);
        ~ConjunctiveNormalForm();

        std::vector<std::shared_ptr<Clause>> clauses();
        void setClauses(std::vector<std::shared_ptr<Clause>> clauses);

        void addClause(Clause clause);
        void addClausesFromLiterals(std::vector<Literal> literals);
        void addClausesFromCNF(ConjunctiveNormalForm cnf);

        std::string string();

        bool empty();
        bool emptyClause();
        void setVariable(int number, int value);
        int getRightMost();
    private:
        std::vector<std::shared_ptr<Clause>> m_clauses;
};

#endif /* CONJUNCTIVENORMALFORM_H_ */
