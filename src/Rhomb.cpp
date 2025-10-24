#include "../include/Rhomb.h"
#include <cmath>

Rhomb::Rhomb() {
    vertices = new Point[n];
}

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

void Rhomb::print(std::ostream& os) const {
    for (int i = 0; i < n; ++i) os << vertices[i] << " ";
}

void Rhomb::read(std::istream& is) {
    if (is.rdbuf() == std::cin.rdbuf())
        std::cout << "Enter 4 rhomb vertices separated by spaces (in x y format):\n";
    
    for (int i = 0; i < n; ++i) is >> vertices[i];
    if (!validate()) throw std::invalid_argument("The entered points do not form a rhomb!");
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
    double d1 = vertices[0].distanceTo(vertices[2]);
    double d2 = vertices[1].distanceTo(vertices[3]);
    return d1 * d2 / 2.0;
}

Rhomb::operator double() const {
    return surface();
}

bool Rhomb::operator==(const Figure& other) const {
    const Rhomb* o = dynamic_cast<const Rhomb*>(&other);
    if (!o) return false;

    for (int shift = 0; shift < n; ++shift) {
        bool match = true;
        for (int i = 0; i < n; ++i) {
            int shifted_index = (i + shift) % n;
            if (vertices[i].x != o->vertices[shifted_index].x ||
                vertices[i].y != o->vertices[shifted_index].y) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

bool Rhomb::operator!=(const Figure& other) const {
    return !(other == *this);
}

bool Rhomb::validate() const {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vertices[i].x == vertices[j].x &&
                vertices[i].y == vertices[j].y) {
                return false;
            }
        }
    }
    
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