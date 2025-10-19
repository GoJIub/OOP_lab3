#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string.h>
#include <string_view>

#include "Point.h"

class Figure
{
    friend std::ostream& operator<<(std::ostream& os, const Figure& f);
    friend std::istream& operator>>(std::istream& is, Figure& f);

protected:
    Figure() = default;

    virtual void Print(std::ostream& os) const = 0;
    virtual void Read(std::istream& is) = 0;
    virtual bool validate() const = 0;

public:
    virtual ~Figure() = default;

    virtual Point center() const = 0;
    virtual double surface() const = 0;

    virtual operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.Print(os);
    return os;
}

inline std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.Read(is);
    return is;
}

#endif