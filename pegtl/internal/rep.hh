// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_REP_HH
#define PEGTL_INTERNAL_REP_HH

#include "trivial.hh"
#include "rule_conjunction.hh"

#include "../analysis/counted.hh"

namespace pegtl
{
   namespace internal
   {
      template< unsigned, typename ... > struct rep;

      template< unsigned Num >
      struct rep< Num >
            : trivial< true > {};

      template< typename Rule, typename ... Rules >
      struct rep< 0, Rule, Rules ... >
            : trivial< true > {};

      template< unsigned Num, typename Rule, typename ... Rules >
      struct rep< Num, Rule, Rules ... >
      {
         using analyze_t = analysis::counted< analysis::rule_type::SEQ, Num, Rule, Rules ... >;

         template< apply_mode A, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
         static bool match( Input & in, States && ... st )
         {
            auto m = in.mark();

            for ( unsigned i = 0; i < Num; ++i ) {
               if ( ! rule_conjunction< Rule, Rules ... >::template match< A, Action, Control >( in, st ... ) ) {
                  return m( false );
               }
            }
            return m( true );
         }
      };

   } // internal

} // pegtl

#endif
