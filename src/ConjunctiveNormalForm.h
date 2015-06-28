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
        ConjunctiveNormalForm(const ConjunctiveNormalForm &cnf);
        ConjunctiveNormalForm(std::vector<std::shared_ptr<Clause>> clauses);
        ~ConjunctiveNormalForm();

        std::vector<std::shared_ptr<Clause>> clauses(bool removed = false) const;
        void setClauses(std::vector<std::shared_ptr<Clause>> clauses);

        void addClause(Clause clause);
        void addClausesFromLiterals(std::vector<Literal> literals);
        void addClausesFromCNF(ConjunctiveNormalForm cnf);

        std::string string(bool removed = false);

        void remove(Clause *clause);
        void removeLiteralsByNumber(unsigned int number);
        void removeClauseByLiteral(Literal *literal);

        bool empty();
        bool emptyClause();
        void setVariable(unsigned int number, int value);
        int getRightMost();
    private:
        std::vector<std::shared_ptr<Clause>> m_clauses;
        std::vector<std::shared_ptr<Clause>> m_removedClauses;
};

#endif /* CONJUNCTIVENORMALFORM_H_ */
