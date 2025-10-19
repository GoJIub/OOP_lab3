#include "Trapezoid.h"
#include <cmath>

Trapezoid::Trapezoid(const Trapezoid& other) : n(other.n) {
    vertices = new Point[n];
    for (int i = 0; i < n; ++i) vertices[i] = other.vertices[i];
}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept : vertices(other.vertices), n(other.n) {
    other.vertices = nullptr;
    other.n = 0;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this == &other) return *this;

    delete[] vertices;

    n = other.n;
    vertices = new Point[n];
    for (int i = 0; i < n; ++i) vertices[i] = other.vertices[i];

    return *this;
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this == &other) return *this;

    delete[] vertices;

    n = other.n;
    vertices = other.vertices;

    other.vertices = nullptr;
    other.n = 0;

    return *this;
}

Point Trapezoid::center() const {
    double cx{0.0}, cy {0.0};
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point{cx / n, cy / n};
}

double Trapezoid::surface() const {
    double a = vertices[0].distanceTo(vertices[1]);
    double b = vertices[2].distanceTo(vertices[3]);
    double h = std::abs(vertices[0].y - vertices[2].y);
    return (a + b) * h / 2.0;
}

Trapezoid::operator double() const {
    return surface();
}

bool Trapezoid::operator==(const Figure& other) const {
    const Trapezoid* o = dynamic_cast<const Trapezoid*>(&other);
    if (!o) return false;
    for (int i = 0; i < n; ++i) {
        if (vertices[i].x != o->vertices[i].x || vertices[i].y != o->vertices[i].y)
            return false;
    }
    return true;
}

Trapezoid::~Trapezoid() {
    delete[] vertices;
}