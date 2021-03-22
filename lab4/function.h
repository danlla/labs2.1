#pragma once
#include <iostream>
#include <cmath>
#include <memory>

class my_function
{
protected:
	virtual void print(std::ostream& s) const = 0;
public:
	virtual bool equals(const my_function& f) const = 0;
	virtual double value(double point) const = 0;
	virtual std::unique_ptr<my_function> derivative() const = 0;
	friend void operator<<(std::ostream& s, const my_function& fun);
	virtual ~my_function() = default;
};

class constant : public my_function //c
{
	double c;
protected:
	void print(std::ostream& s) const;
public:
	constant(double c);
	bool equals(const my_function& f) const;
	double value(double point) const;
	std::unique_ptr<my_function> derivative() const;
};

class linear : public my_function //ax+b
{
	double a;
	double b;
protected:
	void print(std::ostream& s) const;
public:
	linear(double a, double b);
	bool equals(const my_function& f) const;
	double value(double point) const;
	std::unique_ptr<my_function> derivative() const;
	double get_a() const
	{
		return a;
	}
};


class quadratic : public my_function //ax^2+bx+c
{
	double a;
	double b;
	double c;
protected:
	void print(std::ostream& s) const;
public:
	quadratic(double a, double b, double c);
	bool equals(const my_function& f) const;
	double value(double point) const;
	std::unique_ptr<my_function> derivative() const;
};

class sinus : public my_function // a|(-)|( )sin(ax+b)
{
	double a;
	linear arg;
protected:
	void print(std::ostream& s) const;
public:
	sinus(double a ,linear arg);
	sinus(double a, double arg_a, double arg_b);
	sinus(double arg_a, double arg_b);
	bool equals(const my_function& f) const;
	double value(double point) const;
	std::unique_ptr<my_function> derivative() const;
};

class cosine : public my_function // a|(-)|( )cos(ax+b)
{
	double a;
	linear arg;
protected:
	void print(std::ostream& s) const;
public:
	cosine(double a, linear arg);
	cosine(double a, double arg_a, double arg_b);
	cosine(double arg_a, double arg_b);
	bool equals(const my_function& f) const;
	double value(double point) const;
	std::unique_ptr<my_function> derivative() const;
};