#pragma once
#include <stdexcept>
#include <string>


namespace SComponent {	
	extern int componentTypeCounter;
	const static int MAX_COMPONENTS = 32;


	template <typename T>
	int getTypeId() {
		if (componentTypeCounter == MAX_COMPONENTS) {
			throw std::logic_error("Maximum number of components cannot exceed " + std::to_string(MAX_COMPONENTS));
		}
		static int componentId = componentTypeCounter++;
		return componentId;
	}

	class ComponentBase {

	};
}
