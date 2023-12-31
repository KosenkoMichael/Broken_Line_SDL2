#pragma once

#include <iostream>
#include <stdlib.h>
#include <random>
#include <conio.h>
#include <cmath>
#include <windows.h>
#include <fstream>
#include <stdexcept>
#include <complex>

using namespace std;

namespace broken_line {

	template<typename T>
	T random(T a, T b) {
		std::random_device random_device; // Источник энтропии.
		std::mt19937 generator(random_device()); // Генератор случайных чисел.
		// (Здесь берется одно инициализирующее значение, можно брать больше)
		std::uniform_int_distribution<> distribution(a, b); // Равномерное распределение [a, b]
		T x = distribution(generator); // Случайное число.
		return x;
	}

	template<typename T>
	struct Point {
		T x;
		T y;
		Point() :x(0), y(0) {}
		Point(T _x, T _y) :x(_x), y(_y) {}
		Point(const Point<T>& rhs) :x(rhs.x), y(rhs.y) {}
		bool operator == (Point<T> rhs) {
			if ((x == rhs.x) && (y == rhs.y))
				return true;
			return false;
		}
		void operator = (Point<T> rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		T get_x() {
			return x;
		}
		T get_y() {
			return y;
		}
	};
	template<typename U>
	double len(Point<complex<U>>& lhs, Point<complex<U>>& rhs) {
		return sqrt(pow(lhs.get_x().real() - rhs.get_x().real(), 2) + pow(lhs.get_y().real() - rhs.get_y().real(), 2));
	}
	template<typename T>
	double len(Point<T>& lhs, Point<T>& rhs) {
		return sqrt(pow(lhs.get_x() - rhs.get_x(), 2) + pow(lhs.get_y() - rhs.get_y(), 2));
	}

	template<typename T>
	ostream& operator<<(ostream& stream, Point<T>& point) {
		cout << point.x << " " << point.y;
		return stream;
	}

	template<typename T>
	class BrokenLine {
		Point<T>** _data;
		int _size;
	public:
		BrokenLine() {
			_data = new Point<T>*;
			_data[0] = new Point<T>;
			_size = 1;
		}
		BrokenLine(Point<T>& rhs) { // Конструктор по координатам точки
			_data = new Point<T>*;
			_data[0] = new Point<T>(rhs.x, rhs.y);
			_size = 1;
		}
		BrokenLine(size_t size) { // Конструктор по размеру
			_data = new Point<T>*[size];
			for (int i = 0; i < size; ++i)
				_data[i] = new Point<T>;
			_size = size;
		}
		BrokenLine(int count, T x1, T x2, T y1, T y2) { // Диапазон точек
			_data = new Point<T>*[count];
			for (int i = 0; i < count; ++i)
				_data[i] = new Point<T>(random(x1, x2), random(y1, y2));
			_size = count;
		}
		BrokenLine(BrokenLine<T>& other) {
			_data = new Point<T>*[other._size];
			for (int i = 0; i < other._size; ++i)
				_data[i] = new Point<T>(other[i]);
			_size = other._size;
		}
		~BrokenLine() {
			for (int i = 0; i < _size; ++i)
				delete _data[i];
			delete[] _data;
		}
		void push_back(Point<T>& point) { // Сложение ломаной и вершины
			Point<T>** copy = new Point<T>*[_size + 1];
			for (int i = 0; i < _size; ++i)
				copy[i] = new Point<T>(*_data[i]);
			copy[_size] = new Point<T>(point);
			for (int i = 0; i < _size; ++i)
				delete _data[i];
			delete[] _data;
			_data = copy;
			_size++;
		}
		void push_front(Point<T>& point) { // Слоение вершины и ломаной
			Point<T>** copy = new Point<T>*[_size + 1];
			for (int i = 1; i < _size + 1; ++i)
				copy[i] = new Point<T>(*_data[i - 1]);
			copy[0] = new Point<T>(point);
			for (int i = 0; i < _size; ++i)
				delete _data[i];
			delete[] _data;
			_data = copy;
			_size++;
		}

