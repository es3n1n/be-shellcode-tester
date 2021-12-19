#pragma once
#include <stdio.h>
#include <ctype.h>

#include "io/io.hpp"
#include "logger.hpp"
#include "pe/pe.hpp"


namespace util {
	void hexdump( const char* prefix, const void* ptr, size_t buflen );
	__forceinline bool str_ends_with( const char* str, const char* suffix ) {
		if ( !str || !suffix )
			return 0;
		size_t lenstr = strlen( str );
		size_t lensuffix = strlen( suffix );
		if ( lensuffix > lenstr )
			return 0;
		return !strncmp( str + lenstr - lensuffix, suffix, lensuffix );
	}
}
