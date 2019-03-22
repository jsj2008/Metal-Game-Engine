//
//  GameEditorEditor.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/17/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "GameEditor.hpp"
#include "FAnimation.h"

GameEditor *gEditor = NULL;

GameEditor::GameEditor(Game *pGame) {
    
    
    mMenuSpawn = NULL;
    
    gEditor = this;
    mGame = pGame;
    
    mName = "[GameEditor]";
    gEditor = this;
    
    SetWidth(gDeviceWidth);
    SetHeight(gDeviceHeight);
    
    mOverlay = NULL;
    
    
    mPathEditor = NULL;
    
    mToolContainer = new FCanvas();
    mToolContainer->mConsumesTouches = false;
    mToolContainer->mName = "Tool Container";
    AddChild(mToolContainer);
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    
    
    mMenuSections = new EditorMenuSections(this);
    mToolContainer->AddChild(mMenuSections);
    mMenuSections->SetFrame(gSafeAreaInsetLeft + 16.0f, gSafeAreaInsetTop + 20.0f, 400.0f, 640.0f);
    
    mExportIndex = 0;
    
    SetOverlay(mToolContainer);
    
    
    
    //WaveAdd();
    //OpenPathEditor();
}

GameEditor::~GameEditor() {
    if (gEditor == this) {
        gEditor = NULL;
    }
}




void GameEditor::Layout() {
    
    mToolContainer->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    if (mPathEditor) mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    
    FPoint aSpawnZone1 = FPoint(gGame->mSpawnZoneLeft, gGame->mSpawnZoneTop);
    aSpawnZone1 = FCanvas::Convert(aSpawnZone1, gGame, this);
    FPoint aSpawnZone2 = FPoint(gGame->mSpawnZoneRight, gGame->mSpawnZoneBottom);
    aSpawnZone2 = FCanvas::Convert(aSpawnZone2, gGame, this);
    mSpawnZoneTop = aSpawnZone1.mY;
    mSpawnZoneRight = aSpawnZone2.mX;
    mSpawnZoneLeft = aSpawnZone1.mX;
    mSpawnZoneBottom = aSpawnZone2.mY;
    
    
    FPoint aPeekZone1 = FPoint(gGame->mPeekZoneLeft, gGame->mPeekZoneTop);
    aPeekZone1 = FCanvas::Convert(aPeekZone1, gGame, this);
    FPoint aPeekZone2 = FPoint(gGame->mPeekZoneRight, 0.0f);
    aPeekZone2 = FCanvas::Convert(aPeekZone2, gGame, this);
    mPeekZoneTop = aPeekZone1.mY;
    mPeekZoneRight = aPeekZone2.mX;
    mPeekZoneLeft = aPeekZone1.mX;
    
    FPoint aQuarterZone1 = FPoint(gGame->mQuarterZoneLeft, gGame->mQuarterZoneTop);
    aQuarterZone1 = FCanvas::Convert(aQuarterZone1, gGame, this);
    FPoint aQuarterZone2 = FPoint(gGame->mQuarterZoneRight, gGame->mQuarterZoneBottom);
    aQuarterZone2 = FCanvas::Convert(aQuarterZone2, gGame, this);
    mQuarterZoneTop = aQuarterZone1.mY;
    mQuarterZoneRight = aQuarterZone2.mX;
    mQuarterZoneLeft = aQuarterZone1.mX;
    mQuarterZoneBottom = aQuarterZone2.mY;
    
    
    FPoint aExitZone1 = FPoint(gGame->mExitZoneLeft, gGame->mExitZoneTop);
    aExitZone1 = FCanvas::Convert(aExitZone1, gGame, this);
    FPoint aExitZone2 = FPoint(gGame->mExitZoneRight, 0.0f);
    aExitZone2 = FCanvas::Convert(aExitZone2, gGame, this);
    mExitZoneTop = aExitZone1.mY;
    mExitZoneRight = aExitZone2.mX;
    mExitZoneLeft = aExitZone1.mX;
    
    
    FPoint aPlayZone1 = FPoint(0.0f, gGame->mPlayAreaBottom);
    aPlayZone1 = FCanvas::Convert(aPlayZone1, gGame, this);
    mPlayZoneBottom = aPlayZone1.mY;
    

    FPoint aGameArea1 = FPoint(gGame->mGameAreaLeft, gGame->mGameAreaTop);
    aGameArea1 = FCanvas::Convert(aGameArea1, gGame, this);
    FPoint aGameArea2 = FPoint(gGame->mGameAreaRight, gGame->mGameAreaBottom);
    aGameArea2 = FCanvas::Convert(aGameArea2, gGame, this);
    mGameAreaTop = aGameArea1.mY;
    mGameAreaRight = aGameArea2.mX;
    mGameAreaLeft = aGameArea1.mX;
    mGameAreaBottom = aGameArea2.mY;
    
    
    
    FPoint aCenter = FPoint((gGame->mPlayAreaLeft + gGame->mPlayAreaRight) / 2.0f,
                            (gGame->mPlayAreaTop + gGame->mPlayAreaBottom) / 2.0f);
    aCenter = FCanvas::Convert(aCenter, gGame, this);
    mCenterH = aCenter.mX;
    mCenterV = aCenter.mY;
    
    
    
    
    
    
    
}

