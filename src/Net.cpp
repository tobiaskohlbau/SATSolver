#include "Net.h"

Net::Net()
{
}

Net::Net(unsigned int number, std::string name) :
    m_number(number),
    m_name(name)
{
        
}

Net::~Net()
{
}

unsigned int Net::number() const
{
    return this->m_number; 
}

void Net::setNumber(unsigned int number)
{
    this->m_number = number; 
}

std::string Net::name() const
{
    return this->m_name; 
}

void Net::setName(std::string name)
{
    this->m_name = name;
}
