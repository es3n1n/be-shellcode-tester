#pragma once
#include "util/util.hpp"
#include "battleye/battleye.hpp"
#include "hooks/hooks.hpp"


namespace loader {
	bool load_shellcode( util::io::handle_t file_handle );
}
