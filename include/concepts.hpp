#pragma once

#include "type_traits.hpp"

namespace KonaImpl {

// 非空、非引用、非函数类型（未完成）
template <typename _Tp>
constexpr bool is_object_v = KonaImpl::is_object<_Tp>::value;

};  // namespace KonaImpl
