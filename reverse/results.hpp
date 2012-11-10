#ifndef REVERSE_RESULTS_HPP_INCLUDED
#define REVERSE_RESULTS_HPP_INCLUDED

namespace reverse {

    class results {
    public:

      enum values {
	invalid_index = -2,
        failure = -1,
        success = 0
      };

    };

} // namespace reverse

#endif // REVERSE_RESULTS_HPP_INCLUDED
