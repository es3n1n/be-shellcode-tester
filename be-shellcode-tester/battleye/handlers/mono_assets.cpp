#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void mono_assets( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		util::logger::info( "\tassets:" );

		while ( reader.get_size( ) > 1 ) {
			char buf[ 256 ];

			// @note: es3n1n:
			//**buffer_ptr = strlen;
			//for ( off = 0; off < **buffer_ptr; ++off )
			//	( *buffer_ptr )[ off + 1 ] = *( ( _BYTE* )file_name + 2 * off );// write file name to buffer
			auto len = reader.read<uint8_t>( );
			reader.read_to( buf, len );
			buf[ len ] = '\0';
			util::logger::info( "\tname: %s", buf );

			// @note: es3n1n: 
			// if ( getfileattributesexw(full_path, 0i64, v27) )
			//		*( _DWORD* )*buffer_ptr = v28;       // write attributes
			auto file_attributes = reader.read<uint32_t>( );
			util::logger::info( "\t\tfile_attributes: 0x%x", file_attributes );

			// @note: es3n1n:
			// *((_DWORD *)*buffer_ptr + 1) = 0;
			// memset( read_buf, 0, sizeof( read_buf ) );
			// while ( readfile( v26, read_buf, 256i64, &v25, 0i64 ) && v25 )
			//		*( ( _DWORD* )*buffer_ptr + 1 ) += read_buf[ 3 ] + read_buf[ 2 ] + read_buf[ 1 ] + read_buf[ 0 ];
			auto checksum = reader.read<uint32_t>( );
			util::logger::info( "\t\tchecksum: 0x%x", checksum );

			util::logger::info( "\t================================" );
		}
	}
}
