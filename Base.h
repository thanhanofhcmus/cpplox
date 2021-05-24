#include <string>
#include <optional>
#include <variant>
#include <cassert>

#define cref const&

using Number = double;
using String = std::string;
using Literal = std::optional<std::variant<Number, String>>;