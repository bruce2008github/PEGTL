// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#include "test.hh"

namespace pegtl
{
   void unit_test()
   {
      verify_analyze< star_must< eof > >( __LINE__, __FILE__, false, true );
      verify_analyze< star_must< any > >( __LINE__, __FILE__, false );
      verify_analyze< star_must< eof, eof, eof > >( __LINE__, __FILE__, false, true );
      verify_analyze< star_must< any, eof, any > >( __LINE__, __FILE__, false );

      verify_rule< star_must< one< 'a' > > >( __LINE__, __FILE__,  "", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' > > >( __LINE__, __FILE__,  "a", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' > > >( __LINE__, __FILE__,  "aa", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' > > >( __LINE__, __FILE__,  "aaa", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' > > >( __LINE__, __FILE__,  "ba", result_type::SUCCESS, 2 );
      verify_rule< star_must< one< 'a' > > >( __LINE__, __FILE__,  "b", result_type::SUCCESS, 1 );

      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "a", result_type::GLOBAL_FAILURE, 1 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "ab", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "aba", result_type::GLOBAL_FAILURE, 3 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "abb", result_type::SUCCESS, 1 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "abab", result_type::SUCCESS, 0 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "ababc", result_type::SUCCESS, 1 );
      verify_rule< star_must< one< 'a' >, one< 'b' > > >( __LINE__, __FILE__,  "ababab", result_type::SUCCESS, 0 );
   }

} // pegtl

#include "main.hh"
