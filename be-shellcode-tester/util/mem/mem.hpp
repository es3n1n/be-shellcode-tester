#pragma once
#include <cstdint>
#include <string>
#include <vector>


namespace util::mem {
	uintptr_t sig( uint8_t* buffer, size_t size, std::string_view pattern ); // @note: es3n1n: it returns RVA
}