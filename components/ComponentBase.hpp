#pragma once
#include <stdexcept>
#include <string>

static int componentTypeCounter = 0;
const static int MAX_COMPONENTS = 32;

template <typename T>
int getComponentTypeId() {
	if (componentTypeCounter == 32) {
		throw std::logic_error("Maximum number of components cannot exceed "+ std::to_string(MAX_COMPONENTS));
	}
	static int componentId = componentTypeCounter++;
	return componentId;
}

class ComponentBase {
public:
	virtual int getTypeId() = 0;
};