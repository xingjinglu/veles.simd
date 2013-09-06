/*! @file normalize.cc
 *  @brief Tests for normalize2D.
 *  @author Vadim Markovtsev <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2013 Samsung R&D Institute Russia
 */


#include <simd/normalize.h>
#include <gtest/gtest.h>

class NormalizeTest : public ::testing::TestWithParam<bool> {
 protected:
  bool is_simd() {
    return GetParam();
  }
};

TEST_P(NormalizeTest, Normalization) {
  uint8_t array[128 * 100];
  memset(array, 1, sizeof(array));
  array[0] = 127;
  array[1] = 15;
  array[10] = 252;
  array[89] = 31;
  array[128 + 21] = 3;
  float res[100 * 100];
  normalize2D(is_simd(), array, 128, 100, 100, res, 100);
  if(is_simd()) {
    ASSERT_NEAR(2.f * (127 - 1) / 251 - 1, res[0], 1e-6);
  } else {
    ASSERT_FLOAT_EQ(2.f * (127 - 1) / 251 - 1, res[0]);
  }
  ASSERT_FLOAT_EQ(2.f * (15 - 1) / 251 - 1, res[1]);
  ASSERT_FLOAT_EQ(-1.f, res[2]);
  ASSERT_FLOAT_EQ(1.f, res[10]);
  ASSERT_FLOAT_EQ(2.f * (31 - 1) / 251 - 1, res[89]);
  ASSERT_FLOAT_EQ(2.f * (3 - 1) / 251 - 1, res[121]);
}

INSTANTIATE_TEST_CASE_P(NormalizeTests, NormalizeTest, ::testing::Bool());

#include "tests/google/src/gtest_main.cc"