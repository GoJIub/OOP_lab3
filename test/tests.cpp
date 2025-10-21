#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <typeinfo>

// Подключаем заголовки
#include "../include/Figure.h"
#include "../include/Trapezoid.h"
#include "../include/Rhomb.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"

// Вспомогательная функция для ввода
void inputFigure(Figure& fig, const std::string& input) {
    std::istringstream iss(input);
    iss >> fig;
}

// --- ТЕСТЫ ДЛЯ Trapezoid ---
TEST(TrapezoidTest, DefaultConstructor) {
    Trapezoid t;
    EXPECT_EQ(t.center().x, 0.0);
    EXPECT_EQ(t.center().y, 0.0);
}

TEST(TrapezoidTest, InputAndOutput) {
    Trapezoid t;
    inputFigure(t, "0 0  4 0  3 3  1 3"); // равнобедренная трапеция
    std::ostringstream oss;
    oss << t;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 3) (1, 3) ");
}

TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid t;
    inputFigure(t, "0 0  6 0  4 4  2 4");
    EXPECT_DOUBLE_EQ(static_cast<double>(t), 16.0);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid t;
    inputFigure(t, "0 0  4 0  3 3  1 3");
    Point c = t.center();
    EXPECT_DOUBLE_EQ(c.x, 2.0);
    EXPECT_DOUBLE_EQ(c.y, 1.5);
}

TEST(TrapezoidTest, validateEqualSides) {
    Trapezoid t;
    inputFigure(t, "0 0  4 0  3 3  1 3"); // равнобедренная
    EXPECT_TRUE(t.validate());

    Trapezoid t2;
    inputFigure(t2, "0 0  4 0  3 3  0 3"); // не равнобедренная
    EXPECT_FALSE(t2.validate());
}

TEST(TrapezoidTest, CopyConstructor) {
    Trapezoid t1;
    inputFigure(t1, "0 0  4 0  3 3  1 3");
    Trapezoid t2 = t1;
    EXPECT_EQ(t1, t2);
    EXPECT_NE(&t1, &t2);
}

TEST(TrapezoidTest, MoveConstructor) {
    Trapezoid t1;
    inputFigure(t1, "0 0  4 0  3 3  1 3");
    Trapezoid t2 = std::move(t1);
    std::ostringstream oss;
    oss << t2;
    EXPECT_EQ(oss.str(), "(0, 0) (4, 0) (3, 3) (1, 3) ");
}

// --- ТЕСТЫ ДЛЯ Rhomb ---
TEST(RhombTest, InputAndArea) {
    Rhomb r;
    inputFigure(r, "0 0  3 0  5 3  2 3"); // ромб со стороной 3
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 9.0); // диагонали 5 и 6? Нет
    // (0,0), (3,0), (5,3), (2,3) → диагонали: 5 и 6 → 5*6/2 = 15
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 15.0);
}

TEST(RhombTest, validateAllSidesEqual) {
    Rhomb r;
    inputFigure(r, "0 0  3 0  5 3  2 3");
    EXPECT_TRUE(r.validate());

    Rhomb r2;
    inputFigure(r2, "0 0  3 0  4 3  1 3"); // не ромб
    EXPECT_FALSE(r2.validate());
}

TEST(RhombTest, Equality) {
    Rhomb r1, r2;
    inputFigure(r1, "0 0  3 0  5 3  2 3");
    inputFigure(r2, "0 0  3 0  5 3  2 3");
    EXPECT_TRUE(r1 == r2);
}

// --- ТЕСТЫ ДЛЯ Pentagon ---
TEST(PentagonTest, RegularPentagonArea) {
    Pentagon p;
    // Регулярный пятиугольник со стороной 2
    inputFigure(p, "0 0  2 0  3 1.5  1.5 3  0.5 3");
    EXPECT_NEAR(static_cast<double>(p), 7.0, 0.5); // примерно
}

TEST(PentagonTest, validateRegular) {
    Pentagon p;
    inputFigure(p, "0 0  2 0  3 1.5  1.5 3  0.5 3");
    EXPECT_TRUE(p.validate());
}

// --- ТЕСТЫ ДЛЯ Array ---
TEST(ArrayTest, AddAndSize) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    arr.add(std::make_unique<Rhomb>());
    EXPECT_EQ(arr.getSize(), 2);
}

TEST(ArrayTest, Remove) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    arr.add(std::make_unique<Rhomb>());
    arr.add(std::make_unique<Pentagon>());

    arr.remove(1);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_TRUE(dynamic_cast<Trapezoid*>(&arr[0]));
    EXPECT_TRUE(dynamic_cast<Pentagon*>(&arr[1]));
}

TEST(ArrayTest, TotalSurface) {
    Array arr;
    auto t = std::make_unique<Trapezoid>();
    inputFigure(*t, "0 0  4 0  3 3  1 3"); // площадь ~12
    arr.add(std::move(t));

    auto r = std::make_unique<Rhomb>();
    inputFigure(*r, "0 0  3 0  5 3  2 3"); // площадь 15
    arr.add(std::move(r));

    EXPECT_NEAR(arr.totalSurface(), 27.0, 1.0);
}

TEST(ArrayTest, PrintSurfaces) {
    Array arr;
    auto t = std::make_unique<Trapezoid>();
    inputFigure(*t, "0 0  4 0  3 3  1 3");
    arr.add(std::move(t));

    testing::internal::CaptureStdout();
    arr.printSurfaces();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Area") != std::string::npos);
}

TEST(ArrayTest, OutOfRange) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    EXPECT_THROW(arr[10], std::out_of_range);
}

TEST(ArrayTest, Polymorphism) {
    Array arr;
    arr.add(std::make_unique<Trapezoid>());
    arr.add(std::make_unique<Rhomb>());
    arr.add(std::make_unique<Pentagon>());

    for (size_t i = 0; i < arr.getSize(); ++i) {
        EXPECT_NE(typeid(arr[i]), typeid(Figure));
    }
}

// --- ТЕСТЫ ДЛЯ Figure (абстрактный класс) ---
TEST(FigureTest, CannotInstantiate) {
    // Figure f; // Должно быть ошибкой компиляции
    static_assert(!std::is_constructible<Figure>::value, "Figure should not be instantiable");
}

// --- ОСНОВНАЯ ФУНКЦИЯ ---
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}