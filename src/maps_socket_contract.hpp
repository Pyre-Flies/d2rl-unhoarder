#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <initializer_list>
#include "maps_socket_profile.hpp"
namespace UnHoarder::MapsSocket {
enum class Kind {Code,Data,Trampoline};
struct Memory {void* user{};bool (*read)(void*,uintptr_t,void*,size_t,Kind) noexcept{};};
inline bool Relative(uintptr_t end,int32_t delta,uintptr_t& out) noexcept {
    if(delta>=0){if(end>UINTPTR_MAX-static_cast<uintptr_t>(delta))return false;out=end+delta;}
    else {const auto distance=static_cast<uintptr_t>(-static_cast<int64_t>(delta));if(end<distance)return false;out=end-distance;}
    return out!=0;
}
template<size_t N> bool Block(const Memory& memory,uintptr_t at,const unsigned char (&expected)[N],unsigned char (&actual)[N],std::initializer_list<size_t> operands={}) noexcept {
    if(!memory.read || !at || at>UINTPTR_MAX-N || !memory.read(memory.user,at,actual,N,Kind::Code))return false;
    for(size_t i=0;i<N;++i){bool operand=false;for(auto start:operands)operand|=i>=start && i-start<4;if(!operand && actual[i]!=expected[i])return false;}
    return true;
}
inline bool Ref(uintptr_t at,const unsigned char* bytes,size_t operand,size_t end,uintptr_t& out) noexcept {
    if(at>UINTPTR_MAX-end)return false;int32_t delta{};std::memcpy(&delta,bytes+operand,4);return Relative(at+end,delta,out);
}
// Stat 194 - 17 = 177, above the exact unsigned switch bound 110.
// Its JA takes the -1 leaf without reading either switch lookup table.
// Maps then returns the original Core result, including when levelOf is null.
inline bool Validate(const Memory& memory,uintptr_t hook,uintptr_t original) noexcept {
    if(!hook || hook>UINTPTR_MAX-0x83 || !original)return false;
    unsigned char head[sizeof(Profile::Head)]{},gate[sizeof(Profile::Gate)]{},index[sizeof(Profile::Index)]{};
    const auto gateAt=hook+0x83;
    if(!Block(memory,hook,Profile::Head,head,{0x19}) || !Block(memory,gateAt,Profile::Gate,gate,{0x1a,0x27,0x33,0x48}))return false;
    uintptr_t slot{},levelSlot{},continuation{},level{},firstReturn{},secondReturn{},helper{};
    if(!Ref(hook,head,0x19,0x1d,slot) || !Ref(gateAt,gate,0x1a,0x1f,levelSlot) ||
        !Ref(gateAt,gate,0x27,0x2b,firstReturn) || !Ref(gateAt,gate,0x48,0x4c,secondReturn) ||
        firstReturn!=secondReturn || !Ref(gateAt,gate,0x33,0x37,helper) ||
        (slot&7) || (levelSlot&7) || slot==levelSlot ||
        !memory.read(memory.user,slot,&continuation,8,Kind::Data) || continuation!=original ||
        !memory.read(memory.user,levelSlot,&level,8,Kind::Data))return false;
    unsigned char tail[sizeof(Profile::Return)]{},negative[sizeof(Profile::Negative)]{};
    if(!Block(memory,firstReturn,Profile::Return,tail) || !Block(memory,helper,Profile::Index,index,{0x25,0x2d,0x34}))return false;
    // JA at Index+0x1c has end +0x1e and exact positive rel8 0x54.
    if(helper>UINTPTR_MAX-0x72)return false;
    return Block(memory,helper+0x72,Profile::Negative,negative);
}
}
