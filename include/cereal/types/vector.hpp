/*
  Copyright (c) 2013, Randolph Voorhies, Shane Grant
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of cereal nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef CEREAL_TYPES_VECTOR_HPP_
#define CEREAL_TYPES_VECTOR_HPP_

#include <cereal/cereal.hpp>
#include <vector>

#include <iostream>

namespace cereal
{
  //! Serialization for std::vectors of arithmetic (but not bool) using binary serialization, if supported
  template <class Archive, class T, class A> inline
  typename std::enable_if<traits::is_output_serializable<BinaryData<T>, Archive>()
                          && std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, void>::type
  save( Archive & ar, std::vector<T, A> const & vector )
  {
    ar( vector.size() ); // number of elements
    ar( binary_data( vector.data(), vector.size() * sizeof(T) ) );
  }

  //! Serialization for std::vectors of arithmetic (but not bool) using binary serialization, if supported
  template <class Archive, class T, class A> inline
  typename std::enable_if<traits::is_input_serializable<BinaryData<T>, Archive>()
                          && std::is_arithmetic<T>::value && !std::is_same<T, bool>::value, void>::type
  load( Archive & ar, std::vector<T, A> & vector )
  {
    size_t vectorSize;
    ar( vectorSize );

    vector.resize( vectorSize );
    ar( binary_data( vector.data(), vectorSize * sizeof(T) ) );
  }

  //! Serialization for non-arithmetic (and bool) vector types
  template <class Archive, class T, class A> inline
  typename std::enable_if<!traits::is_output_serializable<BinaryData<T>, Archive>()
                          || !std::is_arithmetic<T>::value
                          || std::is_same<T, bool>::value, void>::type
  save( Archive & ar, std::vector<T, A> const & vector )
  {
    ar( vector.size() ); // number of elements
    for( auto it = vector.begin(), end = vector.end(); it != end; ++it )
      ar( *it );
  }

  //! Serialization for non-arithmetic (and bool) vector types
  template <class Archive, class T, class A> inline
  typename std::enable_if<!traits::is_input_serializable<BinaryData<T>, Archive>()
                          || !std::is_arithmetic<T>::value
                          || std::is_same<T, bool>::value, void>::type
  load( Archive & ar, std::vector<T, A> & vector )
  {
    size_t size;
    ar( size );

    vector.resize( size );
    for( auto it = vector.begin(), end = vector.end(); it != end; ++it )
      ar( *it );
  }
} // namespace cereal

#endif // CEREAL_TYPES_VECTOR_HPP_