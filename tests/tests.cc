#include <gtest/gtest.h>
#include "../functions/include/broken_line.h"
#include <stdexcept>
#include <iostream>

using namespace broken_line;

TEST(FunctionsTests, PointDoubleTest) {
	Point a(-5.5, 5.5);
	Point b(-2.2, 2.2);
	EXPECT_NEAR(a.len(b), 4.6, 0.1);
}

TEST(FunctionsTests, PointTest) {
	Point<int> a;
	Point<int> b(1, 0);
	Point<int> c(a);
	Point<int> d = a;
	EXPECT_NEAR(a.len(b), 1, 0.1);
	EXPECT_TRUE(a == c);
	EXPECT_TRUE(a == d);
}

TEST(FunctionsTests, BrokenLineTest) {
	BrokenLine<int> line_1();
	Point point_2(1.1, 1.1);
	BrokenLine line_2(point_2);
	BrokenLine<double> line_3(5);
	BrokenLine<int> line_4(4, 1, 1, 5, 5);
	BrokenLine line_5(line_2);
	Point point_3(5.5, 5.5);
	Point point_4(6.6, 6.6);
	line_5.push_back(point_3);
	line_5.push_front(point_4);
	EXPECT_TRUE(line_5[0] == point_4);
	EXPECT_TRUE(line_5[line_5.size() - 1] == point_3);
	EXPECT_NEAR(line_5.len(), 14, 0.001);
	line_5 = line_2;
	BrokenLine<double> line_6 = line_5 + line_2;
}

TEST(FunctionsTests, SDL_File) {
	draw_trapezoid();
}
	//• конструктор с параметром : координата точки;
	//• конструктор с параметром : количество точек;
	//• конструктор с параметрами(создает ломаную из точек, координаты каждой из которых лежат в диапазоне[m1, m2];
	//• оператор[] для чтения / записи вершины ломаной по её индексу;
	//• оператор сложения двух ломаных(конкатенация);
	//• оператор сложения ломаной и вершины(добавление вершины в конец ломаной);
	//• оператор сложения вершины и ломаной(вставка вершины в начало ломаной);
	//• вычисление длины ломаной.
	// использованы только cin cout
	// реализовано правило трех и copy and swap