#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <unordered_map>


namespace util {
	class c_pe {
	public: // ctors/etc
		c_pe( ) = default;
		~c_pe( ) = default;
		c_pe( uint8_t* base ) : m_base( base ) {
			m_dos_headers = reinterpret_cast< IMAGE_DOS_HEADER* >( m_base );
			m_nt_headers = reinterpret_cast< IMAGE_NT_HEADERS* >( m_base + m_dos_headers->e_lfanew );
		}
	public: // getters
		__forceinline uintptr_t get_image_base( ) { return m_nt_headers->OptionalHeader.ImageBase; }
		__forceinline size_t get_image_size( ) { return m_nt_headers->OptionalHeader.SizeOfImage; }
		__forceinline size_t get_headers_size( ) { return m_nt_headers->OptionalHeader.SizeOfHeaders; }
		__forceinline IMAGE_DATA_DIRECTORY get_dir( size_t i ) { return m_nt_headers->OptionalHeader.DataDirectory[ i ]; }
	public: // imports stuff
		struct import_data_t {
			std::string name;
			uintptr_t function_rva;
			uintptr_t ordinal = 0;
		};
		using import_list = std::unordered_map<std::string, std::vector<import_data_t>>;
	public: // imports stuff
		import_list get_imports( );
	private: // fields
		uint8_t* m_base;
		IMAGE_DOS_HEADER* m_dos_headers;
		IMAGE_NT_HEADERS* m_nt_headers;
	};
}