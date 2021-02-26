#include <funnan/string/ToString.h>

std::string funnan::string::ToString(float x, int precision, std::chars_format fmt)
{
	std::string buffer;
	buffer.resize(32);

	const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x, fmt, precision);

	if(ec == std::errc())
	{
		buffer.resize(p - buffer.data());
	}

	return buffer;
}

std::string funnan::string::ToString(double x, int precision, std::chars_format fmt)
{
	std::string buffer;
	buffer.resize(32);

	const auto [p, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), x, fmt, precision);

	if(ec == std::errc())
	{
		buffer.resize(p - buffer.data());
	}

	return buffer;
}
