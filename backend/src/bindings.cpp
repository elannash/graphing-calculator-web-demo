#include <emscripten/bind.h>
#include <utility> // For std::pair
#include <vector>  // For std::vector

using namespace emscripten;

// bind std::pair<float, float> for webassembly
EMSCRIPTEN_BINDINGS(std_pair_float_float) {
    emscripten::value_object<std::pair<float, float>>("pair_float_float")
        .field("first", &std::pair<float, float>::first)
        .field("second", &std::pair<float, float>::second);
}

// bind std::vector<std::pair<float, float>> for webassembly
EMSCRIPTEN_BINDINGS(std_vector_of_pair_float_float) {
    emscripten::register_vector<std::pair<float, float>>("vector_pair_float_float");
}
