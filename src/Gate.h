#ifndef GATE_H_
#define GATE_H_

#include "Net.h"

#include <vector>

class Gate
{
    public:
        enum class Type
        {
            UNKNOWN,
            AND,
            OR,
            INV,
            XOR,
            ZERO,
            ONE
        };

        Gate();
        Gate(Type type, std::vector<Net> nets);
        ~Gate();

        void setType(Type type);
        void setIONets(std::vector<Net> nets);
    private:
        Type m_type;
        std::vector<Net> m_ioNets;
};

#endif /* GATE_H_ */
