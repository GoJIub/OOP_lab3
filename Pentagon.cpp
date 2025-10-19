#include "Pentagon.h"
#include <cmath>

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
    for (int i = 0; i < n; ++i) {
        if (vertices[i].x != o->vertices[i].x || vertices[i].y != o->vertices[i].y)
            return false;
    }
    return true;
}

bool Pentagon::validate() const {
    double side = vertices[0].distanceTo(vertices[1]);
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double currSide = vertices[i].distanceTo(vertices[j]);
        if (std::abs(currSide - side) > 1e-6) return false;
    }
    return true;
}

Pentagon::~Pentagon() {
    delete[] vertices;
}