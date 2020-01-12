#include "Path.h"
#include <cctype>
#include <FlameSteelCore/FSCUtils.h>

using namespace FlameSteelCore::Utils;
using namespace FlameSteelCommonTraits;

inline bool isRDNS(string path) {
	for (unsigned i=0; i<path.length(); ++i)
	{
		auto character = path.at(i);
		if (isalpha(character) == false && character != '.') {
			return false;
		}
  	}
	return true;
};

Path::Path(string path) {
	if (isRDNS(path) == false) {
		string errorText = path;
		errorText += "is not in reverse-domain-format";
		throwRuntimeException(errorText);
	}
	this->path = path;
};