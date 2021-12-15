#pragma once
#include "util/util.hpp"
#include "loader/loader.hpp"


namespace bootstrap {
	void run_file( const std::wstring& path, const std::wstring& name );
	void run_dir( const std::string& dir );
}