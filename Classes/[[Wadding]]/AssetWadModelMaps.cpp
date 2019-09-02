//
//  AssetWadModelMaps.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/1/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "AssetWadModelMaps.hpp"
#include "core_includes.h"

AssetWadModelMaps::AssetWadModelMaps() {
    
}

AssetWadModelMaps::~AssetWadModelMaps() {
    
}

void AssetWadModelMaps::Load() {
    
    
    //batdart_color_6_map_scale_2
    //dart_color_4_map_scale_2
    //minidart_color_6_map_scale_2
    //extra_life_map_scale_4
    //turtle_map_scale_2
    //turtle_damaged_map_scale_2
    //turtle_propeller_map_scale_3
    
    //gImageBundler.mA
    gImageBundler.StartBundle("bndl_score_font");
    //mFontScoreLarge.LoadNew("fnt_mh_256_font.kern", "mont_heavy_128_", "0123456789+-.,");
    //mFontScoreSmall.LoadNew("fnt_mh_256_font.kern", "mont_heavy_64_", "0123456789+-.,");
    gImageBundler.EndBundle();
    
    
    
}

void AssetWadModelMaps::Unload() {
    
}

