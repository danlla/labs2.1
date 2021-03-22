#include "function.h"

void operator<<(std::ostream & s, const my_function & fun)
{
	fun.print(s);
}

void constant::print(std::ostream & s) const
{
	s << c;
}

constant::constant(double c) : c(c) {}

bool constant::equals(const my_function & f) const
{
	if (typeid(*this) != typeid(f))
		return false;
	auto ref = dynamic_cast<const constant&>(f);
	return c == ref.c;
}

double constant::value(double point) const
{
	return c;
}

std::unique_ptr<my_function> constant::derivative() const
{
	std::unique_ptr<constant> res(new constant(0));
	return res;
}

void linear::print(std::ostream & s) const
{
	if (a)
	{
		if(a==1)
			s << 'x';
		if (a == -1)
			s << '-' << 'x';
		if (a != 1 && a != -1)
			s << a << 'x';
		if (b)
			s << '+' << b;
	}
	else
		s << b;
}

linear::linear(double a, double b) :a(a), b(b) {}

bool linear::equals(const my_function & f) const
{
	if (typeid(*this) != typeid(f))
		return false;
	auto ref = dynamic_cast<const linear&>(f);
	return a == ref.a&&b == ref.b;
}

double linear::value(double point) const
{
	return a * point + b;
}

std::unique_ptr<my_function> linear::derivative() const
{
	std::unique_ptr<constant> res(new constant(a));
	return res;
}

void quadratic::print(std::ostream & s) const
{
	//s << a << "x^2+" << b << "x+" << c;
	if (a) 
	{
		if (a == 1)
			s << "x^2";
		if (a == -1)
			s << '-' << "x^2"; 
		if (a != 1 && a != -1)
			s << a << "x^2";
		if (b)
		{
			if(b==1)
				s << "+x";
			if (b == -1)
				s << "-x";
			if (b != 1 && b != -1)
				s << '+' << b << 'x';
		}
		if (c)
			s << '+' << c;
	}
	else
	{
		if (b)
		{
			if (b == 1)
				s << 'x';
			if (b == -1)
				s << '-' << 'x';
			if (b != 1 && b != -1)
				s << b << 'x';
			if (c)
				s << '+' << c;
		}
		else
			s << c;
	}
}

quadratic::quadratic(double a, double b, double c) : a(a), b(b), c(c) {}

bool quadratic::equals(const my_function & f) const
{
	if (typeid(*this) != typeid(f))
		return false;
	auto ref = dynamic_cast<const quadratic&>(f);
	return a == ref.a&&b == ref.b&&c == ref.c;
}

double quadratic::value(double point) const
{
	return a * point*point + b * point + c;
}

std::unique_ptr<my_function> quadratic::derivative() const
{
	std::unique_ptr<linear> res(new linear(2 * a, b));
	return res;
}

void sinus::print(std::ostream & s) const
{
	if (a == 1)
	{
		s << "sin(";
		s << arg;
		s << ')';
	}
	else if (a == -1)
	{
		s << "-sin(";
		s << arg;
		s << ')';
	}
	else
	{
		s << a << "sin(";
		s << arg;
		s << ')';
	}
}

sinus::sinus(double a, linear arg):a(a), arg(arg){}

sinus::sinus(double a, double arg_a, double arg_b): a(a), arg(arg_a,arg_b){}

sinus::sinus(double arg_a, double arg_b):a(1), arg(arg_a, arg_b){}

bool sinus::equals(const my_function & f) const
{
	if (typeid(*this) != typeid(f))
		return false;
	auto ref = dynamic_cast<const sinus&>(f);
	return a == ref.a && arg.equals(ref.arg);
}

double sinus::value(double point) const
{
	return a*sin(arg.value(point));
}

std::unique_ptr<my_function> sinus::derivative() const
{
	std::unique_ptr<cosine> res(new cosine(a*arg.get_a(), arg));
	return res;
}

void cosine::print(std::ostream & s) const
{
	if (a == 1)
	{
		s << "cos(";
		s << arg;
		s << ')';
	}
	else if (a == -1)
	{
		s << "-cos(";
		s << arg;
		s << ')';
	}
	else
	{
		s << a << "cos(";
		s << arg;
		s << ')';
	}
}

cosine::cosine(double a, linear arg): a(a), arg(arg) {}

cosine::cosine(double a, double arg_a, double arg_b): a(a), arg(arg_a, arg_b) {}

cosine::cosine(double arg_a, double arg_b): a(1), arg(arg_a, arg_b) {}

bool cosine::equals(const my_function & f) const
{
	if (typeid(*this) != typeid(f))
		return false;
	auto ref = dynamic_cast<const cosine&>(f);
	return a == ref.a && arg.equals(ref.arg);
}

double cosine::value(double point) const
{
	return a * cos(arg.value(point));
}

std::unique_ptr<my_function> cosine::derivative() const
{
	std::unique_ptr<sinus> res(new sinus(-a*arg.get_a(), arg));
	return res;
}
