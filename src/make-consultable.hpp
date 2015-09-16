/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Nicolas Bouillot
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef __MAKE_CONSULTABLE_H__
#define __MAKE_CONSULTABLE_H__

#include <functional>
#include <type_traits>
#include <cstddef> // size_t
#include <tuple>  // method_traits args

namespace nicobou {
template<typename F, F f>
struct method_traits;

// const member function pointer
template<typename C, typename R, typename ...Args, R (C::*fn_ptr)(Args... ) const >
struct method_traits<R(C::*)(Args...) const, fn_ptr>
{
  using return_type = R;
  using method_t = R(C::*)(Args...) const;
  static constexpr method_t ptr = fn_ptr;
  static constexpr bool is_const = true;
};

// member function pointer
template<typename C, typename R, typename ...Args, R (C::*fn_ptr)(Args... ) >
struct method_traits<R(C::*)(Args...), fn_ptr>
{
  using return_type = R;
  using method_t = R(C::*)(Args...);
  static constexpr method_t ptr = fn_ptr;
  static constexpr bool is_const = false;
};

}  // namespace nicobou

// selecting method and Overload for template parameter of consultation method
#define Method(_method_ptr)                     \
  decltype(_method_ptr), _method_ptr            

#define Overload(_PTR, _C, _R, ...)             \
  decltype(static_cast<_R(_C::*)(__VA_ARGS__)>(_PTR)), _PTR

#define Const_Overload(_PTR, _C, _R, ...)               \
  decltype(static_cast<_R(_C::*)(__VA_ARGS__) const>(_PTR)), _PTR


// encapsulation:
#define Encapsulate_consultable(_consult_method,                        \
                                _encapsulate_return_type,               \
                                _method_encapsulated)                   \
  template <typename DUMMY>                                             \
  struct _consult_method##encaps_ret<bool, DUMMY>{                      \
    using encaps_return_t = _encapsulate_return_type;                   \
    static inline encaps_return_t global_encaps() {                     \
      std::cout << "coucou" << std::endl;                               \
      return _encapsulate_return_type();                                \
    }                                                                   \
  };  

#define Overload_consultable(_consult_method,                           \
                             _delegated_method_ptr,                     \
                             _alternative_method_ptr)                   \
  /*FIXME check signatures compatibility*/                              \
template<typename DUMMY>                                                \
struct _consult_method##alternative_member_<decltype(_delegated_method_ptr), \
                                            _delegated_method_ptr,      \
                                            DUMMY> {                    \
  /*FIXME use return type deduction and argument types deduction: */    \
  static decltype(_delegated_method_ptr) get() {                        \
    /*reinterpret cast is used for let get method user the alternative*/ \
    /* method is from expected class, but what we want actually, */     \
    /* is a function with same return type and arguments*/              \
    return reinterpret_cast<decltype(_delegated_method_ptr)>(           \
        _alternative_method_ptr);                                       \
  }                                                                     \
};                                                                      \


#define Make_access(_self_type,                                         \
                    _member_type,                                       \
                    _member_rawptr,                                     \
                    _consult_method,                                    \
                    _access_flag)                                       \
  static_assert(std::is_class<_member_type>::value,                     \
                "Make_consultable and Make Delegate first "             \
                "argument must be a class");                            \
                                                                        \
  /*disabling key type for later forward*/                              \
  using _consult_method##MapKey_t = decltype(nullptr);                  \
  /*saving consultable type for the forwarder(s)*/                      \
  using _consult_method##Consult_t = typename                           \
      std::remove_pointer<std::decay<_member_type>::type>::type;        \
                                                                        \
  enum _consult_method##NonConst_t {                                    \
    _consult_method##non_const,                                         \
        _consult_method##const_only                                     \
        };                                                              \
                                                                        \
  /* --- global encapsultaion*/                                         \
  /* testing existance of a global ecapsulation method */               \
  /* FIXME use modern version of this */                                \
  template <typename Tested>                                            \
  class _consult_method##_has_encaps_method {                           \
    template <typename C> static char test(                             \
        decltype(&C::_consult_method##enable_encaps));                  \
    template <typename C> static long test(...);                        \
   public:                                                              \
   enum { value = sizeof(test<Tested>(nullptr)) == sizeof(char) };      \
  };                                                                    \
                                                                        \
  template <typename FlagType, typename DUMMY = void>                   \
  struct _consult_method##encaps_ret{                                   \
    using unused_type = FlagType;                                       \
    using encaps_return_t = bool;                                       \
    static inline encaps_return_t global_encaps() {                     \
      return true;                                                      \
    }                                                                   \
  };                                                                    \
  /* FIXME get a type to allocate to encaps_return_t */                 \
  template <typename DUMMY>                                             \
  struct _consult_method##encaps_ret<bool, DUMMY>{                      \
    using encaps_return_t = int;                                        \
    static inline encaps_return_t global_encaps() {                     \
      return encaps_return_t();                                         \
    }                                                                   \
  };                                                                    \
                                                                        \
