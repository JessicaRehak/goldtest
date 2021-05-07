#include <gtest/gtest.h>

#include "../file_writer.hpp"

namespace  {

class FileWriterTest : public ::testing::Test {
 public:
  using FileWriter = goldtest::example::FileWriter;
  const std::string filename_{ "test_file.txt" };
};

TEST_F(FileWriterTest, ExecuteTest) {
  FileWriter test_file_writer;
  test_file_writer.Execute(filename_);
}

} // namespace
