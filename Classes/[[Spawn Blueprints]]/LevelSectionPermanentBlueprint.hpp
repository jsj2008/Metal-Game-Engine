//
//  LevelSectionPermanentBlueprint.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 4/5/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef LevelSectionPermanentBlueprint_hpp
#define LevelSectionPermanentBlueprint_hpp

#include "LevelPathBlueprint.hpp"

class LevelSectionPermanent;
class LevelSectionPermanentBlueprint {
public:
    LevelSectionPermanentBlueprint();
    ~LevelSectionPermanentBlueprint();
    
    void                                        Reset();
    
    void                                        Update();
    void                                        Draw(bool pSelected);
    
    LevelPathBlueprint                          mPath;
    void                                        ApplyEditorConstraints();
    
    
    
    
    Constraint                                  mConstraint;
    
    float                                       mEditorX;
    float                                       mEditorY;
    
    float                                       mPercentX;
    float                                       mPercentY;
    
    float                                       mBaseGameX;
    float                                       mBaseGameY;
    
    float                                       mGameX;
    float                                       mGameY;
    
    void                                        ShiftX(float pShiftX);
    void                                        ShiftY(float pShiftY);
    
    
    
    //Note: BUILD should have NO TIE-IN TO EDITOR...
    //This HAS to work WITHOUT EDITOR for GAME......
    void                                        Build(LevelSectionPermanent *pPerm);
    
    FJSONNode                                   *Save();
    void                                        Load(FJSONNode *pNode);
    
    int                                         mKillTimer;
};

#endif /* LevelSectionPermanentBlueprint_hpp */