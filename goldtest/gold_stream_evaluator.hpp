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
  GoldStreamEvaluator(std::shared_ptr<std::istream> actual_stream, std::shared_ptr<std::istream> gold_stream)
      : actual_stream_(std::move(actual_stream)), gold_stream_(std::move(gold_stream)) {
    if (actual_stream_ == nullptr)
      throw std::invalid_argument("Pointer to actual stream provided to GoldStreamEvaluator is null");
    if (gold_stream_ == nullptr)
      throw std::invalid_argument("Pointer to gold stream provided to GoldStreamEvaluator is null");
  };

  auto StreamsAreTheSame() const -> bool override {
    if (gold_stream_->bad()) {
      throw std::runtime_error("Error in StreamsAreTheSame: gold stream is bad.");
    } else if (actual_stream_->bad()) {
      throw std::runtime_error("Error in StreamsAreTheSame: actual stream is bad.");
    }

    ResetStreams();

    std::string gold_line{}, actual_line{};
    unsigned int lines_in_gold_file{ 0 }, lines_in_actual_file{ 0 };

    while(!gold_stream_->eof()) {
      getline(*gold_stream_, gold_line);
      ++lines_in_gold_file;
    }
    while (!actual_stream_->eof()) {
      getline(*actual_stream_, actual_line);
      ++lines_in_actual_file;
    }

    ResetStreams();

    bool streams_are_the_same{ lines_in_gold_file == lines_in_actual_file };

    if (lines_in_gold_file == lines_in_actual_file) {
      while (getline(*gold_stream_, gold_line)) {
        getline(*actual_stream_, actual_line);
        if (gold_line != actual_line) {
          streams_are_the_same = false;
          break;
        }
      }
    }

    return streams_are_the_same;
  }

  std::string GetDiff() const override { return std::string(); };
  bool RunGoldTest() const override { return false; };

  auto gold_stream() -> InStream * override { return gold_stream_.get(); }
  auto actual_stream() -> InStream * override { return actual_stream_.get(); }

  //! Closes both stream
  void CloseStreams() {};
 private:
  //! Resets the streams to `bof`
  auto ResetStreams() const -> void {
    for (auto& stream : std::array{actual_stream_, gold_stream_}) {
      stream->clear();
      stream->seekg(0, std::ios::beg);
    }
  };

  mutable std::shared_ptr<std::istream> actual_stream_;
  mutable std::shared_ptr<std::istream> gold_stream_;
};

} // namespace goldtest

#endif // GOLDTEST_GOLD_STREAM_EVALUATOR_HPP_
