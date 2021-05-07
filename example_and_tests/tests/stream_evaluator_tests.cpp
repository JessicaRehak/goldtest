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

  // Dependency pointers
  std::shared_ptr<StringStream> gold_string_stream_{ std::make_shared<StringStream>() };
  std::shared_ptr<StringStream> actual_string_stream_{ std::make_shared<StringStream>() };

  auto SetUp() -> void override;
};

auto StreamEvaluatorTests::SetUp() -> void {
  test_evaluator_ = std::make_unique<StreamEvaluator>(actual_string_stream_, gold_string_stream_);
}

TEST_F(StreamEvaluatorTests, DependencyGetters) {
  EXPECT_NE(test_evaluator_->actual_stream(), nullptr);
  EXPECT_NE(test_evaluator_->gold_stream(), nullptr);
}

TEST_F(StreamEvaluatorTests, BadDependencies) {
  EXPECT_ANY_THROW({
                     StreamEvaluator test_evaluator(actual_string_stream_, nullptr);
  });
  EXPECT_ANY_THROW({
                     StreamEvaluator test_evaluator(nullptr, gold_string_stream_);
                   });
  EXPECT_ANY_THROW({
                     StreamEvaluator test_evaluator(nullptr, nullptr);
                   });
}

TEST_F(StreamEvaluatorTests, SameStream) {
  const std::string input_text{ "1\n2\n3\n4\n5" };
  actual_string_stream_->str(input_text);
  gold_string_stream_->str(input_text);
  ASSERT_TRUE(test_evaluator_->Compare());
}

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