void GameEditor::Update() {
    
}

void GameEditor::Draw() {
    
    //Graphics::PipelineStateSetShape2DAlphaBlending();
    //Graphics::SetColor();
    //Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    

    Graphics::PipelineStateSetShape2DAlphaBlending();
    
    
    float aMarkerMult = 0.75f;
    float aMarkerOpacity = 0.4f;
    
    Graphics::SetColor(0.125f * aMarkerMult, 1.0f * aMarkerMult, 0.056f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneTop);
    Graphics::DrawLine(mSpawnZoneLeft, mSpawnZoneTop, mSpawnZoneLeft, mSpawnZoneBottom);
    Graphics::DrawLine(mSpawnZoneRight, mSpawnZoneTop, mSpawnZoneRight, mSpawnZoneBottom);
    
    Graphics::SetColor(0.65f * aMarkerMult, 0.65f * aMarkerMult, 0.105f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mPeekZoneLeft, mPeekZoneTop, mPeekZoneRight, mPeekZoneTop);
    Graphics::DrawLine(mPeekZoneLeft, mPeekZoneTop, mPeekZoneLeft, mPlayZoneBottom);
    Graphics::DrawLine(mPeekZoneRight, mPeekZoneTop, mPeekZoneRight, mPlayZoneBottom);
    
    Graphics::SetColor(0.125f * aMarkerMult, 0.125f * aMarkerMult, 0.85f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mCenterH, mSpawnZoneTop, mCenterH, mSpawnZoneBottom);
    Graphics::DrawLine(mSpawnZoneLeft, mCenterV, mSpawnZoneRight, mCenterV);
    
    Graphics::SetColor(0.125f * aMarkerMult, 0.125f * aMarkerMult, 0.65f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneTop, mQuarterZoneRight, mQuarterZoneTop);
    Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneBottom, mQuarterZoneRight, mQuarterZoneBottom);
    Graphics::DrawLine(mQuarterZoneLeft, mQuarterZoneTop, mQuarterZoneLeft, mQuarterZoneBottom);
    Graphics::DrawLine(mQuarterZoneRight, mQuarterZoneTop, mQuarterZoneRight, mQuarterZoneBottom);
    
    Graphics::SetColor(0.55f * aMarkerMult, 0.05f * aMarkerMult, 0.05f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mExitZoneLeft, mExitZoneTop, mExitZoneRight, mExitZoneTop);
    Graphics::DrawLine(mExitZoneLeft, mExitZoneTop, mExitZoneLeft, mPlayZoneBottom);
    Graphics::DrawLine(mExitZoneRight, mExitZoneTop, mExitZoneRight, mPlayZoneBottom);
    
    Graphics::SetColor(0.15f * aMarkerMult, 0.15f * aMarkerMult, 0.15f * aMarkerMult, aMarkerOpacity);
    Graphics::DrawLine(mGameAreaLeft, mGameAreaTop, mGameAreaRight, mGameAreaTop);
    Graphics::DrawLine(mGameAreaLeft, mGameAreaBottom, mGameAreaRight, mGameAreaBottom);
    Graphics::DrawLine(mGameAreaLeft, mGameAreaTop, mGameAreaLeft, mGameAreaBottom);
    Graphics::DrawLine(mGameAreaRight, mGameAreaTop, mGameAreaRight, mGameAreaBottom);
    
    
    
    Graphics::SetColor();
    
    
    mSection.Draw();
    
    
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor();
    FString aExportString = FString("Export: ") + FString(mExportIndex);
    gApp->mSysFontBold.Center(aExportString.c(), gDeviceWidth2, gSafeAreaInsetTop + 20.0f, 0.5f);
}

