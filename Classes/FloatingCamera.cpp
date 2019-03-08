//
//  FloatingCamera.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/15/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FloatingCamera.hpp"
#include "core_includes.h"

FloatingCamera::FloatingCamera() {
    mFOV = M_PI_2;
    
    mAspect = gAppWidth / gAppHeight;
    //mAspect = 1.0f;
    
    mTarget = FVec3(0.0f, 0.0f, 0.0f);
    mDirection = FVec3(0.0f, 1.0f, 0.0f);
    
    mCenterOffset = FVec2(0.0f, 0.0f);
    
    mDistance = 24.0f;
    mRotationPrimary = 0.0f;
    mRotationSecondary = 0.0f;
    
}

FloatingCamera::~FloatingCamera() {
    
}

void FloatingCamera::Print() {
    
    printf("*** BEGIN FloatingCamera ***\n");
    
    printf("mFOV = %f;\n", mFOV);
    
    printf("mTarget = FVec3(%f, %f, %f);\n", mTarget.mX, mTarget.mY, mTarget.mZ);
    printf("mDirection = FVec3(%f, %f, %f);\n", mDirection.mX, mDirection.mY, mDirection.mZ);
    
    printf("mDistance = %f;\n", mDistance);
    printf("mRotationPrimary = %f;\n", mRotationPrimary);
    printf("mRotationSecondary = %f;\n", mRotationSecondary);
    
    printf("*** END FloatingCamera ***\n");
}

FMatrix FloatingCamera::GetProjection() {
    mAspect = gDeviceWidth / gDeviceHeight;
    
    FMatrix aPerspective = FMatrixCreatePerspective(mFOV, mAspect, 0.01f, 255.0f);
    aPerspective.Scale(1.0f, -1.0f, 1.0f);
    
    aPerspective.OffsetPerspectiveCenter(mCenterOffset.mX, mCenterOffset.mY);
    
    
    FVec3 aEye = FVec3(0.0f, 0.0f, 1.0f);
    aEye = Rotate3D(aEye, FVec3(1.0f, 0.0f, 0.0f), mRotationSecondary);
    aEye = Rotate3D(aEye, FVec3(0.0f, 1.0f, 0.0f), mRotationPrimary);
    
    
    
    
    FMatrix aCamera = FMatrixCreateLookAt(aEye.mX * mDistance, aEye.mY * mDistance, aEye.mZ * mDistance,
                                          0.0f, 0.0f, 0.0f,
                                          mDirection.mX, mDirection.mY, mDirection.mZ);
    //
    //
    return FMatrixMultiply(aPerspective, aCamera);
    //
    //return aCamera;
    //
}
