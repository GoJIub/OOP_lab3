#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure
{
public:
    Pentagon();

    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    virtual void print(std::ostream& os) const override;
    virtual void read(std::istream& is) override;

    virtual Point center() const override;
    virtual double surface() const override;

    virtual operator double() const override;
    
    bool operator==(const Pentagon& other) const = default;
    virtual bool operator==(const Figure& other) const override;
    
    virtual bool validate() const override;

    ~Pentagon();

private:
    Point* vertices{nullptr};
    int n{5};
};

#endif