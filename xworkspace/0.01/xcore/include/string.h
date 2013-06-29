/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_STRING_H
#define XWORKSPACE_STRING_H

extern u32 cslen( const tchar *cs );
extern i8 cscmp( const tchar *cs0, const tchar *cs1 );
extern i8 csncmp( const tchar *cs0, const tchar *cs1, u32 n );
extern tchar *cscpy( tchar *to, const tchar *from );
extern tchar *csncpy( tchar *to, const tchar *from, u32 n );
extern tchar *cscat( tchar *to, const tchar *from );
extern tchar *csncat( tchar *to, const tchar *from, u32 n );
extern tchar *cschr( const tchar *cs, tchar c );
extern tchar *csrchr( const tchar *cs, tchar c );
extern tchar *cspbrk( const tchar *cs, const tchar *chrset );
extern tchar *csstr( const tchar *cs, const tchar *subcs );
extern tchar *utocshex( u32 value );

#endif
