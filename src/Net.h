#ifndef NET_H_
#define NET_H_

#include <string>

class Net
{
    public:
        Net();
        Net(unsigned int number, std::string name = "undefined");
        ~Net();

        unsigned int number() const;
        void setNumber(unsigned int number);

        std::string name() const;
        void setName(std::string name);
    private:
        int m_number;
        std::string m_name;
};

#endif /* NET_H_ */
