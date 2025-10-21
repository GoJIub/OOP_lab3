#ifndef RHOMB_H
#define RHOMB_H

#include "Figure.h"

class Rhomb : public Figure
{
public:
    Rhomb();

    Rhomb(const Rhomb& other);
    Rhomb(Rhomb&& other) noexcept;

    Rhomb& operator=(const Rhomb& other);
    Rhomb& operator=(Rhomb&& other) noexcept;

    virtual void print(std::ostream& os) const override;
    virtual void read(std::istream& is) override;

    virtual Point center() const override;
    virtual double surface() const override;

    virtual operator double() const override;

    bool operator==(const Rhomb& other) const = default;
    virtual bool operator==(const Figure& other) const override;
    
    virtual bool validate() const override;

    ~Rhomb();

private:
    Point* vertices{nullptr};
    int n{4};
};

#endif