
#include <SAELib_Functor.h>

int foo(int _a, int _b)
{
	return _a + _b;
};

struct Bar
{
	int foobar(int _a, int _b)
	{
		return _a + _b;
	};
};

int main()
{
	sae::functor<int(int, int)> _f{};

	if (_f.good_pointer() || _f)
		return -1;

	_f = &foo;

	if (!_f.good_pointer() || !_f)
		return -1;

	if (_f.invoke(2, 2) != _f(2, 2))
		return -1;

	Bar _b{};

	_f = std::pair{ &Bar::foobar, &_b };

	if (!_f.good_pointer() || !_f)
		return -1;

	if (_f.invoke(2, 2) != _f(2, 2))
		return -1;

	// test copy constructor

	const auto _fconstcopy = _f;
	sae::functor<int(int, int)> _fcopy{ _fconstcopy };

	if (!_fcopy.good_pointer())
		return -1;

	if (_fcopy.invoke(2, 2) != _f.invoke(2, 2))
		return -1;

	
	// test move constructor

	sae::functor<int(int, int)> _fmoved{ std::move(_fcopy) };

	if (_fcopy.good_pointer())
		return -1;

	if (!_fmoved.good_pointer())
		return -1;

	if (_fmoved.invoke(2, 2) != _f.invoke(2, 2))
		return -1;

	return 0;
};
