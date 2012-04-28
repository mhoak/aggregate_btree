//  (C) Copyright 2009-2011 Frederic Bron.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_HAS_MINUS_HPP_INCLUDED
#define BOOST_TT_HAS_MINUS_HPP_INCLUDED

#define BOOST_TT_TRAIT_NAME has_minus
#define BOOST_TT_TRAIT_OP -
#define BOOST_TT_FORBIDDEN_IF\
   ::abt_boost::type_traits::ice_or<\
      /* Lhs==pointer and Rhs==fundamental and Rhs!=integral */\
      ::abt_boost::type_traits::ice_and<\
         ::abt_boost::is_pointer< Lhs_noref >::value,\
         ::abt_boost::is_fundamental< Rhs_nocv >::value,\
         ::abt_boost::type_traits::ice_not< ::abt_boost::is_integral< Rhs_noref >::value >::value\
      >::value,\
      /* Lhs==void* and (Rhs==fundamental or Rhs==pointer) */\
      ::abt_boost::type_traits::ice_and<\
         ::abt_boost::is_pointer< Lhs_noref >::value,\
         ::abt_boost::is_void< Lhs_noptr >::value,\
         ::abt_boost::type_traits::ice_or<\
            ::abt_boost::is_fundamental< Rhs_nocv >::value,\
            ::abt_boost::is_pointer< Rhs_noref >::value\
         >::value\
      >::value,\
      /* Rhs==void* and (Lhs==fundamental or Lhs==pointer) */\
      ::abt_boost::type_traits::ice_and<\
         ::abt_boost::is_pointer< Rhs_noref >::value,\
         ::abt_boost::is_void< Rhs_noptr >::value,\
         ::abt_boost::type_traits::ice_or<\
            ::abt_boost::is_fundamental< Lhs_nocv >::value,\
            ::abt_boost::is_pointer< Lhs_noref >::value\
         >::value\
      >::value,\
      /* Lhs=fundamental and Rhs=pointer */\
      ::abt_boost::type_traits::ice_and<\
         ::abt_boost::is_fundamental< Lhs_nocv >::value,\
         ::abt_boost::is_pointer< Rhs_noref >::value\
      >::value,\
      /* two different pointers */\
      ::abt_boost::type_traits::ice_and<\
         ::abt_boost::is_pointer< Lhs_noref >::value,\
         ::abt_boost::is_pointer< Rhs_noref >::value,\
         ::abt_boost::type_traits::ice_not< ::abt_boost::is_same< Lhs_nocv, Rhs_nocv >::value >::value\
      >::value\
   >::value


#include <boost/type_traits/detail/has_binary_operator.hpp>

#undef BOOST_TT_TRAIT_NAME
#undef BOOST_TT_TRAIT_OP
#undef BOOST_TT_FORBIDDEN_IF

#endif