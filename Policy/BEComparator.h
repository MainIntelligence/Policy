#pragma once
#include "MIFullComparor.h"

template <typename BELIST, typename VT>
struct BEComparator : public MI::FullComparor<BEComparator<BELIST, VT>> {
	bool operator==(const BELIST other) const;
	bool operator>(const BELIST other) const;
	bool operator<(const BELIST other) const;
private:
	BEComparator() = default;
	friend BELIST;
};

template <typename T>
inline bool Minimum(T obj1, T obj2) {
	return (obj1 < obj2) ? obj1 : obj2;
}

template <typename BELIST, typename VT>
bool BEComparator<BELIST, VT>::operator==(const BELIST other) const {
	VT * pv1 = static_cast<const BELIST&>(*this).data;
	VT * pv2 = other.data;

	const unsigned int l1 = static_cast<const BELIST&>(*this).len;
	const unsigned int l2 = other.len;
	if (l1 != l2) { return false; }
	int i = 0;
	for (; i < l1 && *pv1 == *pv2 ; i++, pv1++, pv2++) {
		continue;
	}
	return i == l1;
}

template <typename BELIST, typename VT>
bool BEComparator<BELIST, VT>::operator>(const BELIST other) const {
	VT * pv1 = static_cast<const BELIST&>(*this).data;
	VT * pv2 = other.data;

	const unsigned int l1 = static_cast<const BELIST&>(*this).len;
	const unsigned int l2 = other.len;
	if (l1 != l2) { return (l1 > l2) ? true : false; }
	int i = 0;
	for (; i < l1 && *pv1 == *pv2 ; i++, pv1++, pv2++) {
		continue;
	}
	return i != l1 && *pv1 > *pv2;
}

template <typename BELIST, typename VT>
bool BEComparator<BELIST, VT>::operator<(const BELIST other) const {
	VT * pv1 = static_cast<const BELIST&>(*this).data;
	VT * pv2 = other.data;

	const unsigned int l1 = static_cast<const BELIST&>(*this).len;
	const unsigned int l2 = other.len;
	if (l1 != l2) { return (l1 < l2) ? true : false; }
	int i = 0;
	for (; i < l1 && *pv1 == *pv2 ; i++, pv1++, pv2++) {
		continue;
	}
	return i != l1 && *pv1 < *pv2;
}