void GameEditor::TouchDown(float pX, float pY, void *pData) {

    SelectClosestObject(pX, pY);
    
    
}

void GameEditor::TouchMove(float pX, float pY, void *pData) {
    
}

void GameEditor::TouchUp(float pX, float pY, void *pData) {

    
}

void GameEditor::TouchFlush() {
    
}

void GameEditor::KeyDown(int pKey) {
    
    if (mPathEditor != NULL) {
        if (mOverlay == mPathEditor) {
            printf("Preventing Editor Key, Overlay Has Ownership\n");
            return;
        }
    }
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (pKey == __KEY__0) { mExportIndex = 0; }
    if (pKey == __KEY__1) { mExportIndex = 1; }
    if (pKey == __KEY__2) { mExportIndex = 2; }
    if (pKey == __KEY__3) { mExportIndex = 3; }
    if (pKey == __KEY__4) { mExportIndex = 4; }
    if (pKey == __KEY__5) { mExportIndex = 5; }
    if (pKey == __KEY__6) { mExportIndex = 6; }
    if (pKey == __KEY__7) { mExportIndex = 7; }
    if (pKey == __KEY__8) { mExportIndex = 8; }
    if (pKey == __KEY__9) { mExportIndex = 9; }
    
    if (pKey == __KEY__S) {
        if (aShift == false && aCtrl == true && aAlt == false) { SaveAt(mExportIndex); }
    }
    
    if (pKey == __KEY__L) {
        if (aShift == false && aCtrl == true && aAlt == false) { LoadAt(mExportIndex); }
    }
    
    
    
    if (pKey == __KEY__P) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mSection.WaveSelectPrev();
        }
    }
    if (pKey == __KEY__N) {
        if (aShift == false && aCtrl == false && aAlt == false) {
            mSection.WaveSelectNext();
        }
    }
}

void GameEditor::KeyUp(int pKey) {
    
    if (pKey == __KEY__W) {
        
    }
    
}

void GameEditor::Notify(void *pSender, const char *pNotification) {
    if (FString("slider_update") == pNotification) {
        
    }
    if (FString("button_click") == pNotification) {

        
    }
}


int GameEditor::ClosestXConstraint(float pX) {
    int aResult = X_CONSTRAINT_LEFT_EXIT;
    float aBestDist = fabsf(mExitZoneLeft - pX);
    float aDist = fabsf(mSpawnZoneLeft - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_LEFT_SPAWN; }
    aDist = fabsf(mPeekZoneLeft - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_LEFT_PEEK; }
    aDist = fabsf(mQuarterZoneLeft - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_LEFT_QUARTER; }
    aDist = fabsf(mCenterH - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_CENTER; }
    aDist = fabsf(mQuarterZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_QUARTER; }
    aDist = fabsf(mPeekZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_PEEK; }
    aDist = fabsf(mSpawnZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_SPAWN; }
    aDist = fabsf(mExitZoneRight - pX);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = X_CONSTRAINT_RIGHT_EXIT; }
    return aResult;
}

int GameEditor::ClosestYConstraint(float pY) {
    int aResult = Y_CONSTRAINT_TOP_EXIT;
    float aBestDist = fabsf(mExitZoneTop - pY);
    float aDist = fabsf(mSpawnZoneTop - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_TOP_SPAWN; }
    aDist = fabsf(mPeekZoneTop - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_TOP_PEEK; }
    aDist = fabsf(mQuarterZoneTop - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_TOP_QUARTER; }
    aDist = fabsf(mCenterV - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_CENTER; }
    aDist = fabsf(mQuarterZoneBottom - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_BOTTOM_QUARTER; }
    aDist = fabsf(mPlayZoneBottom - pY);
    if (aDist < aBestDist) { aBestDist = aDist; aResult = Y_CONSTRAINT_BOTTOM; }
    return aResult;
}

int GameEditor::NextXConstraintf(float pX) {
    return NextXConstraint(ClosestXConstraint(pX));
}

int GameEditor::PrevXConstraintf(float pX) {
    return PrevXConstraint(ClosestXConstraint(pX));
}

int GameEditor::NextYConstraintf(float pY) {
    return NextYConstraint(ClosestYConstraint(pY));
}

int GameEditor::PrevYConstraintf(float pY) {
    return PrevYConstraint(ClosestYConstraint(pY));
}

