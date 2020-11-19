#ifndef PLAYGROUND_SEESAW_H
#define PLAYGROUND_SEESAW_H

#include <string> // std::string

namespace playground {

class Seesaw {
  private:
    // +---------+
    // | fields: |
    // +---------+

    std::string _greeting = "Hello from the Seesaw class!";

    int DELETEME = 1;

  public:
    // +-----------------+
    // | public methods: |
    // +-----------------+

    std::string getGreeting();
};

} // namespace playground

#endif // PLAYGROUND_SEESAW_H