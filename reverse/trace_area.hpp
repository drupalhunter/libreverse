#ifndef REVERSE_TRACE_AREA_HPP_INCLUDED
#define REVERSE_TRACE_AREA_HPP_INCLUDED

namespace reverse {

  class trace_area {
  public:

    enum values {
      none = 0x0,
      io = 0x1,
      components = 0x2,
      infrastructure = 0x4,
      data_containers = 0x8,
      errors = 0x10,
      meta = 0x20,
      api = 0x40,
      error_handling = 0x80,
      classifier = 0x100,
      grnn = 0x200,
      grnn_data = 0x400,
      grnn_parser = 0x800,
      candidate_solution = 0x1000,
      grnn_optimizer = 0x2000,
      instruction_decoder = 0x4000,
      all = 0x7fff
    };

  };

} // namespace reverse

#endif // REVERSE_TRACE_AREA_HPP
