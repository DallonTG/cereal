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
#ifndef CEREAL_BINARY_ARCHIVE_STRING_HPP_
#define CEREAL_BINARY_ARCHIVE_STRING_HPP_

#include <cereal/binary_archive/binary_archive.hpp>
#include <string>

namespace cereal
{
  //! Serialization for basic_string types to binary
  template<class CharT, class Traits, class Alloc> inline
  void save(BinaryOutputArchive & ar, std::basic_string<CharT, Traits, Alloc> const & str)
  {
    // Save number of chars + the data
    ar & str.size();
    ar.saveBinary(str.data(), str.size() * sizeof(CharT));
  }

  //! Serialization for basic_string types from binary
  template<class CharT, class Traits, class Alloc> inline
  void load(BinaryInputArchive & ar, std::basic_string<CharT, Traits, Alloc> & str)
  {
    size_t size;
    ar & size;
    str.resize(size);
    ar.loadBinary(const_cast<CharT*>(str.data()), size * sizeof(CharT));
  }
} // namespace cereal

#endif // CEREAL_BINARY_ARCHIVE_STRING_HPP_
