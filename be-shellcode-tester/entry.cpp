#include "bootstrap/bootstrap.hpp"


int main( int argc, char* argv[ ] ) {
	util::logger::info( "Starting..." );
	bootstrap::run_dir(
		argc >= 2 ? argv[ 1 ] : "C:\\Users\\usr\\Desktop\\be_explorer\\x64\\Debug\\shellcodes\\"
	);
	return EXIT_SUCCESS;
}