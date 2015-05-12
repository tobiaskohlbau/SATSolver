#ifndef CONJUNCTIVENORMALFORM_H_
#define CONJUNCTIVENORMALFORM_H_

#include "Clause.h"

#include <vector>

class ConjunctiveNormalForm
{
    public:
        ConjunctiveNormalForm();
        ConjunctiveNormalForm(std::vector<Clause> clauses);
        ~ConjunctiveNormalForm();

        std::vector<Clause> clauses();
        void setClauses(std::vector<Clause> clauses);
    private:
        std::vector<Clause> m_clauses;
};

#endif /* CONJUNCTIVENORMALFORM_H_ */
