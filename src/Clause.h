#ifndef CLAUSE_H_
#define CLAUSE_H_

#include "Literal.h"

#include <vector>

class Clause
{
    public:
        Clause();
        Clause(std::vector<Literal> literals);
        ~Clause();

        std::vector<Literal> literals();
        void setLiterals(std::vector<Literal> literals);
    private:
        std::vector<Literal> m_literals;
};

#endif /* CLAUSE_H_ */
