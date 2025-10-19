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

    Point* vertices{nullptr};
    int n{0};

public:
    virtual ~Figure() = default;

    virtual Point center() const = 0;
    virtual double surface() const = 0;
    // virtual bool validate() const = 0;

    virtual operator double() const = 0;
    virtual bool operator==(const Figure& other) const = 0;
};

inline std::istream& operator>>(std::istream& is, Figure& f) {
    std::cout << "Введите " << f.n << " вершин (x y):\n";
    for (int i = 0; i < f.n; ++i) is >> f.vertices[i];
}

inline std::ostream& operator<<(std::ostream& os, const Figure& f) {
    for (int i = 0; i < f.n; ++i) os << f.vertices[i] << " ";
}

#endif