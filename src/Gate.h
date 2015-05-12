#ifndef GATE_H_
#define GATE_H_

#include "Net.h"
#include "ConjunctiveNormalForm.h"

#include <vector>
#include <memory>

class Gate
{
    public:
        enum class Type
        {
            AND,
            OR,
            INV,
            XOR,
            ZERO,
            ONE,
            EQUAL,
            UNKNOWN
        };

        Gate();
        Gate(Type type, std::vector<std::shared_ptr<Net>> nets);
        ~Gate();

        Type type() const;
        std::string typeAsString();
        void setType(Type type);

        std::vector<std::shared_ptr<Net>> nets() const;
        void setNets(std::vector<std::shared_ptr<Net>> nets);

        ConjunctiveNormalForm characteristicFunction();
    private:
        Type m_type;
        std::vector<std::shared_ptr<Net>> m_nets;
};

#endif /* GATE_H_ */
