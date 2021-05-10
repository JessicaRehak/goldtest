#include <gtest/gtest.h>

#include "../file_writer.hpp"
#include "../goldtest/goldtest.hpp"

namespace  {

class FileWriterTest : public ::testing::Test {
 public:
  using FileWriter = goldtest::example::FileWriter;
  const std::string filename_{ "test_file" };
};

TEST_F(FileWriterTest, ExecuteTest) {
  FileWriter test_file_writer;
  test_file_writer.Execute(filename_ + ".txt");

  EXPECT_GOLD_FILE_MATCH(filename_ + ".txt", "test_data/" + filename_ + ".gold");
}

} // namespace