		float full_len() { // Вычисление длины
			float cur_len = 0;
			for (int i = 1; i < _size; ++i) {
				cur_len += len((*_data[i]), (*_data[i - 1]));
			}
			return cur_len;
		}
		void swap(BrokenLine<T>& rhs)noexcept {
			std::swap(_size, rhs._size);
			std::swap(_data, rhs._data);
		}
		Point<T>& operator[](size_t index) { //Оператор для чтения/записи по индексу
			if (index >= _size)
				throw ("index is out of range");
			return *_data[index];
		}
		BrokenLine<T> operator+(BrokenLine<T>& rhs) { // Сложение двух ломаных
			BrokenLine<T> new_line(*_data[0]);
			for (int i = 1; i < _size; ++i)
				new_line.push_back(*_data[i]);
			for (int i = 0; i < rhs._size; ++i)
				new_line.push_back(*rhs._data[i]);
			return new_line;
		}
		BrokenLine& operator=(BrokenLine<T>& other) {
			BrokenLine copy(other);
			swap(copy);
			return *this;
		}
		bool operator==(BrokenLine<T>& other) {
			if (_size != other._size)
				return false;
			for (int i = 0; i < _size; ++i) {
				if (!((*_data[i]) == other[i]))
					return false;
			}
			return true;
		}
		int size() {
			return _size;
		}
	};
	template<typename T>
	ostream& operator<<(ostream& stream, BrokenLine<T>& line) {
		for (int i = 0; i < line.size(); ++i) {
			cout << line[i] << endl;
		}
		return stream;
	}
	template<typename T>
	BrokenLine<T>& operator+(Point<T>& point, BrokenLine<T>& line) {
		line.push_front(point);
		return line;
	}
	template<typename T>
	BrokenLine<T>& operator+=(BrokenLine<T>& line, Point<T>& point) {
		line.push_back(point);
		return line;
	}
	void draw_trapezoid() {
		double a, b, c, d, h;

		fstream file;
		file.open("C:\\Users\\Aspire 7\\Desktop\\Broken_Line_SDL2\\data_for_BL.txt");
		if (file) {

			cout << "Input x1 coordinates >>>" << endl;
			cin >> a;
			cout << "Input y1 coordinates >>>" << endl;
			cin >> b;
			cout << "Input x2 coordinates >>>" << endl;
			cin >> c;
			cout << "Input y2 coordinates >>>" << endl;
			cin >> d;
			Point x(a, b);
			Point y(c, d);
			cout << "Input h >>>" << endl;
			cin >> h;
			BrokenLine line(x);
			line.push_back(y);

			if (b != d) {
				double x1 = 0.0;
				double x2 = 0.0;
				double y1 = 0.0;
				double y2 = 0.0;

				double k1 = (line[1].y - line[0].y) / (line[1].x - line[0].x);
				double k2 = (-1) / ((line[1].y - line[0].y) / (line[1].x - line[0].x));

				for (double i = abs(line[1].x) - h; i <= abs(line[1].x) + h; i += 0.1)
					for (double j = abs(line[1].y) - h; j <= abs(line[1].y) + h; j += 0.1) {
						Point<double> test_point(i, j);
						if ((j = k2 * (i - line[1].x) + line[1].y) && (h - 0.1 <= round(len(test_point, line[1]) * 100) <= h + 0.1)) {
							x1 = i;
							y1 = j;
							break;
						}
					}
				Point f(x1, y1);
				line.push_back(f);
				double range = len(line[0], line[1]) / 2;
				for (double i = abs(line[2].x) + h; i >= abs(line[2].x) - h; i -= 0.1)
					for (double j = abs(line[2].y) + h; j >= abs(line[2].y) - h; j -= 0.1) {
						Point test_point(i, j);
						if ((j = k1 * (i - line[2].x) + line[2].y) && (range - 1.0 <= round(len(test_point, line[2]) * 100) <= range + 1.0)) {
							x2 = i;
							y2 = j;
							break;
						}
					}
				Point zx(x2, y2);
				line.push_back(zx);
			}
			else
			{
				Point p3(line[1].x, line[1].y + h);
				line.push_back(p3);
				Point p4(line[2].x + (line[0].x - line[1].x) / 2, line[2].y);
				line.push_back(p4);
			}

			cout << line;

			for (int i = 0; i < 4; ++i)
				file << line[i].x << " " << line[i].y << " ";
		}
		else
			cout << "no file open" << endl;
		file.close();
	}
};