int GameEditor::NextXConstraint(int pConstraint) {
    if (pConstraint == X_CONSTRAINT_RIGHT_EXIT || pConstraint == X_CONSTRAINT_RIGHT_SPAWN) { return X_CONSTRAINT_RIGHT_EXIT; }
    if (pConstraint == X_CONSTRAINT_RIGHT_PEEK) { return X_CONSTRAINT_RIGHT_SPAWN; }
    if (pConstraint == X_CONSTRAINT_RIGHT_QUARTER) { return X_CONSTRAINT_RIGHT_PEEK; }
    if (pConstraint == X_CONSTRAINT_CENTER) { return X_CONSTRAINT_RIGHT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_LEFT_QUARTER) { return X_CONSTRAINT_CENTER; }
    if (pConstraint == X_CONSTRAINT_LEFT_PEEK) { return X_CONSTRAINT_LEFT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_LEFT_SPAWN) { return X_CONSTRAINT_LEFT_PEEK; }
    if (pConstraint == X_CONSTRAINT_LEFT_EXIT) { return X_CONSTRAINT_LEFT_SPAWN; }
    return X_CONSTRAINT_LEFT_EXIT;
}

int GameEditor::PrevXConstraint(int pConstraint) {
    if (pConstraint == X_CONSTRAINT_LEFT_EXIT || pConstraint == X_CONSTRAINT_LEFT_SPAWN) { return X_CONSTRAINT_LEFT_EXIT; }
    if (pConstraint == X_CONSTRAINT_LEFT_PEEK) { return X_CONSTRAINT_LEFT_SPAWN; }
    if (pConstraint == X_CONSTRAINT_LEFT_QUARTER) { return X_CONSTRAINT_LEFT_PEEK; }
    if (pConstraint == X_CONSTRAINT_CENTER) { return X_CONSTRAINT_LEFT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_QUARTER) { return X_CONSTRAINT_CENTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_PEEK) { return X_CONSTRAINT_RIGHT_QUARTER; }
    if (pConstraint == X_CONSTRAINT_RIGHT_SPAWN) { return X_CONSTRAINT_RIGHT_PEEK; }
    if (pConstraint == X_CONSTRAINT_RIGHT_EXIT) { return X_CONSTRAINT_RIGHT_SPAWN; }
    return X_CONSTRAINT_RIGHT_EXIT;
}

int GameEditor::NextYConstraint(int pConstraint) {
    if (pConstraint == Y_CONSTRAINT_BOTTOM || pConstraint == Y_CONSTRAINT_BOTTOM_QUARTER) { return Y_CONSTRAINT_BOTTOM; }
    if (pConstraint == Y_CONSTRAINT_BOTTOM_QUARTER) { return Y_CONSTRAINT_BOTTOM; }
    if (pConstraint == Y_CONSTRAINT_CENTER) { return Y_CONSTRAINT_BOTTOM_QUARTER; }
    if (pConstraint == Y_CONSTRAINT_TOP_QUARTER) { return Y_CONSTRAINT_CENTER; }
    if (pConstraint == Y_CONSTRAINT_TOP_PEEK) { return Y_CONSTRAINT_TOP_QUARTER; }
    if (pConstraint == Y_CONSTRAINT_TOP_SPAWN) { return Y_CONSTRAINT_TOP_PEEK; }
    if (pConstraint == Y_CONSTRAINT_TOP_EXIT) { return Y_CONSTRAINT_TOP_SPAWN; }
    return Y_CONSTRAINT_TOP_EXIT;
}

int GameEditor::PrevYConstraint(int pConstraint) {
    if (pConstraint == Y_CONSTRAINT_TOP_EXIT || pConstraint == Y_CONSTRAINT_TOP_SPAWN) { return Y_CONSTRAINT_TOP_EXIT; }
    if (pConstraint == Y_CONSTRAINT_TOP_PEEK) { return Y_CONSTRAINT_TOP_SPAWN; }
    if (pConstraint == Y_CONSTRAINT_TOP_QUARTER) { return Y_CONSTRAINT_TOP_PEEK; }
    if (pConstraint == Y_CONSTRAINT_CENTER) { return Y_CONSTRAINT_TOP_QUARTER; }
    if (pConstraint == Y_CONSTRAINT_BOTTOM_QUARTER) { return Y_CONSTRAINT_CENTER; }
    if (pConstraint == Y_CONSTRAINT_BOTTOM) { return Y_CONSTRAINT_BOTTOM_QUARTER; }
    return Y_CONSTRAINT_BOTTOM;
}


