//
//  DiffuseConfiguration.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 3/25/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "DiffuseConfiguration.hpp"

//
//  DiffuseConfiguration.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "DiffuseConfiguration.hpp"
#include "core_includes.h"

DiffuseConfiguration::DiffuseConfiguration() {
    
    mDirectionRotationPrimary = 30.0f;
    mDirectionRotationSecondary = 225.0f;
    
    mUniform.mLight.mAmbientIntensity = 0.05f;
    mUniform.mLight.mDiffuseIntensity = 0.15f;
    
    mUniform.mLight.mRed = 1.000000;
    mUniform.mLight.mGreen = 1.000000;
    mUniform.mLight.mBlue = 1.000000;
    
    //mUniform.mLight.mAmbientIntensity = 0.0f;
    //mUniform.mLight.mDiffuseIntensity = 0.0f;
    //mUniform.mLight.mSpecularIntensity = 1.000000;
    
}

DiffuseConfiguration::~DiffuseConfiguration() {
    
}

void DiffuseConfiguration::Print() {
    
    Log("**** BEGIN DiffuseConfiguration... ***\n");
    
    Log("mDirectionRotationPrimary = %f;\n", mDirectionRotationPrimary);
    Log("mDirectionRotationSecondary = %f;\n", mDirectionRotationSecondary);
    
    
    mUniform.Print();
    
    Log("**** END DiffuseConfiguration... ***\n");
    
}

void DiffuseConfiguration::Compute() {
    //
    FVec3 aDir = FVec3(0.0f, 0.0f, 1.0f);
    aDir = Rotate3D(aDir, FVec3(1.0f, 0.0f, 0.0f), mDirectionRotationSecondary);
    aDir = Rotate3D(aDir, FVec3(0.0f, 1.0f, 0.0f), mDirectionRotationPrimary);
    
    mUniform.mLight.mDirX = aDir.mX;
    mUniform.mLight.mDirY = aDir.mY;
    mUniform.mLight.mDirZ = aDir.mZ;
}


