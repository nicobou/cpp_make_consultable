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

#define Make_consultable(_member_type,                                  \
                         _member_rawptr,                                \
                         _consult_method)                               \
  static_assert(std::is_class<_member_type>::value,                     \
                "Make_consultable 1st arg must be a class");            \
                                                                        \
  /*disabling key type for later forward*/                              \
  using _consult_method##MapKey_t = decltype(nullptr);                  \
  /*saving consultable type for the forwarder(s)*/                      \
  using _consult_method##Consult_t = typename                           \
      std::remove_pointer<std::decay<_member_type>::type>::type;        \
                                                                        \
  /* exposing T const methods accessible by T instance owner*/          \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs>                                             \
  inline R _consult_method(R(_member_type::*fun)(ATs...) const,         \
			   BTs ...args)	const {                         \
    return ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);        \
  }                                                                     \
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs>                                             \
  inline void _consult_method(void(_member_type::*fun)(ATs...) const,	\
			      BTs ...args) const {                      \
    ((_member_rawptr)->*fun)(std::forward<BTs>(args)...);               \
  }                                                                     \
                                                                        \
  /* disable invokation of non const*/                                  \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs>                                             \
  R _consult_method(R(_member_type::*function)(ATs...),                 \
                    BTs ...) const {                                    \
    static_assert(std::is_const<decltype(function)>::value,             \
                  "consultation is available for const methods only");  \
    return R();  /* for syntax only since assert should always fail */  \
  }                                                                     \
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs>                                             \
  void _consult_method(void(_member_type::*function)(ATs...),           \
                       BTs ...) const {                                 \
    static_assert(std::is_const<decltype(function)>::value,             \
                  "consultation is available for const methods only");  \
  }



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
           typename ...BTs>                                                            \
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
               BTs ...args) const {                                     \
    static_assert(std::is_const<decltype(function)>::value,		\
                  "consultation is available for const methods only");  \
    return R();  /* for syntax only */                                  \
  }									\
                                                                        \
  template<typename ...ATs,                                             \
           typename ...BTs>						\
  void _fw_method(void( _fw_method##Consult_t ::*function)(ATs...),     \
                  BTs ...args) const {                                  \
    static_assert(std::is_const<decltype(function)>::value,		\
                  "consultation is available for const methods only");  \
  }


#define Forward_consultable(_member_type,                               \
                            _member_rawptr,                             \
                            _consult_method,                            \
                            _fw_method)                                 \
                                                                        \
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
                                                                        \
  /*forwarding consult from map if the map key type is defined*/        \
  template<typename R,                                                  \
           typename ...ATs,                                             \
           typename ...BTs,                                             \
           /* enable_if work is depends from a template parameter, */   \
           /* using sizeof...(ATs) for that*/                           \
           class = typename                                             \
           std::enable_if<(sizeof...(ATs),                              \
                           /* if _fw_method##MapKey_t is the same */    \
                           /* type as nullptr then this forward does */ \
                           /* not require map key forwarding*/          \
                           !std::is_same<decltype(nullptr),             \
                           _fw_method##MapKey_t >::value)>::type>       \
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
           class = typename                                             \
           std::enable_if<(sizeof...(ATs),                              \
                           /* if _fw_method##MapKey_t is the same */    \
                           /* type as nullptr then this forward does */ \
                           /* not require map key forwarding*/          \
                           !std::is_same<decltype(nullptr),             \
                           _fw_method##MapKey_t >::value)>::type>       \
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
  
#endif
