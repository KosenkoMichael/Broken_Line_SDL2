#include <gtest/gtest.h>
#include "../functions/include/broken_line.h"

using namespace broken_line;

TEST(FunctionsTests, PointDoubleTest) {
	Point point_1(-5.5, 5.5);
	Point point_2(-2.2, 2.2);
	EXPECT_NEAR(len(point_1, point_2), 4.6, 0.1);
}

TEST(FunctionsTests, PointTest) {
	Point<int> point_a;
	Point<int> point_b(1, 0);
	Point<int> point_c(point_a);
	Point<int> point_d = point_a;
	EXPECT_NEAR(len(point_a, point_b), 1, 0.1);
	EXPECT_TRUE(point_a == point_c);
	EXPECT_TRUE(point_a == point_d);
}
TEST(FunctionsTests, BrokenLineTest) {
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
	EXPECT_NEAR(line_5.full_len(), 14, 0.001);
	line_5 = line_2;
	BrokenLine<double> line_6 = line_5 + line_2;
}
TEST(FunctionsTests, BrokenLineComplexTest) {
	Point<std::complex<double>> complex_1({1,1}, {2,2});
	Point<std::complex<double>> complex_2({ 1,5 }, { 5,1 });
	EXPECT_NEAR(len(complex_1, complex_2), 3, 0.001);
}
TEST(FunctionsTests, SDL_File) {
	draw_trapezoid();
}