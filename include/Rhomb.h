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

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Point center() const override;
    double surface() const override;

    operator double() const override;
    bool operator==(const Figure& other) const override;
    bool operator!=(const Figure& other) const override;
    
    bool validate() const override;

    ~Rhomb();

private:
    Point* vertices{nullptr};
    int n{4};
};

#endif