#pragma once
#include "resources/beclient_x64.hpp"
#include "enums.hpp"
#include "reports.hpp"
#include "typedefs.hpp"

#include <unordered_map>
#include <string>


namespace battleye { 
	inline std::unordered_map<std::string, unsigned char*> resources_list = {
		{ "BEClient_x64.dll", resources::beclient_x64 }
	};
}
