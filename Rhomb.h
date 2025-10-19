#ifndef RHOMB_H
#define RHOMB_H

#include "Figure.h"

class Rhomb : public Figure
{
public:

    Rhomb() = default;
    Rhomb(const Rhomb& other);
    Rhomb(Rhomb&& other) noexcept;

    Rhomb& operator=(const Rhomb& other);
    Rhomb& operator=(Rhomb&& other) noexcept;

    virtual Point center() const override;
    virtual double surface() const override;
    // virtual bool validate() const override;

    virtual operator double() const override;
    virtual bool operator==(const Figure& other) const override;

    ~Rhomb();

private:
    Point* vertices{nullptr};
    int n{0};
};

#endif