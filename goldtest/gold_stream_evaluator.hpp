#ifndef GOLDTEST_GOLD_STREAM_EVALUATOR_HPP_
#define GOLDTEST_GOLD_STREAM_EVALUATOR_HPP_

#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include <dtl.hpp>

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
    CheckStreams();
    ResetStreams();

    const auto lines_in_gold_file{ CountLinesAndReset(gold_stream_.get()) };
    const auto lines_in_actual_file{ CountLinesAndReset(actual_stream_.get()) };

    std::string gold_line, actual_line;
    bool streams_are_the_same{ lines_in_gold_file == lines_in_actual_file };

    if (lines_in_gold_file == lines_in_actual_file) {
      while (std::getline(*gold_stream_, gold_line)) {
        std::getline(*actual_stream_, actual_line);
        if (gold_line != actual_line) {
          streams_are_the_same = false;
          break;
        }
      }
    }

    return streams_are_the_same;
  }
  auto StreamsAreGoodAndTheSame() const -> bool override {
    if (gold_stream_->bad() || actual_stream_->bad())
      return false;
    return StreamsAreTheSame();
  }

  auto GetDiff() const -> std::string override {
    CheckStreams();
    ResetStreams();

    std::ostringstream diff_stream;
    std::string line_buffer;
    std::vector<std::string> gold_lines, actual_lines;

    while (std::getline(*gold_stream_, line_buffer))
      gold_lines.push_back(line_buffer);
    while(std::getline(*actual_stream_, line_buffer))
      actual_lines.push_back(line_buffer);

    dtl::Diff<std::string> diff(gold_lines, actual_lines);
    diff.onHuge();
    diff.compose();
    diff.composeUnifiedHunks();
    diff.printUnifiedFormat(diff_stream);

    return diff_stream.str();
  };

  auto gold_stream() -> InStream * override { return gold_stream_.get(); }
  auto actual_stream() -> InStream * override { return actual_stream_.get(); }
 private:
  auto CheckStreams() const -> void {
    if (gold_stream_->bad()) {
      throw std::runtime_error("Error in StreamsAreTheSame: gold stream is bad.");
    } else if (actual_stream_->bad()) {
      throw std::runtime_error("Error in StreamsAreTheSame: actual stream is bad.");
    }
  }

  //! Counts the lines in the provided stream and resets to `bof`
  auto CountLinesAndReset(InStream* stream) const -> unsigned int {
    std::string line{};
    unsigned int lines{ 0 };
    while(!stream->eof()) {
      std::getline(*stream, line);
      ++lines;
    }
    stream->clear();
    stream->seekg(0, std::ios::beg);
    return lines;
  }

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