void GameEditor::SetOverlay(FCanvas *pCanvas) {
    
    if (mOverlay) {
        if (mOverlay == pCanvas) {
            return;
        }
        
        mOverlay->Deactivate();
        mOverlay = NULL;
        //mOverlay->
    }
    if (pCanvas) {
        mOverlay = pCanvas;
        mOverlay->Activate();
    }
    
}

void GameEditor::WaveAdd() {
    
    mSection.WaveAdd();
    OpenPathEditor();
}

void GameEditor::WaveRemove() {
    mSection.WaveRemove();
}

void GameEditor::WaveSelectNext() {
    mSection.WaveSelectNext();
}

void GameEditor::WaveSelectPrev() {
    mSection.WaveSelectPrev();
}

void GameEditor::WaveDeselect() {
    mSection.WaveDeselect();
}

void GameEditor::OpenPathEditor() {
    if (mSection.mCurrentWave == NULL) { printf("Must have wave...\n"); return; }
    mPathEditor = new GamePathEditor(this);
    mPathEditor->SetFrame(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    mPathEditor->mName = "{Path Editor}";
    AddChild(mPathEditor);
    mPathEditor->SetUp(mSection.mCurrentWave);
    SetOverlay(mPathEditor);
}

void GameEditor::OpenSpawnMenu() {
    
    if (mMenuSpawn == NULL) {
        mMenuSpawn = new EditorMenuSpawn(this);
        mToolContainer->AddChild(mMenuSpawn);
        mMenuSpawn->SetFrame(gDeviceWidth - (gSafeAreaInsetRight + 14.0f + 400.0f), gSafeAreaInsetTop + 20.0f, 400.0f, 480.0f);
    }
}

void GameEditor::ClosePathEditor() {
    SetOverlay(mToolContainer);
    if (mPathEditor) {
        mPathEditor->Kill();
        mPathEditor = NULL;
    }
}

void GameEditor::Clear() {
    FString aRecoverPath = gDirDocuments + FString("clear_backup.json");
    Save(aRecoverPath.c());
    
    ClosePathEditor();
    mSection.Clear();
    
#ifdef EDITOR_MODE
    gGame->mEditorPath.Reset();
#endif
}

void GameEditor::LoadCleared() {
    FString aRecoverPath = gDirDocuments + FString("clear_backup.json");
    Load(aRecoverPath.c());
}

void GameEditor::Autosave() {
    
}

void GameEditor::SelectClosestObject(float pX, float pY) {
    
    LevelWaveBlueprint *aClosestWave = NULL;
    float aClosestWaveDist = 80.0f * 80.0f;
        for (int i=mSection.mWaveList.mCount - 1;i>=0;i--) {
            LevelWaveBlueprint *aWave = (LevelWaveBlueprint *)mSection.mWaveList[i];
            float aDist = 80.0f * 80.0f;
            int aIndex = aWave->mPath.GetClosestIndex(pX, pY, aDist);
            if (aIndex != -1) {
                if (aDist < aClosestWaveDist) {
                    aClosestWaveDist = aDist;
                    aClosestWave = aWave;
                }
            }
        }
    if (aClosestWave) {
        mSection.mCurrentWave = aClosestWave;
        aClosestWave->ApplyEditorConstraints();
    } else {
        mSection.mCurrentWave = NULL;
#ifdef EDITOR_MODE
        gGame->mEditorPath.Reset();
#endif
    }
}


void GameEditor::SaveAt(int pIndex) {
    printf("Save at: %d\n", pIndex);
    
    FString aPath = gDirExport + FString("export_section_") + FString(pIndex) + FString(".json");
    Save(aPath.c());
    
}

void GameEditor::LoadAt(int pIndex) {
    printf("Load at: %d\n", pIndex);
    FString aPath = gDirExport + FString("export_section_") + FString(pIndex) + FString(".json");
    Load(aPath.c());
    
}

void GameEditor::Save(const char *pFile) {
    printf("Save [%s]\n", pFile);
    
    
    FJSON aJSON;
    aJSON.mRoot = mSection.Save();
    aJSON.Save(pFile);
    aJSON.Print();
}

void GameEditor::Load(const char *pFile) {
    
    ClosePathEditor();
    
#ifdef EDITOR_MODE
    gGame->mEditorPath.Reset();
#endif
    
    printf("Load [%s]\n", pFile);
    FJSON aJSON;
    printf("Load...\n");
    aJSON.Load(pFile);
    printf("Print...\n");
    aJSON.Print();
    
    
    mSection.Load(aJSON.mRoot);
}

