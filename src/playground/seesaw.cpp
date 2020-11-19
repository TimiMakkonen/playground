#include <string> // std::string

#include <slide.hpp> // external_library::Slide

#include <playground/seesaw.h>

namespace playground {

// +----------+
// | methods: |
// +----------+

std::string Seesaw::getGreeting() {
    external_library::Slide slide;
    return this->_greeting;
}

} // namespace playground