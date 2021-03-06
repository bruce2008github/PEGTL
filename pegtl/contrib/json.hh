// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_CONTRIB_JSON_HH
#define PEGTL_CONTRIB_JSON_HH

#include "../rules.hh"
#include "../ascii.hh"
#include "../utf8.hh"
#include "abnf.hh"

namespace pegtl
{
   namespace json
   {
      // JSON grammar according to RFC 7159 (for UTF-8 encoded JSON only).

      using namespace abnf;

      struct ws : one< ' ', '\t', '\n', '\r' > {};

      struct begin_array : pad< one< '[' >, ws > {};
      struct begin_object : pad< one< '{' >, ws > {};
      struct end_array : pad< one< ']' >, ws > {};
      struct end_object : pad< one< '}' >, ws > {};
      struct name_separator : pad< one< ':' >, ws > {};
      struct value_separator : pad< one< ',' >, ws > {};

      struct false_ : string< 'f', 'a', 'l', 's', 'e' > {};
      struct null : string< 'n', 'u', 'l', 'l' > {};
      struct true_ : string< 't', 'r', 'u', 'e' > {};

      struct required_digits : plus< DIGIT > {};
      struct exp : if_must< one< 'e', 'E' >, opt< one< '-', '+' > >, required_digits > {};
      struct frac : if_must< one< '.' >, required_digits > {};
      struct int_ : sor< one< '0' >, required_digits > {};
      struct number : seq< opt< one< '-' > >, int_, opt< frac >, opt< exp > > {};

      struct required_xdigit : HEXDIG {};
      struct unicode : seq< one< 'u' >, rep< 4, required_xdigit > > {};
      struct escaped_char : one< '"', '\\', '/', 'b', 'f', 'n', 'r', 't' > {};
      struct escaped : sor< escaped_char, unicode > {};
      struct unescaped : utf8::range< 0x20, 0x10FFFF > {};
      struct char_ : if_then_else< one< '\\' >, escaped, unescaped > {};
      struct string_cont : until< one< '"' >, must< char_ > > {};
      struct string : if_must< one< '"' >, string_cont > {};

      struct value;

      struct member : if_must< string, name_separator, value > {};
      struct object : if_must< begin_object, opt< list_must< member, value_separator > >, end_object > {};

      struct array : if_must< begin_array, opt< list_must< value, value_separator > >, end_array > {};

      struct value : sor< false_, null, true_, object, array, number, string > {};

      struct text : pad< value, ws > {};

   } // json

} // pegtl

#endif
