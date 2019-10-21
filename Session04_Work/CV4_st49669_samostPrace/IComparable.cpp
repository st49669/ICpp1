

#include "stdafx.h"
#include "ICOmparable.h"


int IComparable::compareTo(IComparable* obj) const {
	string left = this->ToString();
	string right = obj->ToString();
	if (left < right) {
		return -1;
	}
	else if (left > right) {
		return 1;
	}
	return 0;
}

 string IComparable::ToString() const {
	 return nullptr;
}
