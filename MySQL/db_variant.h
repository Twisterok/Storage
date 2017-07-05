#pragma once

#include <boost/variant.hpp>
#include <boost/none_t.hpp>
#include <vector>

typedef std::vector<uint8_t>	blob_t;
typedef boost::none_t			null_t;

typedef boost::variant<
	null_t,
	int16_t,
	int32_t,
	int64_t,
	float,
	double,
	std::string,
	blob_t
> db_variant;
