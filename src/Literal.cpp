#include "Literal.h"

#include <sstream>

Literal::Literal()
{
}

Literal::Literal(const Literal &literal) :
    m_netNumber(literal.netNumber()),
    m_inverted(literal.inverted()),
    m_value(literal.value())
{
}

Literal::Literal(unsigned int netNumber, bool inverted, int value) :
    m_netNumber(netNumber),
    m_inverted(inverted),
    m_value(value)
{
}

Literal::~Literal()
{
}


unsigned int Literal::netNumber() const
{
    return this->m_netNumber;
}

void Literal::setNetNumber(unsigned int netNumber)
{
    this->m_netNumber= netNumber;
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
    out << this->m_netNumber;
    out << "(" << this->m_value << ")";

    return out.str();
}
