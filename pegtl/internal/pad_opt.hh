// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_INTERNAL_PAD_OPT_HH
#define PEGTL_INTERNAL_PAD_OPT_HH

#include "seq.hh"
#include "skip_control.hh"
#include "opt.hh"
#include "star.hh"

namespace pegtl
{
   namespace internal
   {
      template< typename Rule, typename Pad >
      using pad_opt = seq< skip_control< star< Pad > >, skip_control< opt< Rule, skip_control< star< Pad > > > > >;

   } // internal

} // pegtl

#endif
