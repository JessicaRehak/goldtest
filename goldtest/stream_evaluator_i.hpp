#ifndef GOLDTEST_STREAM_EVALUATOR_I_HPP_
#define GOLDTEST_STREAM_EVALUATOR_I_HPP_

#include <iostream>

namespace goldtest {

//! This class provides an interface for a class to evaluate two streams
/*!
  The two streams are the "gold" standard `gold_stream` and an "actual" stream
  `actual_stream`.

  \author J. Rehak
  \date 2020/05
*/

class StreamEvaluatorI {
 public:
  using InStream = std::istream;

  virtual ~StreamEvaluatorI() = default;

  //! Returns the result of the comparison
  virtual auto StreamsAreTheSame() const -> bool = 0;

  //! Returns the difference between the two streams
  virtual auto GetDiff() const -> std::string = 0;

  //! Returns the result of a "Gold" test, `true` if both streams are good and identical, `false` otherwise
  virtual auto RunGoldTest() const -> bool = 0;

  //! Get the gold input stream
  virtual auto gold_stream() -> InStream* = 0;

  //! Get the actual input stream
  virtual auto actual_stream() -> InStream* = 0;
};

} // namespace goldtest

#endif //GOLDTEST_STREAM_EVALUATOR_I_HPP_
