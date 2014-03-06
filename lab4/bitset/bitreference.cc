#include "bitreference.h"
#include "bitset.h"

BitReference& BitReference::operator=(bool b) {
	return *this;
}

BitReference& BitReference::operator=(const BitReference& rhs) {
	return *this;
}

BitReference::operator bool() const {
	return true;
}
