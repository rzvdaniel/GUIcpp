#ifndef T_STRINGCI_H
#define T_STRINGCI_H
//-------------------------------------------------------------------
//  CLASS
//  TStringCi
//
//  (C) Herb Sutter (http://www.gotw.ca/gotw/029.htm)
//
//-------------------------------------------------------------------
#undef N_DEFINES
#define N_DEFINES TStringCi
#include "guide/ndefdllclass.h"

#include <string>
#include <iostream>

//-------------------------------------------------------------------
/**
	@brief Case insensitive string variant.
*/
//-------------------------------------------------------------------

struct ignorechar_traits : public stl::char_traits<char>
{
	static bool eq( char c1, char c2 )
	{ 
		return toupper(c1) == toupper(c2); 
	}

	static bool ne( char c1, char c2 )
	{ 
		return toupper(c1) != toupper(c2); 
	}

	static bool lt( char c1, char c2 )
	{ 
		return toupper(c1) <  toupper(c2); 
	}

	static int compare( const char* s1, const char* s2, size_t n ) 
	{
		// Version 1.
		//return memicmp( s1, s2, n );

		// Version 2.
		
		for (stl::size_t i=0; i<n; ++i) {
			if (!eq(s1[i],s2[i])) {
				return lt(s1[i],s2[i])?-1:1;
			}
		}
		return 0;
		
	}

	static const char* find( const char* s, stl::size_t n, const char& a ) 
	{
		// Version 1.
		while( n-- > 0 && toupper(*s) != toupper(a) ) {
			++s;
		}
		return s;

		// Version 2.
		/*
		for (stl::size_t i=0; i<n; ++i) {
			if (eq(s[i],a)) {
				return &(s[i]);
			}
		}
		return 0;
		*/
	}
};

typedef stl::string TString;
typedef stl::basic_string<char, ignorechar_traits> TStringCi;

//-------------------------------------------------------------------
/** 
	Define an output operator because the traits type is different than that for std::ostream
*/
inline std::ostream& operator << (stl::ostream& strm, const TStringCi& s)
{
	// Simply convert the TStringCi into a normal string
	return strm << stl::string(s.data(),s.length());
}

//-------------------------------------------------------------------
#endif

