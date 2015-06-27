#ifndef CLAUSE_H_
#define CLAUSE_H_

#include "Literal.h"

#include <vector>

class Clause
{
    public:
        Clause();
        Clause(const Clause &clause);
        Clause(std::vector<std::shared_ptr<Literal>> literals);
        ~Clause();

        std::vector<std::shared_ptr<Literal>> literals() const;
        void setLiterals(std::vector<std::shared_ptr<Literal>> literals);

        std::string string();
    private:
        std::vector<std::shared_ptr<Literal>> m_literals;
};

#endif /* CLAUSE_H_ */
