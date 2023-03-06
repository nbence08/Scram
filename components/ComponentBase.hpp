#pragma once
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "components_export.hpp"

namespace SComponent {

	class COMPONENTS_EXPORT ComponentBase {};

	template <typename T>
	concept Component = requires (T t) { static_cast<ComponentBase>(t); };

}
