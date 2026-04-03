#ifndef _I_PRINTABLE_
#define _I_PRINTABLE_

#include <iostream>

class I_Printable {
    friend std::ostream &operator<<(std::ostream &os, const I_Printable &obj);
private:
protected:
public:
    virtual void print(std::ostream &os) const = 0;
    virtual ~I_Printable() = default;
};

inline std::ostream &operator<<(std::ostream &os, const I_Printable &obj){
    obj.print(os);
    return os;
}

#endif