#pragma once

#include "mystlconfig.hpp"
#include "utility.hpp"
#include "type_traits.hpp"

namespace KonaImpl {

// 非空、非引用、非函数类型（未完成）
template <typename _Tp>
inline constexpr bool is_object_v = is_object<_Tp>::value;

};  // namespace KonaImpl
