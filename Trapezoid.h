#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"

class Trapezoid : public Figure
{
public:

    Trapezoid() = default;
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    virtual Point center() const override;
    virtual double surface() const override;
    // virtual bool validate() const override;

    virtual operator double() const override;
    virtual bool operator==(const Figure& other) const override;

    ~Trapezoid();

private:
    Point* vertices{nullptr};
    int n{0};
};

#endif