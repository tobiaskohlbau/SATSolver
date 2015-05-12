#ifndef LITERAL_H_
#define LITERAL_H_

#include "Net.h"

#include <memory>

class Literal
{
    public:
        Literal();
        Literal(std::shared_ptr<Net> net, bool inverted, int value);
        ~Literal();

        std::shared_ptr<Net> net();
        void setNet(std::shared_ptr<Net> net);

        bool inverted();
        void setInverted(bool inverted);

        int value();
        void setValue(int value);

        std::string string();
    private:
        std::shared_ptr<Net> m_net;
        bool m_inverted;
        int m_value;
};

#endif /* LITERAL_H_ */
