#include "../goldtest/gold_stream_evaluator.hpp"

#include <iostream>
#include <memory>

#include <gtest/gtest.h>

namespace  {

class StreamEvaluatorTests : public ::testing::Test {
 public:
  using StringStream = std::istringstream;
  using StreamEvaluator = goldtest::GoldStreamEvaluator;

  std::unique_ptr<StreamEvaluator> test_evaluator_{ nullptr };

  auto SetUp() -> void override;
};

auto StreamEvaluatorTests::SetUp() -> void {
  test_evaluator_ = std::make_unique<StreamEvaluator>(std::make_unique<StringStream>(),
                                                      std::make_unique<StringStream>());
}

TEST_F(StreamEvaluatorTests, DependencyGetters) {
  EXPECT_NE(test_evaluator_->actual_stream(), nullptr);
  EXPECT_NE(test_evaluator_->gold_stream(), nullptr);
}


TEST_F(StreamEvaluatorTests, BadGoldStream) {
  auto actual_string_stream = std::make_unique<StringStream>();
  auto gold_string_stream = std::make_unique<StringStream>();
  actual_string_stream->setstate(std::ios_base::goodbit);
  gold_string_stream->setstate(std::ios_base::badbit);

  StreamEvaluator test_evaluator(std::move(actual_string_stream), std::move(gold_string_stream));

  ASSERT_FALSE(test_evaluator.GoldGood());
  ASSERT_TRUE(test_evaluator.ActualGood());
}

TEST_F(StreamEvaluatorTests, BadActualStream) {
  auto actual_string_stream = std::make_unique<StringStream>();
  auto gold_string_stream = std::make_unique<StringStream>();
  actual_string_stream->setstate(std::ios_base::badbit);
  gold_string_stream->setstate(std::ios_base::goodbit);

  StreamEvaluator test_evaluator(std::move(actual_string_stream), std::move(gold_string_stream));

  ASSERT_TRUE(test_evaluator.GoldGood());
  ASSERT_FALSE(test_evaluator.ActualGood());
}

TEST_F(StreamEvaluatorTests, BadBothStream) {
  auto actual_string_stream = std::make_unique<StringStream>();
  auto gold_string_stream = std::make_unique<StringStream>();
  actual_string_stream->setstate(std::ios_base::badbit);
  gold_string_stream->setstate(std::ios_base::badbit);

  StreamEvaluator test_evaluator(std::move(actual_string_stream), std::move(gold_string_stream));

  ASSERT_FALSE(test_evaluator.GoldGood());
  ASSERT_FALSE(test_evaluator.ActualGood());
}

//TEST_F(StreamEvaluatorTests, SameStream) {
//  std::string input_text = "1\n2\n3\n4\n5";
//  gold_iss->str(input_text);
//  actual_iss->str(input_text);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_TRUE(test_eval.Compare());
//}
//
//TEST_F(StreamEvaluatorTests, DiffStream) {
//  std::string gold_text = "1\n2\n3\n4\n5";
//  std::string actual_text = "1\n2\nX\n4\n5";
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_FALSE(test_eval.Compare());
//}
//
//TEST_F(StreamEvaluatorTests, BadGoldStreamCompare) {
//  actual_iss->setstate(std::ios_base::goodbit);
//  gold_iss->setstate(std::ios_base::badbit);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_THROW(test_eval.Compare(), std::runtime_error);
//}
//
//TEST_F(StreamEvaluatorTests, BadActualStreamCompare) {
//  gold_iss->setstate(std::ios_base::goodbit);
//  actual_iss->setstate(std::ios_base::badbit);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_THROW(test_eval.Compare(), std::runtime_error);
//}
//
//TEST_F(StreamEvaluatorTests, CompareLongerGold) {
//  std::string gold_text = "1\n2\n3\n4\n5";
//  std::string actual_text = "1\n2\n3\n4";
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_FALSE(test_eval.Compare());
//}
//
//TEST_F(StreamEvaluatorTests, CompareLongerActual) {
//  std::string gold_text = "1\n2\n3\n4";
//  std::string actual_text = "1\n2\n3\n4\n5";
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_FALSE(test_eval.Compare());
//}
//
//TEST_F(StreamEvaluatorTests, DiffWorks) {
//  std::string gold_text = "1\n2\nX\n4";
//  std::string actual_text = "1\n2\n3\n4";
//  std::string diff;
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  diff = test_eval.GetDiff();
//  ASSERT_EQ(diff, "@@ -1,4 +1,4 @@\n 1\n 2\n-X\n+3\n 4\n");
//}
//
//TEST_F(StreamEvaluatorTests, DiffWorksSame) {
//  std::string gold_text = "1\n2\n3\n4";
//  std::string actual_text = "1\n2\n3\n4";
//  std::string diff;
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  diff = test_eval.GetDiff();
//  ASSERT_EQ(diff, "");
//}
//
//TEST_F(StreamEvaluatorTests, BadGoldStreamDiff) {
//  actual_iss->setstate(std::ios_base::goodbit);
//  gold_iss->setstate(std::ios_base::badbit);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_THROW(test_eval.GetDiff(), std::runtime_error);
//}
//
//TEST_F(StreamEvaluatorTests, BadActualStreamDiff) {
//  gold_iss->setstate(std::ios_base::goodbit);
//  actual_iss->setstate(std::ios_base::badbit);
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_THROW(test_eval.GetDiff(), std::runtime_error);
//}
//
//TEST_F(StreamEvaluatorTests, RunGoldTestFail) {
//  std::string gold_text = "1\n2\nX\n4";
//  std::string actual_text = "1\n2\n3\n4";
//  std::string diff;
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_FALSE(test_eval.RunGoldTest());
//}
//
//TEST_F(StreamEvaluatorTests, RunGoldTestPass) {
//  std::string gold_text = "1\n2\n3\n4";
//  std::string actual_text = "1\n2\n3\n4";
//  std::string diff;
//  gold_iss->str(gold_text);
//  actual_iss->str(actual_text);
//
//  test_helpers::GoldStreamEvaluator test_eval(std::move(gold_iss),
//                                              std::move(actual_iss));
//  ASSERT_TRUE(test_eval.RunGoldTest());
//}


} // namespace
