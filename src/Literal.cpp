#include "Literal.h"

Literal::Literal()
{
}

Literal::Literal(int netNumber, bool inverted, int value) :
    m_netNumber(netNumber),
    m_inverted(inverted),
    m_value(value)
{
};

Literal::~Literal()
{
}


int Literal::netNumber()
{
    return this->m_netNumber;
}

void Literal::setNetNumber(int netNumber)
{
    this->m_netNumber = netNumber;
};

bool Literal::inverted()
{
    return this->m_inverted;
};

void Literal::setInverted(bool inverted)
{
    this->m_inverted = inverted;
};

int Literal::value()
{
    return m_value;
};

void Literal::setValue(int value)
{
    this->m_value = value; 
};
