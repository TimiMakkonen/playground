#ifndef EXTERNAL_LIBRARY_SLIDE_H
#define EXTERNAL_LIBRARY_SLIDE_H

#include <string> // std::string

namespace external_library {

class Slide {
  private:
    // +---------+
    // | fields: |
    // +---------+

    std::string greeting = "Hello from the Slide class!";

  public:
    // +-----------------+
    // | public methods: |
    // +-----------------+

    std::string getGreeting() {
      return this->greeting;
    }
};

} // namespace external_library

#endif // EXTERNAL_LIBRARY_SLIDE_H