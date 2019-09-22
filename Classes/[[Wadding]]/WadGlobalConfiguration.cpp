//
//  WadGlobalConfiguration.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 8/24/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "WadGlobalConfiguration.hpp"
#include "core_includes.h"

WadGlobalConfiguration gWadConfiguration;

WadGlobalConfiguration::WadGlobalConfiguration() {

    mAssetScale = 1;
    mPrevAssetScale = 0;
    
    mSpriteScale = 1;
    mPrevSpriteScale = 0;
    
    mAutoScale = true;
}

WadGlobalConfiguration::~WadGlobalConfiguration() {
    
}

bool WadGlobalConfiguration::ShouldReload() {
    
    if (mSpriteScale != mPrevSpriteScale) { return true; }
    if (mAssetScale != mPrevAssetScale) { return true; }
    
    return false;
    
}

void WadGlobalConfiguration::NotifyReload() {
    mPrevAssetScale = mAssetScale;
    mPrevSpriteScale = mSpriteScale;
}

void WadGlobalConfiguration::NotifyVirtualFrameChange() {
    
    float aScreenWidth = gVirtualDevWidth;
    
    
    //float aCutoff = gVirtualDevHeight * 0.75f;
    //if (aCutoff < aScreenWidth) { aScreenWidth = aCutoff; }
    
    
    
    if (aScreenWidth < 100.0f) { aScreenWidth = 100.0f; }
    
    //TODO: This will be the magic number that determines our scale...
    float aExampleImageWidth = 480.0f;
    //float aExampleImageWidth = 540.0f;
    
    
    float aFactor = (aScreenWidth - 640.0f) / (1412.0 - 640.0f);
    if (aFactor < 0.0f) { aFactor = 0.0f; }
    if (aFactor > 1.0f) { aFactor = 1.0f; }
    
    float aNumer = aScreenWidth + (aExampleImageWidth * 0.5f) + (aExampleImageWidth * 0.5f * aFactor);
    float aExpectScale = aNumer / (aExampleImageWidth);
    
    float aScale = RoundSpriteScale(aExpectScale);
    
    //Log("WadGlobalConfiguration::Expect Scale: %f (%f) VD(%f x %f)\n", aScale, aExpectScale, gVirtualDevWidth, gVirtualDevHeight);
    
    if (mAutoScale) {
        
        mSpriteScale = aScale;
        mAssetScale = os_getAssetScale();
        
        int aThresholdScale = (int)(mSpriteScale + 0.5f);
        if (aThresholdScale < 1) { aThresholdScale = 1; }
        if (aThresholdScale > 4) { aThresholdScale = 4; }
        
        if (mAssetScale < aThresholdScale) {
            mAssetScale = aThresholdScale;
        }
    }
}

void WadGlobalConfiguration::SetAssetScale(int pScale) {
    mAssetScale = pScale;
}

void WadGlobalConfiguration::SetSpriteScale(float pScale) {
    mSpriteScale = RoundSpriteScale(pScale);
}

float WadGlobalConfiguration::RoundSpriteScale(float pScale) {
    
    float aScale = pScale;
    
    if (aScale < 1.0f) {
        aScale = 1.0f;
    } else if (aScale >= 1.0f && aScale < 2.0f) {
        if (aScale >= 1.5f) {
            aScale = 1.5f;
        } else {
            aScale = 1.0f;
        }
    } else if (aScale >= 2.0f && aScale < 3.0f) {
        if (aScale >= 2.5f) {
            aScale = 2.5f;
        } else {
            aScale = 2.0f;
        }
    } else if (aScale >= 3.0f && aScale < 4.0f) {
        if (aScale >= 3.5f) {
            aScale = 3.5f;
        } else {
            aScale = 3.0f;
        }
    } else {
        aScale = 4.0f;
    }
    
    return aScale;
}

void WadGlobalConfiguration::Print() {
    Log("*** BEGIN WadGlobalConfiguration ***\n");
    
    
    
    Log("*** END WadGlobalConfiguration ***\n");
}