/*getting alternative invocation */                                     \
  template<typename FlagType>                                           \
  static typename _consult_method##encaps_ret<FlagType>::encaps_return_t \
  _consult_method##get_global_encaps(){                                 \
    return _consult_method##encaps_ret<FlagType>::global_encaps();      \
  }                                                                     \
                                                                        \
  /* --- selective encapsulation*/                                      \
  /* no default alternative to delegated method invokation: */          \
  template<typename MemberType,                                         \
           MemberType ptr,                                              \
           typename DUMMY = void>                                       \
  struct _consult_method##alternative_member_ {                         \
    static MemberType get(){                                            \
      return nullptr;                                                   \
    };                                                                  \
  };                                                                    \
  /*getting alternative invocation */                                   \
  template<typename MemberType, MemberType t>                           \
  static MemberType _consult_method##get_alternative() {                \
    return _consult_method##alternative_member_<MemberType, t>::get();  \
  }                                                                     \
                                                                        \
  /* const and non void return  */                                      \
  template<typename MMType,                                             \
           MMType fun,                                                  \
           typename ...BTs>                                             \
  inline typename std::                                                 \
  enable_if<!std::is_same<void,                                         \
                          typename nicobou::                        \
                          method_traits<MMType, fun>::return_type>::value, \
            typename nicobou::method_traits<MMType, fun>::return_type \
            >::type                                                     \
  _consult_method##2(BTs ...args) const {                               \
    static_assert(nicobou::method_traits<MMType, fun>::is_const,        \
                  "consultation is available for const methods only");  \
    /* __attribute__((unused)) tells compiler encap is not used*/       \
    auto encap __attribute__((unused)) =                                \
        _consult_method##get_global_encaps<bool>();                     \
        auto alt =                                                      \
            _consult_method##get_alternative<decltype(fun), fun>();     \
        if(nullptr != alt)                                              \
          return ((_member_rawptr)->*alt)(std::forward<BTs>(args)...);  \
        return ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);    \
  }                                                                     \
                                                                        \
  /*const and void returning*/                                          \
  template<typename MMType,                                             \
           MMType fun,                                                  \
           typename ...BTs>                                             \
  inline typename std::                                                 \
  enable_if<std::is_same<void,                                          \
                         typename nicobou::                         \
                         method_traits<MMType, fun>::return_type>::value\
            >::type                                                     \
  _consult_method##2(BTs ...args) const {                               \
    static_assert(nicobou::method_traits<MMType, fun>::is_const,        \
                  "consultation is available for const methods only");  \
    /* __attribute__((unused)) tells compiler encap is not used*/       \
    auto encap __attribute__((unused)) =                                \
        _consult_method##get_global_encaps<bool>();                     \
    auto alt =                                                          \
        _consult_method##get_alternative<decltype(fun), fun>();         \
        if(nullptr != alt)                                              \
          ((_member_rawptr)->*alt)(std::forward<BTs>(args)...);         \
        else                                                            \
          ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);         \
  }                                                                     \
                                                                        \
  /* non const and non void return  */                                  \
  template<typename MMType,                                             \
           MMType fun,                                                  \
           typename ...BTs,                                             \
           int flag=_consult_method##_access_flag>                      \
  inline typename std::                                                 \
  enable_if<!std::is_same<void,                                         \
                          typename nicobou::                        \
                          method_traits<MMType, fun>::return_type>::value, \
            typename nicobou::method_traits<MMType, fun>::return_type \
            >::type                                                     \
  _consult_method##2(BTs ...args) {                                     \
    static_assert(nicobou::method_traits<MMType, fun>::is_const     \
                  || (!nicobou::method_traits<MMType, fun>::is_const \
                      && flag == _consult_method##NonConst_t::          \
                      _consult_method##non_const),                      \
                  "consultation is available for const methods only"    \
                  " (delegation is disabled)");                          \
    /* __attribute__((unused)) tells compiler encap is not used*/       \
    auto encap __attribute__((unused)) =                                \
        _consult_method##get_global_encaps<bool>();                     \
        auto alt =                                                      \
            _consult_method##get_alternative<decltype(fun), fun>();     \
        if(nullptr != alt)                                              \
          return ((_member_rawptr)->*alt)(std::forward<BTs>(args)...);  \
        return ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);    \
  }                                                                     \
                                                                        \
  /*const and void returning*/                                          \
  template<typename MMType,                                             \
           MMType fun,                                                  \
           typename ...BTs,                                             \
           int flag=_consult_method##_access_flag>                      \
  inline typename std::                                                 \
  enable_if<std::is_same<void,                                          \
                         typename nicobou::                         \
                         method_traits<MMType, fun>::return_type>::value\
            >::type                                                     \
  _consult_method##2(BTs ...args) {                                     \
    static_assert(nicobou::method_traits<MMType, fun>::is_const         \
                  || (!nicobou::method_traits<MMType, fun>::is_const    \
                      && flag == _consult_method##NonConst_t::          \
                      _consult_method##non_const),                      \
                  "consultation is available for const methods only"    \
                  "(delegation is disabled)");                          \
    /* __attribute__((unused)) tells compiler encap is not used*/       \
    auto encap __attribute__((unused)) =                                \
        _consult_method##get_global_encaps<bool>();                     \
    auto alt =                                                          \
        _consult_method##get_alternative<decltype(fun), fun>();         \
        if(nullptr != alt)                                              \
          ((_member_rawptr)->*alt)(std::forward<BTs>(args)...);         \
        else                                                            \
          ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);         \
  }                                                                     \
                                                                        \
                                                                        \
  /* exposing T const methods accessible by T instance owner*/          \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs,                                             \
           R (_member_type::*)(ATs...) = nullptr,                       \
           typename std::enable_if<                                     \
      !std::is_same<R, void>::value                                     \
      && true>::type * = nullptr>  /* FIXME enable_if should be for return*/ \
  inline R _consult_method(                                             \
      R(_member_type::*fun)(ATs...) const,                              \
      BTs ...args) const {                                              \
    /* __attribute__((unused)) tells compiler encap is not used*/       \
    return ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);        \
  }                                                                     \
                                                \
  template<typename ...ATs,                                             \
           typename ...BTs,                                             \
           void (_member_type::*)(ATs...) = nullptr>                    \
  inline void _consult_method(void(_member_type::*fun)(ATs...) const,	\
			      BTs ...args) const {                      \
    ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);               \
  }                                                                     \
                                                                        \
  /* disable invokation of non-const if the flag is set*/               \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs,                                             \
           int flag=_consult_method##_access_flag>                      \
  inline R _consult_method(R(_member_type::*fun)(ATs...),               \
                           BTs ...args) {                               \
    static_assert(flag == _consult_method##NonConst_t::                 \
                   _consult_method##non_const,                          \
                   "consultation is available for const methods only "  \
                   "and delegation is disabled");                       \
    return ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);        \
  }                                                                     \
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs,                                             \
           int flag=_consult_method##_access_flag>                      \
  void _consult_method(void(_member_type::*fun)(ATs...),                \
                       BTs ...args) {                                   \
    static_assert(flag == _consult_method##NonConst_t::                 \
                  _consult_method##non_const,                           \
                   "consultation is available for const methods only"   \
                  "and delegation is disabled");                        \
    ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);               \
  }                                                                     \
  
