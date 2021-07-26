#pragma once

template <typename CT, CT first, CT ... last> 
constexpr CT Polynomial (CT item) {
	if constexpr (sizeof...(last) != 0) { return first + item * Polynomial<CT, last...>(item); }
	return first;
};

