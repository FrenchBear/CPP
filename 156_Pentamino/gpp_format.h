// gpp_format.h
// A replacement for format.h since g++ doesn't include <format.h> header...
//
// 2022-07-13	PV		To install libfmt on WSL: apt installlibfmt-dev
// 2022-07-22	PV		Make it work on Mac; install fmt with "brew install fmt".  Will create aliases folders after next update

#pragma once

#ifdef __APPLE__
#include "/opt/homebrew/Cellar/fmt/8.1.1_1/include/fmt/format.h"
using namespace fmt;
#else
#include <fmt/format.h>
namespace std
{
   template<typename... Args> \
   inline auto format(Args&&... args) -> decltype(fmt::format(std::forward<Args>(args)...)) \
   { \
      return fmt::format(std::forward<Args>(args)...); \
   }
}
#endif

