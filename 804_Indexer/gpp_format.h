// gpp_format.h
// A replacement for format.h since g++ doesn't include <format.h> header...
//
// 2022-07-13	PV

#include <fmt/format.h>

namespace std
{
   template<typename... Args> \
   inline auto format(Args&&... args) -> decltype(fmt::format(std::forward<Args>(args)...)) \
   { \
      return fmt::format(std::forward<Args>(args)...); \
   }
}
