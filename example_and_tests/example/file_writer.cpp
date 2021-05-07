#include "file_writer.hpp"

#include <fstream>

namespace goldtest::example {

auto FileWriter::Execute(const std::string &filename) const -> void {
  std::ofstream file_outstream(filename, std::ofstream::out);
  file_outstream << "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla fermentum sem quis justo auctor, in"
                    "scelerisque nulla consectetur. Vestibulum lorem mi, consequat id ultrices in, congue non leo. "
                    "Fusce id suscipit eros, eget imperdiet nisi. Quisque lobortis semper sodales. Donec lobortis metus"
                    " nulla, sit amet malesuada ligula sollicitudin quis. Aliquam ac gravida lectus, a maximus felis."
                    " Aenean efficitur dui et felis semper porta. Sed nunc tortor, aliquet eu lobortis pellentesque,"
                    " tincidunt non lectus. Cras porta orci ut elit tristique hendrerit. Curabitur id porta mauris,"
                    " venenatis sodales eros. Fusce lorem elit, faucibus nec risus dignissim, fringilla feugiat est."
                    " Nam quis egestas mauris. Quisque blandit enim ipsum, vel porttitor lacus pulvinar eu. In vel"
                    " rutrum justo, cursus pellentesque sem. Mauris fringilla dictum elit, nec accumsan ante"
                    " consectetur id.";
  file_outstream.close();
}

} // namespace goldtest::example
