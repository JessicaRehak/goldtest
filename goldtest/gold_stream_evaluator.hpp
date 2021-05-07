#ifndef GOLDTEST_GOLD_STREAM_EVALUATOR_HPP_
#define GOLDTEST_GOLD_STREAM_EVALUATOR_HPP_

#include <exception>
#include <memory>
#include <iostream>

#include "stream_evaluator_i.hpp"

namespace goldtest {

//! This class will conduct a line by line comparison test on two streams.
/*!
 The two streams are the "gold" standard `gold_stream` and an "actual" stream
 `actual_stream`.
 
 \author Joshua Rehak
 \date 2018/2
 */
class GoldStreamEvaluator : public StreamEvaluatorI {
 public:
  //! Constructor, takes ownership of two streams for comparison
  GoldStreamEvaluator(std::unique_ptr<std::istream> actual_stream, std::unique_ptr<std::istream> gold_stream)
      : actual_stream_(std::move(actual_stream)), gold_stream_(std::move(gold_stream)) {
    if (actual_stream_ == nullptr)
      throw std::invalid_argument("Pointer to actual stream provided to GoldStreamEvaluator is null");
    if (gold_stream_ == nullptr)
      throw std::invalid_argument("Pointer to gold stream provided to GoldStreamEvaluator is null");
  };

  bool Compare() const override { return false; };
  std::string GetDiff() const override { return std::string(); };
  bool RunGoldTest() const override { return false; };

  bool GoldGood() const override { return gold_stream_->good(); };
  bool ActualGood() const override { return actual_stream_->good(); };
  auto gold_stream() -> InStream * override { return gold_stream_.get(); }
  auto actual_stream() -> InStream * override { return actual_stream_.get(); }

  //! Closes both stream
  void CloseStreams() {};
 private:
  //! Resets the streams to `bof`
  void ResetStreams() const {};

  mutable std::unique_ptr<std::istream> actual_stream_;
  mutable std::unique_ptr<std::istream> gold_stream_;
};

} // namespace goldtest

#endif // GOLDTEST_GOLD_STREAM_EVALUATOR_HPP_
