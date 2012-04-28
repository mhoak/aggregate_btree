// Copyright (C) 2004 Peder Holt
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TYPE_TRAITS_MSVC_REMOVE_CV_HOLT_2004_0901
#define BOOST_TYPE_TRAITS_MSVC_REMOVE_CV_HOLT_2004_0901

#include <boost/type_traits/msvc/typeof.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_array.hpp>

namespace abt_boost{} namespace boost = abt_boost; namespace abt_boost{
    namespace detail {
        template<bool IsPointer,bool IsArray,bool IsConst,bool IsVolatile>
        struct remove_cv_impl_typeof {
            template<typename T,typename ID>
            struct inner {
                typedef T type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };
        template<> //Volatile
        struct remove_cv_impl_typeof<false,false,false,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U volatile&(*)());
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (T(*)())(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T& type;
            };
        };
        template<> //Const
        struct remove_cv_impl_typeof<false,false,true,false> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U const&(*)());
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (T(*)())(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T& type;
            };
        };
        template<> //CV
        struct remove_cv_impl_typeof<false,false,true,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(U const volatile&(*)());
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (T(*)())(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T& type;
            };
        };
        template<> //Volatile Pointer
        struct remove_cv_impl_typeof<true,false,false,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(void(*)(U volatile[]));
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type[];
            };
        };
        template<> //Const Pointer
        struct remove_cv_impl_typeof<true,false,true,false> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(void(*)(U const[]));
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type[];
            };
        };
        template<> //CV Pointer
        struct remove_cv_impl_typeof<true,false,true,true> {
            template<typename T,typename ID>
            struct inner {
                template<typename U>
                static msvc_register_type<U,ID> test(void(*)(U const volatile[]));
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type[];
            };
        };        
        template<> //Volatile Array
        struct remove_cv_impl_typeof<false,true,false,true> {
            template<typename T,typename ID>
            struct inner {
                BOOST_STATIC_CONSTANT(unsigned,value=(sizeof(T)/sizeof((*((T*)NULL))[0])));

                template<typename U>
                static msvc_register_type<U[value],ID> test(void(*)(U volatile[]));
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };
        template<> //Const Array
        struct remove_cv_impl_typeof<false,true,true,false> {
            template<typename T,typename ID>
            struct inner {
                BOOST_STATIC_CONSTANT(unsigned,value=(sizeof(T)/sizeof((*((T*)NULL))[0])));

                template<typename U>
                static msvc_register_type<U[value],ID> test(void(*)(U const[]));
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };

        template<> //CV Array
        struct remove_cv_impl_typeof<false,true,true,true> {
            template<typename T,typename ID>
            struct inner {
                BOOST_STATIC_CONSTANT(unsigned,value=(sizeof(T)/sizeof((*((T*)NULL))[0])));

                template<typename U>
                static msvc_register_type<U[value],ID> test(void(*)(U const volatile[]));
                static msvc_register_type<T,ID> test(...);
                BOOST_STATIC_CONSTANT(unsigned,register_test=sizeof(test( (void(*)(T))(NULL) ) ));
                typedef typename msvc_extract_type<ID>::id2type::type type;
            };
            template<typename T>
            struct transform_type {
                typedef T type;
            };
        };

    } //namespace detail

    template<typename T>
    struct remove_cv {
        typedef abt_boost::detail::remove_cv_impl_typeof<
            abt_boost::is_pointer<T>::value,
            abt_boost::is_array<T>::value,
            abt_boost::is_const<T>::value,
            abt_boost::is_volatile<T>::value
        > remove_cv_type;
        typedef typename 
            remove_cv_type::template inner<
                typename remove_cv_type::template transform_type<T>::type,
                remove_cv<T>
            >::type
        type;
        BOOST_MPL_AUX_LAMBDA_SUPPORT(1,remove_cv,T)
    };
}//namespace abt_boost

#endif //BOOST_TYPE_TRAITS_MSVC_REMOVE_CV_HOLT_2004_0901