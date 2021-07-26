#pragma once

template <typename T>
struct BitGroup {
	static constexpr T bbit0 = 1 << (8 * sizeof(T) - 1);
	static constexpr T lbit0 = 1;
	T bits;
	BitGroup(T bitgroup = T{}) : bits{bitgroup} {};
	operator T& () { return bits; }
	
	BitGroup Compliment() const { return ~bits; }
	
	BitGroup Shared(const T other) const { return bits & other; }
	BitGroup& Restrict(const T other) const { bits &= other; return *this; }
	
	BitGroup Combined(const T other) const { return bits | other; }
	BitGroup& Combine(const T other) const { bits |= other; return *this; }
	
	//NAND gate
	BitGroup GetB0Indicator(const T other) const { return ~(bits & other); } //NAND
	BitGroup GetB1Indicator(const T other) const { return ~(bits | other); } //NOR
	BitGroup GetDiffIndicator(const T other) const { return bits ^ other; } //EXOR
	BitGroup GetSameIndicator(const T other) const { return ~(bits ^ other); } //EXNOR
	template <unsigned int total>
	static constexpr BitGroup<T> Big();
	template <unsigned int total>
	static constexpr BitGroup<T> Little();
	
	template <unsigned int bId>
	BitGroup BitsAtleast();
	template <unsigned int bId>
	BitGroup BitsUnder();
	
	template <unsigned int bId>
	BitGroup Rebased();
	static T Bitify(unsigned int id) { return 1 << id; }
	
	//unsigned int HighestDiffBit(const T other);
};
template <typename T> template <unsigned int total>
constexpr BitGroup<T> BitGroup<T>::Big() {
	if constexpr (total != 1) { return (bbit0 >> ( total - 1 )) | Big<total - 1>(); }//bbit0; }
	return bbit0;
}

template <typename T> template <unsigned int total>
constexpr BitGroup<T> BitGroup<T>::Little() {
	if constexpr (total != 1) { return (lbit0 << ( total - 1 )) | Little<total - 1>(); }//lbit0; }
	return lbit0;
}


template <typename T> template <unsigned int bId>
BitGroup<T> BitGroup<T>::BitsAtleast() {
	return ~Little<bId>() & bits; 
}

template <typename T> template <unsigned int bId>
BitGroup<T> BitGroup<T>::BitsUnder() {
	return Little<bId - 1>() & bits;
}

template <typename T> template <unsigned int bId>
BitGroup<T> BitGroup<T>::Rebased() {
	return BitsAtleast<bId>() / Bitify(bId - 1);
}

