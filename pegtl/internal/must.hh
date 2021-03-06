// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_MUST_HH
#define PEGTL_INTERNAL_MUST_HH

#include "seq.hh"
#include "skip_control.hh"

namespace pegtl
{
   namespace internal
   {
      template< typename ... Rules >
      struct must
            : seq< skip_control< must< Rules > >... > {};

      template< typename Rule >
      struct must< Rule >
      {
         using analyze_t = typename Rule::analyze_t;

         template< apply_mode A, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
         static bool match( Input & in, States && ... st )
         {
            if ( ! Control< Rule >::template match< A, Action, Control >( in, st ... ) ) {
               Control< Rule >::raise( static_cast< const Input & >( in ), st ... );
            }
            return true;
         }
      };

   } // internal

} // pegtl

#endif
