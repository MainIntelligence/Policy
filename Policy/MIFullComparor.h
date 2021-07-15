#pragma once
namespace MI {
//Defines weak comparison operators in terms of strong comparison operators.
//	(ie. the type T given to the template parameter must define the operators "==", ">", and "<",
//	     and afterwards (by inheriting from FullComparor<T>) will get the operators "!=", "<=", and ">=" for free).
// Note: This allows for the definition of weak comparisons between T and ANY type for which the strong (& opposite) comparison is defined.
//	    Defining == gives you !=, < gives you >=, and > gives you <=.
//	    its easy to remember ==, <, and > as STRONG comparisons, since of the 6, these are the 3 with the smallest subset of elements
//	    for which the comparison is true. (for an object in a typical system, == is true between it and one object in the system (itself),
//		 < is (on average) true for just less than half, etc. while for the others (!=, >=, <=), truth is (on average) much more likely.
template<typename T>
struct FullComparor
{
	//FullComparor() = default;
	template<typename OTy>
	inline bool operator!=(const OTy& other) const {
		return !(static_cast<const T&>(*this) == other);
	}
	
	template<typename OTy>
	inline bool operator>=(const OTy& other) const {
		return !(static_cast<const T&>(*this) < other);
	};
	
	template<typename OTy>
	inline bool operator<=(const OTy& other) const {
		return !(static_cast<const T&>(*this) > other);
	}
private:
	FullComparor() = default;
	friend T;
};

}
