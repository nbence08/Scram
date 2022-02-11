#pragma once
#include <stdexcept>
#include <string>


extern int componentTypeCounter;
const static int MAX_COMPONENTS = 32;


template <typename T>
int getTypeId() {
	if (componentTypeCounter == 32) {
		throw std::logic_error("Maximum number of components cannot exceed "+ std::to_string(MAX_COMPONENTS));
	}
	static int componentId = componentTypeCounter++;
	return componentId;
}

class ComponentBase {

};