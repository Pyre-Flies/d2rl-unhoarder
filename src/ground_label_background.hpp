#pragma once
#include <array>
#include <bit>
#include <cstdint>
namespace UnHoarder::GroundLabelBackground {
// Called only after the existing exact native caller, pointer pairing,
// copied color, item identity, rule and name checks have succeeded.
inline bool KnownNativeBlack(const std::array<float,4>& color) noexcept {
    const auto bits=std::bit_cast<std::array<std::uint32_t,4>>(color);
    // Original admitted baseline and the exact Reimagined profile value,
    // corroborated by the native unselected label record on build 93847.
    return bits==std::array<std::uint32_t,4>{0,0,0,0x3f19999a} ||
           bits==std::array<std::uint32_t,4>{0,0,0,0x3f4ccccd};
}
}
