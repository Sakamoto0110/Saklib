#pragma once
#include <ostream>
typedef struct RGBACOLOR_t {

	short red;
	short green;
	short blue;
	short alpha;

	RGBACOLOR_t() :red(0), green(0), blue(0), alpha(0) {}

	RGBACOLOR_t(const short value) :red(value), green(value), blue(value), alpha(value) {}

	RGBACOLOR_t(const short _red, const short _green, const short _blue) :red(_red), green(_green), blue(_blue), alpha(255) {}
	RGBACOLOR_t(const short _red, const short _green, const short _blue, const short _alpha) :red(_red), green(_green), blue(_blue), alpha(_alpha) {}

	bool operator==(const RGBACOLOR_t& other) const
	{
		return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha;
	}
	bool operator!=(const RGBACOLOR_t& other) const
	{
		return !((*this) == other);
	}

	friend std::ostream& operator<<(std::ostream& cout, const RGBACOLOR_t&);

}RGBAColor, RGBA;

inline std::ostream& operator<<(std::ostream& cout, const RGBACOLOR_t& c)
{
	return cout << "{" << c.red << "," << c.green << "," << c.blue << "," << c.alpha << "}";
}