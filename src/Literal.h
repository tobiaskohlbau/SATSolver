#ifndef LITERAL_H_
#define LITERAL_H_

class Literal
{
    public:
        Literal();
        Literal(int netNumber, bool inverted, int value);
        ~Literal();

        int netNumber();
        void setNetNumber(int netNumber);

        bool inverted();
        void setInverted(bool inverted);

        int value();
        void setValue(int value);
    private:
        int m_netNumber;
        bool m_inverted;
        int m_value;
};

#endif /* LITERAL_H_ */
