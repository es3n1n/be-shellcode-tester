#pragma once
#include <Windows.h>
#include <cstdint>
#include <filesystem>


namespace util::io {
	using handle_t = HANDLE;

	handle_t create_file( const char* path );
	handle_t create_file( const wchar_t* path );
	handle_t open_file( const char* path );
	handle_t open_file( const wchar_t* path );
	size_t get_file_size( handle_t handle );
	bool read_file( handle_t handle, uint8_t* buffer, size_t size );
	bool write_file( handle_t handle, uint8_t* buffer, size_t size );
	void close_file( handle_t handle );

	struct reader_t {
	private:
		const uint8_t* m_buffer;
		const uint8_t* m_start_buffer;
		size_t m_size; // @note: es3n1n: isn't const cz we'll change it skip function obv
		const size_t m_start_size;
	public: // ctor/etc
		reader_t( ) = default;
		~reader_t( ) = default;
		reader_t( const uint8_t* buffer, size_t size ) : m_buffer( buffer ), m_size( size ), m_start_size( size ), m_start_buffer( buffer ) { }
	public: // getters
		__forceinline const uint8_t* get_buffer( ) { return m_buffer; }
		__forceinline size_t get_size( ) { return m_size; }
		__forceinline size_t get_start_size( ) { return m_start_size; }
		__forceinline const uint8_t* get_start_buffer( ) { return m_start_buffer; }
	public: // r/w funcs
		template <typename t>
		__forceinline t read( ) {
			t ret = *( t* )m_buffer;
			skip( sizeof( t ) );
			return ret;
		}
		template <typename t>
		__forceinline void read_to( t* buf, size_t size ) {
			memcpy( buf, m_buffer, size );
			skip( size );
		}
		__forceinline void skip( size_t size ) {
			m_buffer += size;
			m_size -= size;
		}
	};
}