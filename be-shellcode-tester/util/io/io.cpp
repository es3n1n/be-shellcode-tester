#include "io.hpp"


namespace util::io {
	handle_t create_file( const char* path ) {
		return CreateFileA( path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	handle_t create_file( const wchar_t* path ) {
		return CreateFileW( path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	handle_t open_file( const char* path ) {
		return CreateFileA( path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	handle_t open_file( const wchar_t* path ) {
		return CreateFileW( path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	size_t get_file_size( handle_t handle ) {
		LARGE_INTEGER i = {};
		if ( GetFileSizeEx( handle, &i ) )
			return i.QuadPart;

		return 0;
	}

	bool read_file( handle_t handle, uint8_t* buffer, size_t size ) {
		const auto file_size = get_file_size( handle );

		DWORD bytes_read = 0;
		return ReadFile( handle, buffer, size, &bytes_read, NULL );
	}

	bool write_file( handle_t handle, uint8_t* buffer, size_t size ) {
		return WriteFile( handle, buffer, size, NULL, NULL );
	}

	void close_file( handle_t handle ) {
		CloseHandle( handle );
	}
}