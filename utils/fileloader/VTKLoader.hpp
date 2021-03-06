#pragma once

#include <cstdint>

#include "utils/mathfunc/mathfunc.hpp"

//
//tetgenから生成されるfileをロードする
//非構造格子，四面体のみ対応
//

bool LoadVTKtoTetrahedraMesh(
    const char* filename,
    fvec3** const vertdata,
    uint32_t& vertsize,
    uint32_t** const ilistdata,
    uint32_t& ilistsize,
    const fvec3& meshoffset = fvec3(0.0),
    const float& meshscale  = 1.0);
