#ifndef GOLDTEST_GOLDTEST_HPP_
#define GOLDTEST_GOLDTEST_HPP_

#include <fstream>
#include <gtest/gtest.h>

#include "goldtest/gold_stream_evaluator.hpp"

#define EXPECT_GOLD_FILE_MATCH(actual_file_location, gold_file_location) \
EXPECT_PRED_FORMAT2(goldtest::gold_test_passes, actual_file_location, gold_file_location)

namespace goldtest {

testing::AssertionResult gold_test_passes(const char*,
                                          const char*,
                                          const std::string& actual_file_location,
                                          const std::string& gold_file_location) {
  goldtest::GoldStreamEvaluator stream_evaluator(std::make_shared<std::ifstream>(actual_file_location),
                                                 std::make_shared<std::ifstream>(gold_file_location));

  if (stream_evaluator.StreamsAreGoodAndTheSame()) return testing::AssertionSuccess();

  if (stream_evaluator.gold_stream()->fail()) {
    return testing::AssertionFailure() << "Failed to open gold file at " << gold_file_location;
  } else if (stream_evaluator.actual_stream()->fail()) {
    return testing::AssertionFailure() << "Failed to open actual file at " << actual_file_location;
  }
  return testing::AssertionFailure() << "File at " << actual_file_location <<
                                     " is not the same as the gold file at location " << gold_file_location
                                     << " with diff " << stream_evaluator.GetDiff();
}

} // namespace goldtest

#endif //GOLDTEST_GOLDTEST_HPP_
