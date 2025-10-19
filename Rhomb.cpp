#include "Rhomb.h"
#include <cmath>

Rhomb::Rhomb(const Rhomb& other) : n(other.n) {
    vertices = new Point[n];
    for (int i = 0; i < n; ++i) vertices[i] = other.vertices[i];
}

Rhomb::Rhomb(Rhomb&& other) noexcept : vertices(other.vertices), n(other.n) {
    other.vertices = nullptr;
    other.n = 0;
}

Rhomb& Rhomb::operator=(const Rhomb& other) {
    if (this == &other) return *this;

    delete[] vertices;

    n = other.n;
    vertices = new Point[n];
    for (int i = 0; i < n; ++i) vertices[i] = other.vertices[i];

    return *this;
}

Rhomb& Rhomb::operator=(Rhomb&& other) noexcept {
    if (this == &other) return *this;

    delete[] vertices;

    n = other.n;
    vertices = other.vertices;

    other.vertices = nullptr;
    other.n = 0;

    return *this;
}

Point Rhomb::center() const {
    double cx{0.0}, cy {0.0};
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point{cx / n, cy / n};
}

double Rhomb::surface() const {
    double d1 = vertices[0].distanceTo(vertices[1]);
    double d2 = vertices[2].distanceTo(vertices[3]);
    return d1 * d2 / 2.0;
}

Rhomb::operator double() const {
    return surface();
}

bool Rhomb::operator==(const Figure& other) const {
    const Rhomb* o = dynamic_cast<const Rhomb*>(&other);
    if (!o) return false;
    for (int i = 0; i < n; ++i) {
        if (vertices[i].x != o->vertices[i].x || vertices[i].y != o->vertices[i].y)
            return false;
    }
    return true;
}

bool Rhomb::validate() const {
    double side1 = vertices[0].distanceTo(vertices[1]);
    double side2 = vertices[1].distanceTo(vertices[2]);
    double side3 = vertices[2].distanceTo(vertices[3]);
    double side4 = vertices[3].distanceTo(vertices[0]);
    return std::abs(side1 - side2) < 1e-6 && std::abs(side2 - side3) < 1e-6 &&
           std::abs(side3 - side4) < 1e-6;
}

Rhomb::~Rhomb() {
    delete[] vertices;
}