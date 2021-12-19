#include "util.hpp"


namespace util {
	void hexdump( const char* prefix, const void* ptr, int buflen ) {
		unsigned char* buf = ( unsigned char* )ptr;
		int i, j;
		for ( i = 0; i < buflen; i += 16 ) {
			printf( "%s%06x: ", prefix, i );
			for ( j = 0; j < 16; j++ )
				if ( i + j < buflen )
					printf( "%02x ", buf[ i + j ] );
				else
					printf( "   " );
			printf( " " );
			for ( j = 0; j < 16; j++ )
				if ( i + j < buflen )
					printf( "%c", isprint( buf[ i + j ] ) ? buf[ i + j ] : '.' );
			printf( "\n" );
		}
	}
}
