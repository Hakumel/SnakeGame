#pragma once
#ifndef POINT_H
#define POINT_H
struct Point
{
	Point(int x, int y, Point* p = nullptr) :m_x(x), m_y(y), next(p) {}
	int m_x;
	int m_y;
	Point* next;
};
#endif // !POINT_H