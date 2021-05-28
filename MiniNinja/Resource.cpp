#include "Resource.h"

std::ostream& operator<<(std::ostream& os, const Resource& rhs) {
	return os << rhs.name;
}

std::istream& operator>>(std::istream& is, Resource& rhs) {
	return is >> rhs.name;
}

bool Resource::operator<(const Resource& rhs) {
	return type < rhs.type;
}