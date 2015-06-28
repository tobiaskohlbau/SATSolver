#ifndef LITERAL_H_
#define LITERAL_H_

#include "Net.h"

#include <memory>

class Literal
{
    public:
        Literal();
        Literal(const Literal &literal);
        Literal(unsigned int netNumber, bool inverted, int value);
        ~Literal();

        unsigned int netNumber() const;
        void setNetNumber(unsigned int netNumber);

        bool inverted() const;
        void setInverted(bool inverted);

        int value() const;
        void setValue(int value);

        std::string string();
    private:
        unsigned int m_netNumber;
        bool m_inverted;
        int m_value;
};

#endif /* LITERAL_H_ */
