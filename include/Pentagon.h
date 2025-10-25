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

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    Point center() const override;
    double surface() const override;

    operator double() const override;
    bool operator==(const Figure& other) const override;
    bool operator!=(const Figure& other) const override;
    
    bool validate() const override;

    ~Pentagon();

private:
    Point* vertices{nullptr};
    int n{5};
};

#endif