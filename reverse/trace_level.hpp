#ifndef REVERSE_TRACE_LEVEL_HPP_INCLUDED
#define REVERSE_TRACE_LEVEL_HPP_INCLUDED

namespace reverse {

  class trace_level
  {
  public:
    enum values {
      none = 0,
      warn = 10,
      error = 20,
      info = 30,
      debug = 40,
      detail = 50,
      data = 60
    };
  };

} // namespace reverse

#endif // REVERSE_TRACE_LEVEL_HPP_INCLUDED
