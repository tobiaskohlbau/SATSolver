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

        std::vector<std::shared_ptr<Literal>> literals(bool removed = false) const;
        void setLiterals(std::vector<std::shared_ptr<Literal>> literals);

        std::string string(bool removed = false);
        void remove(Literal *literal);
    private:
        std::vector<std::shared_ptr<Literal>> m_literals;
        std::vector<std::shared_ptr<Literal>> m_removedLiterals;
};

#endif /* CLAUSE_H_ */
