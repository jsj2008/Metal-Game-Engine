//
//  FModelDataPackedSequence.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/4/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FModelDataPackedSequence_hpp
#define FModelDataPackedSequence_hpp

#include "FModelData.h"
#include "FModelDataPacked.hpp"
#include "FFile.hpp"
#include "FImage.hpp"
#include "FSprite.hpp"
#include "os_core_graphics.h"

class FModelDataPackedSequence {
public:
    
    FModelDataPackedSequence();
    virtual ~FModelDataPackedSequence();
    
    void                                Free();
    
    FModelDataPacked                    *GetModel(float pFrame);
    float                               GetMaxFrame();
    
    
    void                                Save(FFile *pFile);
    void                                Save(const char *pFile);
    inline void                         Save(FString pName) { Save((const char*)pName.c()); }
    
    //This is for loading a sequence of 3DM files...
    void                                LoadData(FFile *pFile, FSprite *pSprite);
    void                                LoadData(const char *pFile, FSprite *pSprite);
    inline void                         LoadData(FString pFile, FSprite *pSprite) { LoadData((const char*)pFile.c(), pSprite); }
    
    void                                LoadOBJSequence(const char *pFile, int pStartIndex, int pEndIndex);
    inline void                         LoadOBJSequence(FString pFile, int pStartIndex, int pEndIndex) { LoadOBJSequence((const char*)pFile.c(), pStartIndex, pEndIndex); }
    
    GFX_MODEL_INDEX_TYPE                *mIndex;
    int                                 mIndexCount;
    
    //List of FModelDataPacked
    FList                               mList;
    
    bool                                mUseUVW;
    bool                                mUseNormals;
    bool                                mUseTangents;
    bool                                mUseUNormals;
};

#endif