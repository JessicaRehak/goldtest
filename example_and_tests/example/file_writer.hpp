#ifndef GOLDTEST_EXAMPLE_AND_TESTS_EXAMPLE_FILE_WRITER_HPP_
#define GOLDTEST_EXAMPLE_AND_TESTS_EXAMPLE_FILE_WRITER_HPP_

#include <string>

namespace goldtest::example {

class FileWriter {
 public:
  auto Execute(const std::string& filename) const -> void;
};

} // namespace goldtest::example

#endif //GOLDTEST_EXAMPLE_AND_TESTS_EXAMPLE_FILE_WRITER_HPP_
