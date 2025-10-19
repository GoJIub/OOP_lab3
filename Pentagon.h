#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure
{
public:

    Pentagon() = default;
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    virtual Point center() const override;
    virtual double surface() const override;
    // virtual bool validate() const override;

    virtual operator double() const override;
    virtual bool operator==(const Figure& other) const override;

    ~Pentagon();

private:
    Point* vertices{nullptr};
    int n{0};
};

#endif