#include "util/mem/mem.hpp"


namespace {
	std::vector<int> pattern_to_byte( std::string_view pattern ) {
		auto bytes = std::vector<int> {};
		auto start = const_cast< char* >( pattern.data( ) );
		auto len = pattern.length( );
		auto end = const_cast< char* >( start ) + len;
		bytes.reserve( len / 3 + 5 );

		for ( auto current = start; current < end; ++current ) {
			if ( *current == '?' ) {
				++current;

				if ( *current == '?' )
					++current;

				bytes.emplace_back( -1 );
			} else
				bytes.emplace_back( strtoul( current, &current, 16 ) );
		}
		return bytes;
	}
}

namespace util::mem {
	uintptr_t sig( uint8_t* buffer, size_t size, std::string_view pattern ) {
		const auto pattern_bytes = pattern_to_byte( pattern.data( ) );

		const std::size_t pattern_size = pattern_bytes.size( );
		const int* pattern_data = pattern_bytes.data( );

		for ( std::uint32_t i = 0ul; i < size - pattern_size; ++i ) {
			bool found = true;

			for ( std::uint32_t j = 0ul; j < pattern_size; ++j ) {
				if ( buffer[ i + j ] == pattern_data[ j ] || pattern_data[ j ] == -1 )
					continue;

				found = false;
				break;
			}

			if ( !found )
				continue;

			return i;
		}

		return 0;
	}
}
