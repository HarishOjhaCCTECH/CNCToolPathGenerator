#pragma once

class Triangle
{
public:
	Triangle();
	Triangle(const int v1, const int v2, const int v3);
	~Triangle();

	int v1() const;
	int v2() const;
	int v3() const;

private:
	int mv1;
	int mv2;
	int mv3;
};