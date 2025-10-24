#include "../include/Pentagon.h"
#include <cmath>

Pentagon::Pentagon() {
    vertices = new Point[n];
}

Pentagon::Pentagon(const Pentagon& other) : n(other.n) {
    vertices = new Point[n];
    for (int i = 0; i < n; ++i) vertices[i] = other.vertices[i];
}

Pentagon::Pentagon(Pentagon&& other) noexcept : vertices(other.vertices), n(other.n) {
    other.vertices = nullptr;
    other.n = 0;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this == &other) return *this;

    delete[] vertices;

    n = other.n;
    vertices = new Point[n];
    for (int i = 0; i < n; ++i) vertices[i] = other.vertices[i];

    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this == &other) return *this;

    delete[] vertices;

    n = other.n;
    vertices = other.vertices;

    other.vertices = nullptr;
    other.n = 0;

    return *this;
}

void Pentagon::print(std::ostream& os) const {
    for (int i = 0; i < n; ++i) os << vertices[i] << " ";
}

void Pentagon::read(std::istream& is) {
    if (is.rdbuf() == std::cin.rdbuf())
        std::cout << "Enter 5 pentagon vertices separated by spaces (in x y format):\n";

    for (int i = 0; i < n; ++i) is >> vertices[i];
    if (!validate()) throw std::invalid_argument("The entered points do not form a pentagon!");
}

Point Pentagon::center() const {
    double cx{0.0}, cy {0.0};
    for (int i = 0; i < n; ++i) {
        cx += vertices[i].x;
        cy += vertices[i].y;
    }
    return Point{cx / n, cy / n};
}

double Pentagon::surface() const {
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

Pentagon::operator double() const {
    return surface();
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* o = dynamic_cast<const Pentagon*>(&other);
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

bool Pentagon::operator!=(const Figure& other) const {
    return !(other == *this);
}

bool Pentagon::validate() const {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (vertices[i].x == vertices[j].x &&
                vertices[i].y == vertices[j].y) {
                return false;
            }
        }
    }

    double side = vertices[0].distanceTo(vertices[1]);
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double currSide = vertices[i].distanceTo(vertices[j]);
        if (std::abs(currSide - side) > 1) return false;
    }
    return true;
}

Pentagon::~Pentagon() {
    delete[] vertices;
}