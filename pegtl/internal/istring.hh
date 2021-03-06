// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_ISTRING_HH
#define PEGTL_INTERNAL_ISTRING_HH

#include <type_traits>

#include "trivial.hh"

#include "../analysis/counted.hh"

namespace pegtl
{
   namespace internal
   {
      template< char C >
      using is_alpha = std::integral_constant< bool, ( ( 'a' <= C ) && ( C <= 'z' ) ) || ( ( 'A' <= C ) && ( C <= 'Z' ) ) >;

      template< char C, bool A = is_alpha< C >::value > struct ichar_equal;

      template< char C > struct ichar_equal< C, true >
      {
         static bool match( const char c )
         {
            return ( C | 0x20 ) == ( c | 0x20 );
         }
      };

      template< char C > struct ichar_equal< C, false >
      {
         static bool match( const char c )
         {
            return c == C;
         }
      };

      template< char ... Cs > struct istring_equal;

      template<> struct istring_equal<>
      {
         static bool match( const char * )
         {
            return true;
         }
      };

      template< char C, char ... Cs > struct istring_equal< C, Cs ... >
      {
         static bool match( const char * r )
         {
            return ichar_equal< C >::match( * r ) && istring_equal< Cs ... >::match( r + 1 );
         }
      };

      template< char ... Cs > struct istring;

      template<> struct istring<>
            : trivial< true > {};

      template< char C, char ... Cs >
      struct istring< C, Cs ... >
      {
         using analyze_t = analysis::counted< analysis::rule_type::ANY, 1 + sizeof ... ( Cs ) >;

         template< typename Input >
         static bool match( Input & in )
         {
            if ( in.size() >= 1 + sizeof ... ( Cs ) ) {
               if ( istring_equal< C, Cs ... >::match( in.begin() ) ) {
                  in.bump( 1 + sizeof ... ( Cs ) );
                  return true;
               }
            }
            return false;
         }
      };

   } // internal

} // pegtl

#endif
