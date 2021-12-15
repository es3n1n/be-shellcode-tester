#include "battleye/reports.hpp"


namespace battleye::reports::handlers {
	void encrypted( battleye::enums::e_report_id id, util::io::reader_t& reader ) {
		// @note: user344: This decryption is really bad coded, but it works
		// and i dont want to spend any more time on it so shall it stay.
		auto v90 = ( uint8_t )reader.read<uint32_t>( );
		for ( auto i = reader.get_start_size( ) - 1; i >= 5; --i ) {
			auto v408 = i != 0 ? *( uint8_t* )( reader.get_start_buffer( ) + i - 1 ) : v90;
			*( uint8_t* )( reader.get_start_buffer( ) + i ) ^= v408;
		}

		// @note: user344: Since our decryption is not proper and we dont decrypt last byte
		// we cant do a proper "if (report_size == 0xFFFF) break;" check inside loop
		// thus im forced to do this ugly "while (bf.get_size() > 2)" check for now.
		// CHANGE WHEN DECRYPTION IS FIXED!!!
		int iteration = 0;
		while ( reader.get_size( ) > 4 ) {
			const auto report_size = reader.read<uint16_t>( );
			if ( ( iteration > 0 && report_size > reader.get_size( ) ) || !report_size ) // @note: es3n1n: otherwise it will fail cz of inproper decryption
				continue;

			battleye::reports::execute_handler( reader.get_buffer( ), report_size );

			reader.skip( report_size );
			iteration += 1;
		}

		// @note: user344: skip remaining bytes due to improper decryption
		reader.skip( reader.get_size( ) );
	}
}
