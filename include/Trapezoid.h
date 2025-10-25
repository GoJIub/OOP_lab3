#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

class Trapezoid : public Figure
{
public:
    Trapezoid();

    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Point center() const override;
    double surface() const override;

    operator double() const override;
    bool operator==(const Figure& other) const override;
    bool operator!=(const Figure& other) const override;
    
    bool validate() const override;

    ~Trapezoid();

private:
    Point* vertices{nullptr};
    int n{4};
};

#endif