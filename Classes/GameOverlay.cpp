//
//  GameOverlay.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 8/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameOverlay.hpp"
#include "FAnimation.hpp"
#include "Game.hpp"

GameOverlay *gGameOverlay = NULL;

GameOverlay::GameOverlay() {
    gGameOverlay = this;
    mName = "[Game Overlay]";
    
    mConsumesTouches = false;
}

GameOverlay::~GameOverlay() {
    
}

void GameOverlay::Layout() {
    
}

void GameOverlay::Update() {
    
    mEffectListBalloonBursts.Update();
    mEffectListDartFadeStar.Update();
    
}

void GameOverlay::Draw() {
    
    //DrawTransform();
    //Graphics::MatrixModelViewReset();
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    //Graphics::SetColor(1.0f, 0.0f, 0.0f, 0.50f);
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    Graphics::SetColor();
    
    //Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mEffectListBalloonBursts.Draw();
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    mEffectListDartFadeStar.Draw();
    
    
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    
    /*
    gWadGameInterface.mFontScoreLarge.Draw("Xa aX0123456789yYzZZzzYaY", 20.0f, 100.0f);
    gWadGameInterface.mFontScoreLarge.Draw("aa 2345BB", 20.0f, 150.0f);
    gWadGameInterface.mFontScoreLarge.Draw("987 65bacaBCACAeE", 20.0f, 200.0f);
    
    gWadGameInterface.mFontScoreSmall.Draw("Xaa X0123456789yYzZZzzYaY", 20.0f, 250.0f);
    gWadGameInterface.mFontScoreSmall.Draw("aa 2345BB", 20.0f, 300.0f);
    gWadGameInterface.mFontScoreSmall.Draw("987 65bacaBCACAeE", 20.0f, 400.0f);
     */
    
    gWadGameInterface.mFontScoreLarge.Right(FString(gGame->mScore), mWidth - 40.0f, 40.0f);
    
    
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    float aWindBarCenter = mWidth2;
    float aWindBarLength = mWidth * 0.9f;
    
    Graphics::SetColor(0.45f, 0.45f, 0.45f, 0.9f);
    Graphics::DrawRect(aWindBarCenter - aWindBarLength / 2.0f, mHeight - 100.0f, aWindBarLength, 50.0f);
    
    float aWindPower = gGame->mWind.mPower;
    float aWindBarWidth = aWindBarLength * aWindPower * 0.5f;
    
    if (aWindPower >= 0.0f) {
        Graphics::SetColor(1.0f, 0.125f, 0.125f, 0.9f);
        Graphics::DrawRect(aWindBarCenter, mHeight - 100.0f, aWindBarWidth, 50.0f);
    } else {
        Graphics::SetColor(1.0f, 0.125f, 0.125f, 0.9f);
        Graphics::DrawRect(aWindBarCenter + aWindBarWidth, mHeight - 100.0f, -aWindBarWidth, 50.0f);
    }
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    
    gWadGameInterface.mPauseButtonUp.Draw(20.0f, 20.0f);
    
    float aPauseWidth = gWadGameInterface.mPauseButtonUp.mWidth;
    float aPauseHeight = gWadGameInterface.mPauseButtonUp.mHeight;
    
    
    gWadGameInterface.mPauseButtonDown.Draw(20.0f + aPauseWidth * 0.75f, 20.0f);
    
    
    
    float aLIWidth = gWadGameInterface.mLivesIndicatorShadow.mWidth;
    gWadGameInterface.mLivesIndicatorShadow.Draw(20.0f + aPauseWidth, 120.0f);
    
    gWadGameInterface.mLivesIndicatorFull.Draw(20.0f + aLIWidth * 0.7f, 20.0f + aPauseHeight);
    gWadGameInterface.mLivesIndicatorFull.Draw(20.0f + aLIWidth * 0.7f * 2, 20.0f + aPauseHeight);
    gWadGameInterface.mLivesIndicatorEmpty.Draw(20.0f + aLIWidth * 0.7f * 3, 20.0f + aPauseHeight);
    gWadGameInterface.mLivesIndicatorEmpty.Draw(20.0f + aLIWidth * 0.7f * 4, 20.0f + aPauseHeight);

    
    
    
}

void GameOverlay::TouchDown(float pX, float pY, void *pData) {
    
}

void GameOverlay::TouchMove(float pX, float pY, void *pData) {
    
}

void GameOverlay::TouchUp(float pX, float pY, void *pData) {
    
}

void GameOverlay::TouchFlush() {
    
}

void GameOverlay::Notify(void *pSender, const char *pNotification) {
    
}
