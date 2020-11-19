#ifndef PLAYGROUND_SEESAW_H
#define PLAYGROUND_SEESAW_H

#include <string> // std::string

#include <slide.hpp> // external_library::Slide

namespace playground {

class Seesaw {
  private:
    // +---------+
    // | fields: |
    // +---------+

    std::string _greeting = "Hello from the Seesaw class!";
    
    external_library::Slide _externalSlide;

  public:
    // +-----------------+
    // | public methods: |
    // +-----------------+

    std::string getGreeting();
};

} // namespace playground

#endif // PLAYGROUND_SEESAW_H