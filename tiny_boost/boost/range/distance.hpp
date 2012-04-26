// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2006. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_DISTANCE_HPP
#define BOOST_RANGE_DISTANCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/difference_type.hpp>

namespace abt_boost{} namespace boost = abt_boost; namespace abt_boost{

    template< class T >
    inline BOOST_DEDUCED_TYPENAME range_difference<T>::type 
    distance( const T& r )
    {
        return std::distance( abt_boost::begin( r ), abt_boost::end( r ) );
    }

} // namespace 'boost'

#endif
