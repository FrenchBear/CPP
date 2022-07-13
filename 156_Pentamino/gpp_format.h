#include <fmt/format.h>

namespace std
{
   template<typename... Args> \
   inline auto format(Args&&... args) -> decltype(fmt::format(std::forward<Args>(args)...)) \
   { \
      return fmt::format(std::forward<Args>(args)...); \
   }
}
