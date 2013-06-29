#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <windows.h>
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

  setmode( fileno(stdin), O_BINARY );

  if( argc == 1 )  {
    std::cerr << "use `--help` for more info\n";
    return 0;
  };

  if( !strcmp(argv[1],"--help") )  {
    use::usage();
  } else {
    FILE *outfile = fopen64( argv[1], "wb+" );

    const u32 cachesize = 4096UL;
    size_t read;
    u8 cache[cachesize];

    if( !outfile )  {
      std::cerr << "warning: inaccessible file `" << argv[1] << "`\n";
      return -1;
    };

    for( int i = 2; i < argc; ++i )
    {
      i64 offset;
      if( !strcmp(argv[i],"-mb") )  {
        fseek( outfile, 0, SEEK_SET );
      } else if( !strcmp(argv[i],"-me") )  {
        fseek( outfile, 0, SEEK_END );
      } else if( !strcmp(argv[i],"-ms") )  {
        if( ++i < argc )  {
          offset = atoll( argv[i] );
          if( fseeko64(outfile,offset,SEEK_CUR) )  {
            std::cerr << "error: seeking failed\n";
            return -1;
          };
        } else {
          use::usage();
          return -1;
        };
      } else if( !strcmp(argv[i],"-w") ) {
        while( read = fread(&cache,1,cachesize,stdin) )  {
          if( read < cachesize )  {
            fwrite( &cache, 1, read, outfile );
            break;
          };
          fwrite( &cache, 1, read, outfile );
        };
      } else {
        use::usage();
        return -1;
      };
    };
  };

  return 0;
};





void use::usage()  {
  std::cout << "etools::pcp: partial copy\n"
               "built: " __DATE__ "\n\n"
	       "usage: " << appname << " <output-filename> [commands]\n"
               "commands:\n"
               "\t[-w]\n\t\twrite in current position\n"
               "\t[-mb]\n\t\tmove to begin\n"
               "\t[-me]\n\t\tmove to end\n"
               "\t[-ms <offset>]\n\t\tmove to current+<offset>\n";
};
