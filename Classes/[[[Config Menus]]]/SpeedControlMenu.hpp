//
//  SpeedControlMenu.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 9/20/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef SpeedControlMenu_hpp
#define SpeedControlMenu_hpp

#include "ToolMenu.hpp"

class SpeedControlMenu : public ToolMenu {
public:
    SpeedControlMenu();
    virtual ~SpeedControlMenu();
    
    virtual void                            Update();
    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);
    
    UISegment                               *mSegmentSpeed;
    
    ToolMenuSectionRow                      *mRowFreezeFrame;
    UICheckBox                              *mCheckBoxPause;
    UICheckBox                              *mCheckBoxFreezeFrameEnabled;
    UITextBox                               *mTextBoxFreezeFrame;
    
    UIButton                                *mButtonNextFrame;
    UIButton                                *mButtonPrevFrame;
    
    
    UIButton                                *mButtonNext10Frame;
    UIButton                                *mButtonPrev10Frame;
    
    UIButton                                *mButtonNext100Frame;
    UIButton                                *mButtonPrev100Frame;
    
};

#endif /* SpeedControlMenu_hpp */
