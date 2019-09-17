//
//  EditorMenuSpawn.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef EditorMenuSpawn_hpp
#define EditorMenuSpawn_hpp

#include "ToolMenu.hpp"

class GameEditor;
class EditorMenuSpawn : public ToolMenu {
public:
    EditorMenuSpawn(GameEditor *pEditor);
    virtual ~EditorMenuSpawn();
    
    virtual void                            Layout() override;
    virtual void                            Notify(void *pSender, const char *pNotification) override;
    virtual void                            Update() override;
    
    GameEditor                              *mEditor;
    
    ToolMenuPanel                           *mGenerationPanel;
    UISegment                               *mSegmentSpeed;
    UIStepper                               *mStepperSpawnCount;
    UIStepper                               *mStepperSpacing;
    ToolMenuSectionRow                      *mGenerationRow1;
    UIButton                                *mButtonCopy;
    UIButton                                *mButtonPasteEOL;
    UIButton                                *mButtonPasteINS;
    
    
    
    ToolMenuPanel                           *mTimingPanel;
    UIStepper                               *mStepperCreationDelay;
    
    ToolMenuSectionRow                      *mTimingRow1;
    UICheckBox                              *mCheckBoxCreationRequiresPrevWaveStart;
    UICheckBox                              *mCheckBoxCreationRequiresPrevWaveComplete;
    
    
    ToolMenuSectionRow                      *mTimingRow2;
    UICheckBox                              *mCheckBoxCreationRequiresScreenWavesClear;
    UICheckBox                              *mCheckBoxCreationRequiresScreenPermsClear;
};

#endif
