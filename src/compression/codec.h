// Copyright 2012 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PARQUET_COMPRESSION_CODEC_H
#define PARQUET_COMPRESSION_CODEC_H

#include "parquet/parquet.h"

#include <boost/cstdint.hpp>
#include "gen-cpp/parquet_constants.h"
#include "gen-cpp/parquet_types.h"

namespace parquet_cpp {

class Codec {
 public:
  virtual ~Codec() {}
  virtual void Decompress(int input_len, const uint8_t* input,
      int output_len, uint8_t* output_buffer) = 0;

  virtual int Compress(int input_len, const uint8_t* input,
      int output_buffer_len, uint8_t* output_buffer) = 0;

  virtual int MaxCompressedLen(int input_len, const uint8_t* input) = 0;

  virtual const char* name() const = 0;
};


// Snappy codec.
class SnappyCodec : public Codec {
 public:
  virtual void Decompress(int input_len, const uint8_t* input,
      int output_len, uint8_t* output_buffer);

  virtual int Compress(int input_len, const uint8_t* input,
      int output_buffer_len, uint8_t* output_buffer);

  virtual int MaxCompressedLen(int input_len, const uint8_t* input);

  virtual const char* name() const { return "snappy"; }
};

// Lz4 codec.
class Lz4Codec : public Codec {
 public:
  virtual void Decompress(int input_len, const uint8_t* input,
      int output_len, uint8_t* output_buffer);

  virtual int Compress(int input_len, const uint8_t* input,
      int output_buffer_len, uint8_t* output_buffer);

  virtual int MaxCompressedLen(int input_len, const uint8_t* input);

  virtual const char* name() const { return "lz4"; }
};

// GZip codec.
class GZipCodec : public Codec {
 public:
  virtual void Decompress(int input_len, const uint8_t* input,
      int output_len, uint8_t* output_buffer);

  virtual int Compress(int input_len, const uint8_t* input,
      int output_buffer_len, uint8_t* output_buffer);

  virtual int MaxCompressedLen(int input_len, const uint8_t* input);

  virtual const char* name() const { return "gzip"; }
};

}

#endif

