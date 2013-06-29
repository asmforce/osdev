#include <iostream>
#include <windows.h>
#include <elib/aliases.hpp>
using namespace elib::aliases;






namespace use
{
  char *appname;
  DWORD openmode;
  void usage();
  u64 filesize( const char *filename );
};





int main( int argc, char **argv )
{
  use::appname = argv[0];
  use::openmode = OPEN_EXISTING;

  if( argc == 1 )  {
    std::cerr << "use `--help` for more info\n";
    return -1;
  };

  if( !strcmp(argv[1],"--help") )  {
    use::usage();
  } else {
    u64 res = 0;
    for( int i = 1; i < argc; ++i )
      res += use::filesize( argv[i] );
    std::cout << res;
  };

  return 0;
};





void use::usage()  {
  std::cout << "etools::size: prints the total size of file set\n"
               "built: " __DATE__ "\n\n"
	       "usage: " << appname << " <filename> [... <filenameN>]\n";
};


u64 use::filesize( const char *filename )
{
  HANDLE file = CreateFile( filename, GENERIC_READ, 0, 0, openmode, 0, 0 );
  if( file == INVALID_HANDLE_VALUE )  {
    std::cerr << "warning: inaccessible file `" << filename << "`\n";
    return 0ULL;
  };

  union {
    u64 value;
    struct { u32 a,b; };
  } x;

  x.a = GetFileSize( file, &x.b );
  CloseHandle( file );
  return x.value;
};
