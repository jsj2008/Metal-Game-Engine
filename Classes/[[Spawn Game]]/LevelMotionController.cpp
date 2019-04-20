//
//  LevelMotionController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/13/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelMotionController.hpp"

//
//  LevelMotionController.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "LevelMotionController.hpp"
#include "LevelSection.hpp"
#include "GameLevelController.hpp"
#include "Game.hpp"
#include "Balloon.hpp"

LevelMotionController::LevelMotionController() {
    mKillTimer = 8;
    
    mTestRotation = 0.0f;
}

LevelMotionController::~LevelMotionController() {
    
}

void LevelMotionController::Reset() {

    
}

void LevelMotionController::Restart() {
    
}


void LevelMotionController::Update() {

    mTestRotation += 1.0f;
    if (mTestRotation >= 360.0f) {
        mTestRotation -= 360.0f;
    }
    
}

void LevelMotionController::Draw() {
    
}

void LevelMotionController::Apply(float pReferenceX, float pReferenceY, GameObject *pObject) {
    
    if (pObject != NULL && pObject->mKill == 0) {
        
        
        FVec2 aPos = FVec2(pObject->mTransform.mX, pObject->mTransform.mY);
        FVec2 aCenter = FVec2(pReferenceX, pReferenceY);
        
        aPos = PivotPoint(aPos, mTestRotation, aCenter);
        
        pObject->mTransform.mX = aPos.mX;
        pObject->mTransform.mY = aPos.mY;
        
        //PivotPoint(<#FVec2 pPoint#>, <#float pDegrees#>, <#FVec2 pCenter#>, <#float pScaleX#>, <#float pScaleY#>)
        
        
        //pObject->mTransform.mY += 60.0f;
        
        
        
        
    }
    
    
    
}



