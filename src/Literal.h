#ifndef LITERAL_H_
#define LITERAL_H_

#include "Net.h"

#include <memory>

class Literal
{
    public:
        Literal();
        Literal(const Literal &literal);
        Literal(std::shared_ptr<Net> net, bool inverted, int value);
        ~Literal();

        std::shared_ptr<Net> net() const;
        void setNet(std::shared_ptr<Net> net);

        bool inverted() const;
        void setInverted(bool inverted);

        int value() const;
        void setValue(int value);

        std::string string();
    private:
        std::shared_ptr<Net> m_net;
        bool m_inverted;
        int m_value;
};

#endif /* LITERAL_H_ */