#define Make_consultable_default(...)           \
  Make_access(__VA_ARGS__, const_only)

#define Make_delegate(...)                      \
  Make_access(__VA_ARGS__, non_const)

// overloading Make_consultable selection Make_access
// and Make_consultable according to number of args
#define Make_consultable_get_overload(_1, _2, _3, _4, _5, NAME,...) NAME
#define Make_consultable(...)                                           \
  Make_consultable_get_overload(                                        \
      __VA_ARGS__,                                                      \
      Make_access,                                                      \
      Make_consultable_default)(__VA_ARGS__)


#define Forward_consultable_full(_member_type,                          \
                                 _member_rawptr,                        \
                                 _consult_method,                       \
                                 _fw_method,                            \
                                 _access_flag)                          \
  /*forwarding key type*/                                               \
  using _fw_method##MapKey_t =                                          \
      typename std::decay<_member_type>::type::                         \
      _consult_method##MapKey_t;                                        \
                                                                        \
  /*forwarding consultable type for other forwarder(s)*/                \
  using _fw_method##Consult_t = typename                                \
      std::decay<_member_type>::type::                                  \
      _consult_method##Consult_t;                                       \
                                                                        \
  enum  _fw_method##NonConst_t {                                        \
    _fw_method##non_const,                                              \
        _fw_method##const_only                                          \
        };                                                              \
                                                                        \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs>                                             \
  inline R _fw_method(                                                  \
      R( _fw_method##Consult_t ::*function)(ATs...) const,              \
      BTs ...args) const {                                              \
    return (_member_rawptr)->                                           \
        _consult_method<R, ATs...>(                                     \
            std::forward<R( _fw_method##Consult_t ::*)(ATs...) const>(  \
                function),                                              \
            std::forward<BTs>(args)...);                                \
  }                                                                     \
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs>                                             \
  inline void _fw_method(                                               \
      void( _fw_method##Consult_t ::*function)(ATs...) const,           \
      BTs ...args) const {                                              \
    (_member_rawptr)->_consult_method<ATs...>(                          \
        std::forward<void( _fw_method##Consult_t ::*)(ATs...) const>(   \
            function),                                                  \
        std::forward<BTs>(args)...);                                    \
  }									\
                                                                        \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs,                                             \
           int flag=_fw_method##_access_flag>                           \
  inline R _fw_method(                                                  \
      R( _fw_method##Consult_t ::*function)(ATs...),                    \
      BTs ...args) {                                                    \
    static_assert(flag == _fw_method##NonConst_t::                      \
                   _fw_method##non_const,                               \
                   "Forwarded consultation is available for const "     \
                   "methods only");                                     \
    return (_member_rawptr)->                                           \
        _consult_method<R, ATs...>(                                     \
            std::forward<R( _fw_method##Consult_t ::*)(ATs...)>(        \
                function),                                              \
            std::forward<BTs>(args)...);                                \
  }                                                                     \
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs,                                             \
           int flag=_fw_method##_access_flag>                           \
  inline void _fw_method(                                               \
      void( _fw_method##Consult_t ::*function)(ATs...),                 \
      BTs ...args) {                                                    \
    static_assert(flag == _fw_method##NonConst_t::                      \
                   _fw_method##non_const,                               \
                   "Forwarded consultation is available for const "     \
                   "methods only");                                     \
    (_member_rawptr)->_consult_method<ATs...>(                          \
        std::forward<void( _fw_method##Consult_t ::*)(ATs...)>(         \
            function),                                                  \
        std::forward<BTs>(args)...);                                    \
  }									\
                                                                        \
                                                                        \
  /*forwarding consult from map if the map key type is defined*/        \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs,                                             \
           /* enable_if work is depends from a template parameter, */   \
           /* using sizeof...(ATs) for that*/                           \
           typename std::						\
	   enable_if<(sizeof...(ATs),					\
		      /* if _fw_method##MapKey_t is the same */		\
		      /* type as nullptr then this forward does */	\
		      /* not require map key forwarding*/		\
		      !std::is_same<decltype(nullptr),			\
		      _fw_method##MapKey_t >::value)>::type* = nullptr>	\
  inline R _fw_method(                                                  \
      _fw_method##MapKey_t key,                                         \
      /*typename std::enable_if<!std::is_class<>::value, T>::type,*/    \
      R( _fw_method##Consult_t ::*function)(ATs...) const,              \
      BTs ...args) const {                                              \
    return (_member_rawptr)->                                           \
        _consult_method<R, ATs...>(                                     \
            std::forward< _fw_method##MapKey_t >(key),                  \
            std::forward<R( _fw_method##Consult_t ::*)(ATs...) const>(  \
                function),                                              \
            std::forward<BTs>(args)...);                                \
  }                                                                     \
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs,                                             \
           /* enable_if work is depends from a template parameter, */   \
           /* using sizeof(ATs) for that*/                              \
           typename std::						\
	   enable_if<(sizeof...(ATs),					\
		      /* if _fw_method##MapKey_t is the same */		\
		      /* type as nullptr then this forward does */	\
		      /* not require map key forwarding*/		\
		      !std::is_same<decltype(nullptr),			\
		      _fw_method##MapKey_t >::value)>::type* = nullptr>	\
  inline void _fw_method(                                               \
      _fw_method##MapKey_t key,                                         \
      void( _fw_method##Consult_t ::*function)(ATs...) const,           \
      BTs ...args) const {                                              \
    (_member_rawptr)->_consult_method<ATs...>(                          \
        std::forward< _fw_method##MapKey_t >(key),                      \
        std::forward<void( _fw_method##Consult_t ::*)(ATs...) const>(   \
            function),                                                  \
        std::forward<BTs>(args)...);                                    \
  }									\

#define Forward_consultable_default(...)                   \
  Forward_consultable_full(__VA_ARGS__, const_only)

#define Forward_delegate(...)                           \
  Forward_consultable_full(__VA_ARGS__, non_const)

// overloading Forward_consultable selection Make_access
// and Forawrd_consultable according to number of args
#define Forward_consultable_get_overload(_1, _2, _3, _4, _5, NAME,...)  \
  NAME
#define Forward_consultable(...)                                        \
  Forward_consultable_get_overload(                                     \
      __VA_ARGS__,                                                      \
      Forward_consultable_full,                                         \
      Forward_consultable_default)(__VA_ARGS__)

// returns default constructed R if key not found
// assuming the map is storing shared or unique pointers
#define Forward_consultable_from_map(_map_key_type,                     \
                                     _map_member_type,                  \
                                     _map_member,                       \
                                     _consult_method,			\
                                     _fw_method)			\
                                                                        \
  /*saving key type for later forward*/                                 \
  using _fw_method##MapKey_t =                                          \
      const std::decay<_map_key_type>::type &;                          \
                                                                        \
  /*forwarding consultable type for other forwarder(s)*/                \
  using _fw_method##Consult_t = typename                                \
      std::decay<_map_member_type>::type::                              \
      _consult_method##Consult_t;                                       \
                                                                        \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs>                                             \
  R _fw_method(                                                         \
      const typename std::decay<_map_key_type>::type &key,              \
      R( _fw_method##Consult_t ::*function)(ATs...) const,              \
      BTs ...args) const {                                              \
    auto it = _map_member.find(key);					\
    if (_map_member.end() == it){					\
      static typename std::decay<R>::type r; /*if R is a reference*/	\
      return r;                                                         \
    }									\
    return it->second->_consult_method<R, ATs...>(			\
        std::forward<R( _fw_method##Consult_t ::*)(ATs...) const>(      \
            function),                                                  \
        std::forward<BTs>(args)...);                                    \
  }									\
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs>                                             \
  void _fw_method(                                                      \
      const typename std::decay<_map_key_type>::type &key,              \
      void( _fw_method##Consult_t ::*function)(ATs...) const,           \
      BTs ...args) const {                                              \
    auto it = _map_member.find(key);					\
    if (_map_member.end() == it)					\
      return;								\
    it->second->_consult_method<ATs...>(				\
        std::forward<void( _fw_method##Consult_t ::*)(ATs...) const>(   \
            function),                                                  \
        std::forward<BTs>(args)...);                                    \
  }									\
                                                                        \
  /* disable invokation of non const*/                                  \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs>                                             \
  R _fw_method(R( _fw_method##Consult_t ::*function)(ATs...),           \
               BTs ...) const {						\
    static_assert(std::is_const<decltype(function)>::value,		\
                  "consultation is available for const methods only");  \
    return R();  /* for syntax only */                                  \
  }									\
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs>						\
  void _fw_method(void( _fw_method##Consult_t ::*function)(ATs...),     \
                  BTs ...) const {					\
    static_assert(std::is_const<decltype(function)>::value,		\
                  "consultation is available for const methods only");  \
  }

#endif
