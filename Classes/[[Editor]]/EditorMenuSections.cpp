//
//  EditorMenuSections.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/18/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "EditorMenuSections.hpp"
#include "LightConfigurationScene.hpp"
#include "EditorMenuSections.hpp"
#include "GameEditor.hpp"
#include "FApp.hpp"

EditorMenuSections::EditorMenuSections(GameEditor *pEditor) : ToolMenu() {
    mName = "EditorMenuSections";
    
    mEditor = pEditor;
    
    
    SetTitle("Section");
    SetScrollMode(true);
    
    mRowMain1 = new ToolMenuSectionRow();
    AddSection(mRowMain1);
    
    mButtonNewSection = new UIButton();
    mButtonNewSection->SetText("New Section");
    mRowMain1->AddButton(mButtonNewSection);
    
    mButtonSaveSection = new UIButton();
    mButtonSaveSection->SetText("Save..");
    mRowMain1->AddButton(mButtonSaveSection);
    
    mButtonLoadSection = new UIButton();
    mButtonLoadSection->SetText("Load..");
    mRowMain1->AddButton(mButtonLoadSection);
    
    mRowMain2 = new ToolMenuSectionRow();
    AddSection(mRowMain2);
    
    
    mButtonClear = new UIButton();
    mButtonClear->SetText("Clear");
    mRowMain2->AddButton(mButtonClear);
    
    mButtonLoadCleared = new UIButton();
    mButtonLoadCleared->SetText("Undo Clear");
    mRowMain2->AddButton(mButtonLoadCleared);
    
    
    mMenusPanel = new ToolMenuPanel();
    mMenusPanel->SetTitle("Menus...");
    AddSection(mMenusPanel);
    
    mRowMenus1 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus1);
    
    
    mButtonShowSpawn = new UIButton();
    mButtonShowSpawn->SetText("Spawn");
    mRowMenus1->AddButton(mButtonShowSpawn);
    
    mButtonShowWavePicker = new UIButton();
    mButtonShowWavePicker->SetText("Wave Picker");
    mRowMenus1->AddButton(mButtonShowWavePicker);
    
    mRowMenus2 = new ToolMenuSectionRow();
    mMenusPanel->AddSection(mRowMenus2);
    
    
    mWavePanel = new ToolMenuPanel();
    mWavePanel->SetTitle("Wave Panel");
    AddSection(mWavePanel);
    
    mRowWave1 = new ToolMenuSectionRow();
    mWavePanel->AddSection(mRowWave1);
    
    
    mButtonAddWave = new UIButton();
    mButtonAddWave->SetText("Add Wave");
    mRowWave1->AddButton(mButtonAddWave);
    
    mButtonDeleteWave = new UIButton();
    mButtonDeleteWave->SetText("Delete Wave");
    mRowWave1->AddButton(mButtonDeleteWave);
    
    mButtonSelectNextWave = new UIButton();
    mButtonSelectNextWave->SetText("Next");
    mRowWave1->AddButton(mButtonSelectNextWave);
    
    mButtonSelectPreviousWave = new UIButton();
    mButtonSelectPreviousWave->SetText("Prev");
    mRowWave1->AddButton(mButtonSelectPreviousWave);
    
    
    mRowWave2 = new ToolMenuSectionRow();
    mWavePanel->AddSection(mRowWave2);
    
    
    mCheckBoxPreview = new UICheckBox();
    mCheckBoxPreview->SetText("References");
    mRowWave2->AddCheckBox(mCheckBoxPreview);
    
    mButtonMoveWaveUp = new UIButton();
    mButtonMoveWaveUp->SetText("Send Up");
    mRowWave2->AddButton(mButtonMoveWaveUp);
    
    mButtonMoveWaveDown = new UIButton();
    mButtonMoveWaveDown->SetText("Send Down");
    mRowWave2->AddButton(mButtonMoveWaveDown);
    
    
    

    mPathPanel = new ToolMenuPanel();
    mPathPanel->SetTitle("Path Editor");
    AddSection(mPathPanel);
    
    mRowPath1 = new ToolMenuSectionRow();
    mPathPanel->AddSection(mRowPath1);
    
    
    mButtonEditPaths = new UIButton();
    mButtonEditPaths->SetText("Edit Paths");
    mRowPath1->AddButton(mButtonEditPaths);
    
    mButtonSelectNextPath = new UIButton();
    mButtonSelectNextPath->SetText("Next Paths");
    mRowPath1->AddButton(mButtonSelectNextPath);
    
    mButtonSelectPreviousPath = new UIButton();
    mButtonSelectPreviousPath->SetText("Prev Paths");
    mRowPath1->AddButton(mButtonSelectPreviousPath);
    
    
    mRowPath2 = new ToolMenuSectionRow();
    mPathPanel->AddSection(mRowPath2);
    
    
    /*
    mSpecularPanel = new ToolMenuPanel();
    mSpecularPanel->SetTitle("Specular");
    AddSection(mSpecularPanel);
    
    mSliderSpecularShininess = new UISlider();
    mSliderSpecularShininess->SetRange(0.0f, 40.0f);
    mSliderSpecularShininess->SetText("Shininess:");
    mSpecularPanel->AddSection(mSliderSpecularShininess);
    
    
    mSliderSpecularEyeRotationPrimary = new UISlider();
    
    mSliderSpecularEyeRotationPrimary->SetRange(0.0f, 360.0f);
    mSliderSpecularEyeRotationPrimary->SetText("Eye-R1:");
    mSpecularPanel->AddSection(mSliderSpecularEyeRotationPrimary);
    
    mSliderSpecularEyeRotationSecondary = new UISlider();
    
    mSliderSpecularEyeRotationSecondary->SetRange(0.0f, 360.0f);
    mSliderSpecularEyeRotationSecondary->SetText("Eye-R2:");
    mSpecularPanel->AddSection(mSliderSpecularEyeRotationSecondary);
    
    
    
    
    mDirectionPanel = new ToolMenuPanel();
    mDirectionPanel->SetTitle("Directions");
    AddSection(mDirectionPanel);
    
    mSliderDirectionRotationPrimary = new UISlider();
    
    mSliderDirectionRotationPrimary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationPrimary->SetText("Dir-R1:");
    mDirectionPanel->AddSection(mSliderDirectionRotationPrimary);
    
    
    mSliderDirectionRotationSecondary = new UISlider();
    
    mSliderDirectionRotationSecondary->SetRange(0.0f, 360.0f);
    mSliderDirectionRotationSecondary->SetText("Dir-R2:");
    mDirectionPanel->AddSection(mSliderDirectionRotationSecondary);
    
*/
    
    
    /*
    
    mColorPanel = new ToolMenuPanel();
    mColorPanel->SetTitle("Color");
    AddSection(mColorPanel);
    
    mSliderColorR = new UISlider();
    mSliderColorR->SetValue(&pConfiguration->mUniform.mLight.mRed);
    mSliderColorR->SetRange(0.0f, 1.0f);
    mSliderColorR->SetText("Red:");
    mColorPanel->AddSection(mSliderColorR);
    
    mSliderColorG = new UISlider();
    mSliderColorG->SetValue(&pConfiguration->mUniform.mLight.mGreen);
    mSliderColorG->SetRange(0.0f, 1.0f);
    mSliderColorG->SetText("Green:");
    mColorPanel->AddSection(mSliderColorG);
    
    mSliderColorB = new UISlider();
    mSliderColorB->SetValue(&pConfiguration->mUniform.mLight.mBlue);
    mSliderColorB->SetRange(0.0f, 1.0f);
    mSliderColorB->SetText("Blue:");
    mColorPanel->AddSection(mSliderColorB);
    
    mColorPanel->Collapse();
    
    
    
    
    
    
    mIntensityPanel = new ToolMenuPanel();
    mIntensityPanel->SetTitle("Intensity");
    AddSection(mIntensityPanel);
    
    mSliderIntensityAmbient = new UISlider();
    mSliderIntensityAmbient->SetValue(&pConfiguration->mUniform.mLight.mAmbientIntensity);
    mSliderIntensityAmbient->SetRange(0.0f, 1.0f);
    mSliderIntensityAmbient->SetText("Ambient:");
    mIntensityPanel->AddSection(mSliderIntensityAmbient);
    
    mSliderIntensityDiffuse = new UISlider();
    mSliderIntensityDiffuse->SetValue(&pConfiguration->mUniform.mLight.mDiffuseIntensity);
    mSliderIntensityDiffuse->SetRange(0.0f, 1.0f);
    mSliderIntensityDiffuse->SetText("Diffuse:");
    mIntensityPanel->AddSection(mSliderIntensityDiffuse);
    
    mSliderIntensitySpecular = new UISlider();
    mSliderIntensitySpecular->SetValue(&pConfiguration->mUniform.mLight.mSpecularIntensity);
    mSliderIntensitySpecular->SetRange(0.0f, 1.0f);
    mSliderIntensitySpecular->SetText("Specular:");
    mIntensityPanel->AddSection(mSliderIntensitySpecular);
    
    mIntensityPanel->Collapse();
     
    */
    
    DeactivateCloseButton();
}

