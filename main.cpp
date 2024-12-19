/************************************************************/
/*						  BMP2JASCPAL						*/
/*		Converts a common-format image file to a JASC		*/
/*		256-color palette.									*/
/*		The image HAS to be 16x16.							*/
/************************************************************/

#include <Windows.h>
#include <stdio.h>
#pragma comment( lib, "user32.lib" )

using namespace System;
using namespace System::Drawing;

// Helper func
String^ MakeString( char* str ) {
	char* chr = NULL;
	String^ converted_str;

	chr = str;
	for( INT i = 0; chr[i] != '\0'; i++ ) {
		converted_str += wchar_t(str[i]);
	}
	return converted_str;
}

BOOL WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR pCmdLine, INT ) {
	Bitmap^ pBmpFile;
	Color^ clr;
	FILE* pPalFile;
	char szInFname[256]; char szOutFname[256];

	memset( szInFname, 0, 256 ); memset( szOutFname, 0, 256 );
	sscanf( pCmdLine, "-in %s -out %s", &szInFname[0], &szOutFname[0] );

	pPalFile = fopen( szOutFname, "wb" );
	if( !pPalFile ) {
		MessageBoxA( NULL,
			"Error:\n\tThe specified output file could not be created/opened for writing",
			"Error",
			MB_ICONERROR );
		exit( -1 );
	}

	if( !IO::File::Exists(MakeString(szInFname)) ) {
		MessageBoxA( NULL,
			"Error:\n\tThe specified input file could not be found",
			"Error",
			MB_ICONERROR );
		exit( -1 );
	}
	pBmpFile = (Bitmap^)Bitmap::FromFile( MakeString(szInFname) );
	fputs( "JASC-PAL\r\n0100\r\n256\r\n", pPalFile ); // header

	for( INT y = 0; y < pBmpFile->Height; y++ ) {
		for( INT x = 0; x < pBmpFile->Width; x++ ) {
			clr = pBmpFile->GetPixel( x, y );
			fprintf( pPalFile, "%i %i %i\r\n", clr->R, clr->G, clr->B );
		}
	}

	fclose( pPalFile );

	return TRUE;
}