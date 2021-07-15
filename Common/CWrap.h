#pragma once
#include <Policy/MIFullComparor.h>

namespace MI {

struct CWrap : public FullComparor<CWrap> {
	char * str;
	
	CWrap(char * strv) : str{strv} {}
	void operator=(char * strv) { str = strv; }
	
	//Basic Pointer manipulation functionality
	char operator*() { return *str; }
	char* operator++(int) { return str++; }
	char* operator++() { return ++str; }
	char* operator--(int) { return str--; }
	char* operator--() { return --str; }
	
	//Functionality for pointer differences.
	int operator-(const char * other) const;
	
	//Comparison by value functionality (instead of pointer comparisons)
	bool operator==(const char * other) const;
	bool operator<(const char * other) const;
	bool operator>(const char * other) const;
	
	bool operator==(const CWrap&) const;
	bool operator<(const CWrap&) const;
	bool operator>(const CWrap&) const;
	
	explicit operator char*() const { return str; }
private:
	const char * ShiftToFirstCharDiff(const char *& other) const;
};

const char * CWrap::ShiftToFirstCharDiff(const char *& other) const {
	const char * pc = str;
	for (; *other == *pc && *pc != '\0' ; pc++, other++) {
		continue;
	}
	return pc;
}

bool CWrap::operator==(const char * other) const {
	const char * pc = ShiftToFirstCharDiff(other);
	return *pc == *other;
}

bool CWrap::operator<(const char * other) const {
	const char * pc = ShiftToFirstCharDiff(other);
	return *pc < *other;
}

bool CWrap::operator>(const char * other) const {
	const char * pc = ShiftToFirstCharDiff(other);
	return *pc > *other;
}


bool CWrap::operator==(const CWrap& other) const {
	return (*this) == static_cast<const char*>(other);
}

bool CWrap::operator<(const CWrap& other) const {
	return (*this) < static_cast<const char*>(other);
}

bool CWrap::operator>(const CWrap& other) const {
	return (*this) > static_cast<const char*>(other);
}

int CWrap::operator-(const char * other) const {
	return (int) (reinterpret_cast<long unsigned int>(str) - reinterpret_cast<long unsigned int>(other));
}

}
