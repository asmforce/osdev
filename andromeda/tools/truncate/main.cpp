#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <elib/aliases.hpp>
using namespace elib::aliases;






namespace use
{
  char *appname;
  void usage();
};




int main( int argc, char **argv )
{
  use::appname = argv[0];

  if( argc == 1 )  {
    std::cerr << "use `--help` for more information\n";
    return -1;
  };

  if( !strcmp(argv[1],"--help") )  {
    use::usage();
    return 0;
  };

  // set size to zero by default
  LARGE_INTEGER size, newsize;
  newsize.QuadPart = 0LL;

  // deny by default
  bool incdeny = true;
  char *filename = (char*) 0;
  u32 opencreate = OPEN_EXISTING;

  for( u32 i = 1uL; i < argc; ++i )  {
    if( !strcmp(argv[i],"-s") )  {
      if( ++i == argc )  {
        use::usage();
        return -1;
      } else {
        newsize.QuadPart = atoll(argv[i]);
      };
    } else if( !strcmp(argv[i],"-i") )  {
      incdeny = false;
    } else if( !strcmp(argv[i],"-c") )  {
      opencreate = OPEN_ALWAYS;
    } else {
      if( filename )  {
        use::usage();
        return -1;
      } else {
        filename = argv[i];
      };
    };
  };

  if( !filename )  {
    std::cerr << "error: file is not specified\n";
    return -1;
  };


  HANDLE file = CreateFile( filename, GENERIC_WRITE, 0, 0, opencreate, 0, 0 );
  if( file == INVALID_HANDLE_VALUE )  {
    std::cerr << "error: inaccessible file `" << filename << "`\n";
    return -1;
  };

  size.LowPart = GetFileSize( file, (DWORD*) &size.HighPart );
  if( incdeny && newsize.QuadPart > size.QuadPart )
    return 0;

  DWORD factor = newsize.QuadPart < 0LL ? FILE_END : FILE_BEGIN;
  if( !SetFilePointerEx( file, newsize, 0, factor ) )  {
    std::cerr << "error: cannot set file pointer\n";
    return -1;
  };

  if( !SetEndOfFile(file) )  {
    std::cerr << "error: cannot set EOF\n";
    return -1;
  };

  return 0;
};





void use::usage()  {
  std::cout << "etools::truncate: truncation of files\n"
               "built: " __DATE__ "\n\n"
               "usage: " << appname << " [options] <filename>\n"
               "options:\n"
               "\t[-s <size>]\n\t\tset file size to <size> bytes\n"
               "\t[-c]\n\t\tcreate inexistent files\n"
               "\t[-i]\n\t\tallow increasing of size\n";
};
