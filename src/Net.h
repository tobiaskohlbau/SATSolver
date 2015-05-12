#ifndef NET_H_
#define NET_H_

#include <string>

class Net
{
    public:
        Net();
        Net(int number, std::string name = "undefined");
        ~Net();

        int number();
        void setNumber(int number);

        std::string name();
        void setName(std::string name);
    private:
        int m_number;
        std::string m_name;
};

#endif /* NET_H_ */