EditorMenuSections::~EditorMenuSections() {
    
}

void EditorMenuSections::Layout() {
    ToolMenu::Layout();
    
}


void EditorMenuSections::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == mButtonEditPaths) { mEditor->OpenPathEditor(); }
        if (pSender == mButtonAddWave) { mEditor->WaveAdd(); }
        if (pSender == mButtonDeleteWave) { mEditor->WaveRemove(); }
        if (pSender == mButtonSelectNextWave) { mEditor->WaveSelectNext(); }
        if (pSender == mButtonSelectPreviousWave) { mEditor->WaveSelectPrev(); }
        
        if (pSender == mButtonMoveWaveUp) { mEditor->WaveMoveUp(); }
        if (pSender == mButtonMoveWaveDown) { mEditor->WaveMoveDown(); }
        
        if (pSender == mButtonClear) { mEditor->Clear(); }
        if (pSender == mButtonLoadCleared) { mEditor->LoadCleared(); }
        
        if (pSender == mButtonShowSpawn) { mEditor->OpenSpawnMenu(); }
        if (pSender == mButtonShowWavePicker) { mEditor->OpenWavePickerMenu(); }
        
     
        
    }
    
    if (FString(pNotification) == "segment") {
        UISegment *aSegment = (UISegment *)pSender;
        
    }
}

void EditorMenuSections::Update() {
    
    if (gGame != NULL) {
#ifdef EDITOR_MODE
        mCheckBoxPreview->SetTarget(&gGame->mEditorShowReferenced);
#else
        mCheckBoxPreview->SetTarget(NULL);
#endif
    }
    
    
}