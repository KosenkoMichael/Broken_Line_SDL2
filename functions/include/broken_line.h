#pragma once

#include <iostream>
#include <stdlib.h>
#include <random>
#include <conio.h>
#include <cmath>
#include<windows.h>
#include<fstream>

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
		Point():x(0),y(0){}
		Point(T _x, T _y) :x(_x), y(_y) {}
		Point(const Point<T>& rhs) :x(rhs.x), y(rhs.y) {}
		float len(Point& rhs) {
			return static_cast<float>(sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y)));
		}
		bool operator == (Point<T> rhs) {
			if ((x == rhs.x) && (y == rhs.y))
				return true;
			return false;
		}
		void operator = (Point<T> rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		void print() {
			cout << x << " " << y << endl;
		}
	};
	template<typename T>
	ostream& operator<<(ostream& potok, Point<T>& point) {
		cout << point.x << " " << point.y;
		return potok;
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
					_data[i] = new Point<T>(random(x1,x2), random(y1,y2));
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
			for (int i = 1; i < _size+1; ++i)
				copy[i] = new Point<T>(*_data[i-1]);
			copy[0] = new Point<T>(point);
			for (int i = 0; i < _size; ++i)
				delete _data[i];
			delete[] _data;
			_data = copy;
			_size++;
		}
		float len() { // Вычисление длины
			float len = 0;
			for (int i = 1; i < _size; ++i) {
				len += (*_data[i]).len(*_data[i - 1]);
			}
			return len;
		}
		void swap(BrokenLine<T>& rhs)noexcept {
			std::swap(_size, rhs._size);
			std::swap(_data, rhs._data);
		}
		Point<T>& operator[](size_t index) { //Оператор для чтения/записи по индексу
			return *_data[index];
		}
		BrokenLine<T> operator+(BrokenLine<T>& rhs) { // Сложение двух ломаных
			BrokenLine<T> new_line(*_data[0]);
			for (int i = 1; i <_size; ++i)
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
		int size() {
			return _size;
		}
		void print() {
			for (int i = 0; i < _size; ++i)
				(*_data[i]).print();
		}
	};
	template<typename T>
	ostream& operator<<(ostream& potok, BrokenLine<T>& line) {
		for (int i = 0; i < line.size(); ++i) {
			cout << line[i] << endl;
		}
		return potok;
	}
	void draw_trapezoid() {
		double a, b, c, d, h;

		fstream file;
		file.open("C:\\Users\\79379\\Desktop\\Right_BL\\data_for_BL.txt");
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
			Point f(y.x, y.y + h);
			line.push_back(f);
			Point e(random(-f.x, f.x), f.y);
			line.push_back(e);
			cout << line << endl;

			for (int i = 0; i < line.size(); ++i)
				file << line[i].x << " " << line[i].y << " ";
		}
		else
			cout << "no file open" << endl;
	}
};