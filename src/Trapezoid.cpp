#include "../include/Trapezoid.h"
#include <cmath>

Trapezoid::Trapezoid() {
    vertices = new Point[n];
}

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

void Trapezoid::print(std::ostream& os) const {
    for (int i = 0; i < n; ++i) os << vertices[i] << " ";
}

void Trapezoid::read(std::istream& is) {
    std::cout << "Enter 4 trapezoid vertices separated by spaces (in x y format):\n";
    for (int i = 0; i < n; ++i) is >> vertices[i];
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
    if (typeid(*this) != typeid(other)) return false;
    return *this == static_cast<const Trapezoid&>(other);
}

bool Trapezoid::validate() const {
    if (std::abs(vertices[0].y - vertices[1].y) != std::abs(vertices[2].y - vertices[3].y)) return false; // Параллельность
    double side1 = vertices[1].distanceTo(vertices[2]);
    double side2 = vertices[0].distanceTo(vertices[3]);
    return std::abs(side1 - side2) < 1e-6;
}

Trapezoid::~Trapezoid() {
    delete[] vertices;
}