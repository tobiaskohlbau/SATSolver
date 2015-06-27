#include "Literal.h"

#include <sstream>

Literal::Literal()
{
}

Literal::Literal(const Literal &literal) :
    m_net(literal.net()),
    m_inverted(literal.inverted()),
    m_value(literal.value())
{
}

Literal::Literal(std::shared_ptr<Net> net, bool inverted, int value) :
    m_net(net),
    m_inverted(inverted),
    m_value(value)
{
}

Literal::~Literal()
{
}


std::shared_ptr<Net> Literal::net() const
{
    return this->m_net;
}

void Literal::setNet(std::shared_ptr<Net> net)
{
    this->m_net= net;
}

bool Literal::inverted() const
{
    return this->m_inverted;
}

void Literal::setInverted(bool inverted)
{
    this->m_inverted = inverted;
}

int Literal::value() const
{
    return m_value;
}

void Literal::setValue(int value)
{
    this->m_value = value; 
}

std::string Literal::string()
{
    std::stringstream out;
    if (this->m_inverted)
        out << "!";
    out << this->m_net->number();
    out << "(" << this->m_value << ")";

    return out.str();
}
