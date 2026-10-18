#include "src/ground_label_background.hpp"
#include <cstdio>
#include <limits>
#include <bit>
int main(){
    using UnHoarder::GroundLabelBackground::KnownNativeBlack;
    // Exact live amulet record: RGB=0; alpha bits 3F4CCCCD from Reimagined's
    // TooltipStyle.inGameBackgroundColor. This failed the old paint predicate.
    const std::array<float,4> captured{0,0,0,0.8f};
    if(!KnownNativeBlack(captured)){std::puts("FAIL: captured native 80% black background rejected");return 1;}
    if(!KnownNativeBlack({0,0,0,0.6f}))return 2;
    for(float alpha:{0.0f,0.1f,0.5f,0.7f,0.75f,0.82f,1.0f,-1.0f,
        std::numeric_limits<float>::infinity(),std::numeric_limits<float>::quiet_NaN()})
        if(KnownNativeBlack({0,0,0,alpha}))return 3;
    for(auto alphaBits:{0x3f199999u,0x3f19999bu,0x3f4cccccu,0x3f4cccceu})
        if(KnownNativeBlack({0,0,0,std::bit_cast<float>(alphaBits)}))return 4;
    for(float alpha:{0.6f,0.8f})for(unsigned channel=0;channel<3;++channel){
        auto changed=std::array<float,4>{0,0,0,alpha};changed[channel]=0.001f;
        if(KnownNativeBlack(changed))return 5;
    }
    if(KnownNativeBlack({0,0.25f,0.5f,1}))return 6; // native selected blue
    if(KnownNativeBlack({110.f/255,35.f/255,160.f/255,.82f}))return 7; // already styled
    std::puts("Exact 60%/80% native black admitted; unknown alpha, adjacent bits, colors and selected blue refused.");
}
