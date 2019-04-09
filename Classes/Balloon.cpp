//
//  Balloon.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/14/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "Balloon.hpp"
#include "Game.hpp"

Balloon::Balloon() {
    
    mGameObjectType = GAME_OBJECT_TYPE_BALLOON;
    
    mSpinSpeed = gRand.GetFloat(0.25f, 0.45f);
    if (gRand.GetBool()) mSpinSpeed = -mSpinSpeed;
    
    mModel = &gApp->mBalloon;
    mSprite = &gApp->mBalloonMap[gRand.Get(5)];
    mUniform = &(gGame->mRenderer->mUniformPhongBalloon);
    
    mVelX = 0.0f;
    mVelY = 0.0f;
}

Balloon::~Balloon() {
    //Log("Balloon has died [%LX]\n", this);
}

void Balloon::Update() {
    
    GameObject::Update();
    
    mTransform3D.mSpin += mSpinSpeed;
    
    if (mFloatAway == false) {
        mTransform.mX += mVelX;
        mTransform.mY += mVelY;
    }
    
}

void Balloon::Draw() {
    
    GameObject::Draw();
    
    //Graphics::PipelineStateSetShape2DNoBlending();
    //Graphics::SetColor(1.0f, 0.25f, 0.25f, 0.35f);
    //Graphics::DrawPoint(mTransform.mX, mTransform.mY);
    
}

void Balloon::Draw3D() {
    
    
    //aNormal.SetNormalMatrix(aModelView);
    //((FUniformsLightPhong *)mUniform)->mLight.mShininess = 58.0f;
    //((FUniformsLightPhong *)mUniform)->mLight.mSpecularIntensity = 1.0f;
    
    GameObject::Draw3D();
}
