// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_TRIVIAL_HH
#define PEGTL_INTERNAL_TRIVIAL_HH

#include "../analysis/counted.hh"

namespace pegtl
{
   namespace internal
   {
      template< bool What >
      struct trivial
      {
         using analyze_t = analysis::counted< analysis::rule_type::ANY, unsigned( ! What ) >;

         template< typename Input >
         static bool match( Input & )
         {
            return What;
         }
      };

   } // internal

} // pegtl

#endif
