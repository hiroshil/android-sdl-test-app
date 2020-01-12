#ifndef FLAMESTEELCORESHAREDNOTNULLPOINTER_H_
#define FLAMESTEELCORESHAREDNOTNULLPOINTER_H_

#include <memory>
#include "Utils.h"

using namespace std;
using namespace FlameSteelCore::Utils;

namespace FlameSteelCore {
namespace Utils {

template <typename T>
class SharedNotNullPointer {

public:
	SharedNotNullPointer() {
	}

	SharedNotNullPointer(shared_ptr<T> rawSharedPointer) {
		if (rawSharedPointer.get() == nullptr) {
			throwRuntimeException("Excepted not null, but got null shared_ptr at SharedNotNullPointer constructor");
		}
		this->rawSharedPointer = rawSharedPointer;
	};

	shared_ptr<T> sharedPointer() {
		return rawSharedPointer;
	}

	T* operator->() const {
		return get();
	}

    T* get() const {
	if (rawSharedPointer.get() == nullptr) {
		throwRuntimeException("Excepted not null, but got null shared_ptr at SharedNotNullPointer getter");
	}
        return rawSharedPointer.get();
    }

private:
	shared_ptr<T> rawSharedPointer;

};

template <typename T, typename... Args>
SharedNotNullPointer<T> 
MakeSharedNotNullPointer(Args&&... args) {
	auto rawSharedPointer = make_shared<T>(forward<Args>(args)...);
	auto sharedNotNullPointer = SharedNotNullPointer<T>(rawSharedPointer);
	return sharedNotNullPointer;
};


namespace Shortcuts {

template <typename T>
using NotNull = SharedNotNullPointer<T>;

template <typename T, typename... Args>
SharedNotNullPointer<T>
make(Args&&... args) {
	return MakeSharedNotNullPointer<T>(forward<Args>(args)...);
};

template <typename T, typename... Args>
SharedNotNullPointer<T>
toNotNull(shared_ptr<T> rawSharedPointer) {
	return SharedNotNullPointer<T>(rawSharedPointer);
};

};

};
};




#endif
