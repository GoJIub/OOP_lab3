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

    virtual void print(std::ostream& os) const override;
    virtual void read(std::istream& is) override;

    virtual Point center() const override;
    virtual double surface() const override;

    virtual operator double() const override;
    
    bool operator==(const Trapezoid& other) const = default;
    virtual bool operator==(const Figure& other) const override;
    
    virtual bool validate() const override;

    ~Trapezoid();

private:
    Point* vertices{nullptr};
    int n{4};
};

#endif