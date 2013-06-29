#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
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

  setmode( fileno(stdout), O_BINARY );
  setmode( fileno(stdin), O_BINARY );

  const u32 cachesize = 4096UL;
  size_t read;
  u8 cache[cachesize];


  if( argc > 1 )
  {
    if( !strcmp(argv[1],"--help") )  {
      use::usage();
      return 0;
    };

    u64 preskip = 0ULL;
    u64 limit = ~0ULL;
    for( int i = 1; i < argc; ++i )  {
      if( !strcmp(argv[i],"-p") )  {
        if( ++i < argc )  {
          preskip = atoll( argv[i] );
        } else {
          use::usage();
          return -1;
        };
      } else if( !strcmp(argv[i],"-s") )  {
        if( ++i < argc )  {
          limit = atoll( argv[i] );
        } else {
          use::usage();
          return -1;
        };
      } else {
        use::usage();
        return -1;
      };
    };

    if( fseeko64(stdin,preskip,SEEK_SET) )
      std::cerr << "error: seeking failed\n";
    while( read = fread(&cache,1,cachesize,stdin) )  {
      if( limit < read )
        read = limit;
      fwrite( &cache, 1, read, stdout );
      if( read < cachesize )
        break;
      limit -= read;
    };
  } else {
    while( read = fread(&cache,1,cachesize,stdin) )  {
      fwrite( &cache, 1, read, stdout );
      if( read < cachesize )
        break;
    };
  };

  // just in case
  fflush( stdout );
  return 0;
};





void use::usage()  {
  std::cout << "etools::re: forwards from <stdin> to <stdout>\n"
               "built: " __DATE__ "\n\n"
               "usage: " << appname << " [options] [< <input-filename>] [> <output-filename>]\n"
               "options:\n"
               "\t[-p <size>]\n\t\tskip first <size> bytes\n"
               "\t[-s <size>]\n\t\tset limit to <size> bytes\n";
};
