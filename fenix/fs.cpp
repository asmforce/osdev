typedef u32 node;

#define INVALID_INDEX 0



node open( const tchar *path );
void close( node i );

u32 read( node i, void *to, u32 bytes );
u32 write( node i, const void *from, u32 bytes );