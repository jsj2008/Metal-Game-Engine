//
//  FModelDataPackedSequence.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 9/4/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "FModelDataPackedSequence.hpp"
#include "FApp.hpp"
#include "FTexture.hpp"
#include "FList.hpp"
#include "FFloatBufferCache.hpp"
#include "FIndexBufferCache.hpp"

FModelDataPackedSequence::FModelDataPackedSequence() {
    mIndex = NULL;
    mIndexCount = 0;
    mUseUVW = true;
    mUseNormals = true;
    mUseTangents = false;
    mUseUNormals = false;
}

FModelDataPackedSequence::~FModelDataPackedSequence() {
    Free();
}

void FModelDataPackedSequence::Free() {

    FreeList(FModelDataPacked, mList);
    
    delete [] mIndex;
    mIndex = 0;
    mIndexCount = 0;
}

void FModelDataPackedSequence::Save(const char *pFile) {
    FFile aFile;
    Save(&aFile);
    aFile.Save(pFile);
}

void FModelDataPackedSequence::Save(FFile *pFile) {
    if (!pFile) { return; }

    
    //Now the index count.
    pFile->WriteInt(mIndexCount);
    
    //Now the indices.
    for (int i=0;i<mIndexCount;i++) {
        pFile->WriteShort(mIndex[i]);
    }
    
    pFile->WriteInt(mList.mCount);
    EnumList(FModelDataPacked, aModelPacked, mList) {
        aModelPacked->Save(pFile);
    }
}

void FModelDataPackedSequence::LoadData(FFile *pFile, FSprite *pSprite) {
    
    Free();
    
    if (pFile == NULL) { return; }
    if (pFile->mLength <= 0) { return; }
    
    mIndexCount = pFile->ReadInt();
    mIndex = new GFX_MODEL_INDEX_TYPE[mIndexCount+1];
    for (int i=0;i<mIndexCount;i++) {
        mIndex[i] = pFile->ReadShort();
    }
    
    int aModelListCount = pFile->ReadInt();
    if (mList.mSize < aModelListCount) {
        mList.Size(aModelListCount);
    }
    
    for (int i=0;i<aModelListCount;i++) {
        FModelDataPacked *aModelPacked = new FModelDataPacked();
        aModelPacked->LoadData(pFile, pSprite);
        mList.Add(aModelPacked);
    }
    
    
    
    if (pSprite != NULL) {
        float aStartU = pSprite->mTextureRect.GetStartU();
        float aStartV = pSprite->mTextureRect.GetStartV();
        
        float aEndU = pSprite->mTextureRect.GetEndU();
        float aEndV = pSprite->mTextureRect.GetEndV();
        
        EnumList(FModelDataPacked, aModelPacked, mList) {
            aModelPacked->FitUVW(aStartU, aEndU, aStartV, aEndV);
        }
    }
}

void FModelDataPackedSequence::LoadData(const char *pFile, FSprite *pSprite) {
    FFile aFile;
    
    const char *aResourcePath = gRes.GetResourcePathOfType(pFile, RESOURCE_TYPE_MODEL_DATA);
    while ((aResourcePath != NULL)) {
        aFile.LoadDirect((char *)aResourcePath);
        if (aFile.mLength > 0) { break; }
        aResourcePath = gRes.GetNextResourcePath();
    }
    
    if (aFile.mLength == 0) {
        aFile.Load(pFile);
    }
    
    LoadData(&aFile, pSprite);
}

void FModelDataPackedSequence::LoadOBJSequence(const char *pFile, int pStartIndex, int pEndIndex) {
    
    Free();
    
    const char *aResourcePath = NULL;
    
    FList aModelList;
    
    FFile aFile;
    
    bool aSuccess = false;
    
    FString aFileBase = pFile;
    FString aNumberStringUnpadded;
    FString aNumberStringPadded;
    FString aPath;
    
    FString aZeroString;
    
        for (int aLeadingZeroes = 1;(aLeadingZeroes < 7) && (aSuccess == false);aLeadingZeroes++) {
            aNumberStringUnpadded.ParseInt(pStartIndex);
            if (aNumberStringUnpadded.mLength < aLeadingZeroes) {
                aZeroString.Reset();
                aZeroString.Insert('0', (aLeadingZeroes - aNumberStringUnpadded.mLength), 0);
                aNumberStringPadded.Reset();
                aNumberStringPadded.Append(aZeroString);
                aNumberStringPadded.Append(aNumberStringUnpadded);
            } else {
                aNumberStringPadded.Set(aNumberStringUnpadded);
            }
            
            aPath.Reset();
            aPath.Append(aFileBase);
            aPath.Append(aNumberStringPadded);
            aPath.Append(".obj");
            
            aResourcePath = gRes.GetResourcePathOfType(aPath.c(), RESOURCE_TYPE_MODEL_OBJ);
            while ((aResourcePath != NULL)) {
                aFile.LoadDirect((char *)aResourcePath);
                if (aFile.mLength > 0) { break; }
                aResourcePath = gRes.GetNextResourcePath();
            }
            if (aFile.mLength == 0) {
                aFile.Load(aPath.c());
            }
            
            if (aFile.mLength != 0) {
                FModelData *aData = new FModelData();
                aData->LoadOBJ(&aFile);
                aModelList.Add(aData);
                aSuccess = true;
            }
            
            if (aSuccess) {
                int aIndex = pStartIndex + 1;
                while (aIndex <= pEndIndex) {
                    aNumberStringUnpadded.ParseInt(aIndex);
                    if (aNumberStringUnpadded.mLength < aLeadingZeroes) {
                        aZeroString.Reset();
                        aZeroString.Insert('0', (aLeadingZeroes - aNumberStringUnpadded.mLength), 0);
                        aNumberStringPadded.Reset();
                        aNumberStringPadded.Append(aZeroString);
                        aNumberStringPadded.Append(aNumberStringUnpadded);
                    } else {
                        aNumberStringPadded.Set(aNumberStringUnpadded);
                    }
                    
                    aPath.Reset();
                    aPath.Append(aFileBase);
                    aPath.Append(aNumberStringPadded);
                    aPath.Append(".obj");
                    
                    aResourcePath = gRes.GetResourcePathOfType(aPath.c(), RESOURCE_TYPE_MODEL_OBJ);
                    while ((aResourcePath != NULL)) {
                        aFile.LoadDirect((char *)aResourcePath);
                        if (aFile.mLength > 0) { break; }
                        aResourcePath = gRes.GetNextResourcePath();
                    }
                    if (aFile.mLength == 0) {
                        aFile.Load(aPath.c());
                    }
                    
                    if (aFile.mLength != 0) {
                        FModelData *aData = new FModelData();
                        aData->LoadOBJ(&aFile);
                        aModelList.Add(aData);
                        aIndex++;
                    } else {
                        break;
                    }
                }
            }
        }
    
    if (aModelList.mCount > 0) {
        
        FModelData *aData = ((FModelData *)aModelList.mData[0]);
        if (mUseUVW == false) aData->DiscardUVW();
        if (mUseNormals == false) aData->DiscardNormal();
        
        FModelDataOptimizer *aOptimizer = new FModelDataOptimizer();
        FModelDataIndexed *aDataIndexed = new FModelDataIndexed();
        
        aOptimizer->Generate(aData);
        aOptimizer->Convert(aData, aDataIndexed);
        
        if (aDataIndexed->mIndexCount > 0) {
            mIndexCount = aDataIndexed->mIndexCount;
            mIndex = new GFX_MODEL_INDEX_TYPE[mIndexCount + 1];
            for (int i=0;i<mIndexCount;i++) {
                mIndex[i] = aDataIndexed->mIndex[i];
            }
        }
        
        delete aDataIndexed;
        aDataIndexed = NULL;
        for (int i=0;i<aModelList.mCount;i++) {
            aData = ((FModelData *)aModelList.mData[i]);
            aDataIndexed = new FModelDataIndexed();
            aOptimizer->SolveXYZ(aData, aDataIndexed);
            if (aData->mUVWCount > 0 && mUseUVW == true) { aOptimizer->SolveUVW(aData, aDataIndexed); }
            if (aData->mNormalCount > 0 && mUseNormals == true) { aOptimizer->SolveNormal(aData, aDataIndexed); }
            if (aDataIndexed->mXYZCount > 0) {
                FModelDataPacked *aPacked = new FModelDataPacked();
                aPacked->LoadIndexedModel(aDataIndexed);
                mList.Add(aPacked);
            }
            delete aDataIndexed;
            aDataIndexed = NULL;
        }
        
        delete aOptimizer;
    }
    
    /*
    const char *aResourcePath = gRes.GetResourcePathOfType(pFile, RESOURCE_TYPE_MODEL_OBJ);
    while ((aResourcePath != NULL)) {
        aFile.LoadDirect((char *)aResourcePath);
        if (aFile.mLength > 0) { break; }
        aResourcePath = gRes.GetNextResourcePath();
    }
    if (aFile.mLength == 0) {
        aFile.Load(pFile);
    }
    LoadOBJ(&aFile);
    */
    
    
    //mTestSequence1.LoadOBJ("butterfly_body_", 0, 19);
    //mTestSequence2.LoadOBJ("butterfly_wings_", 0, 19);
    //mTestSequenceMap.Load("butterfly_map");
    
    /*
     butterfly_body_19.obj
     butterfly_body_0.obj
     
     butterfly_wings_0.obj
     butterfly_wings_19.obj
     */
    
    
    /*
     FModelData aTemp;
     FModelDataIndexed aData;
     aTemp.LoadOBJ(pFile);
     FModelDataOptimizer *aOptimizer = new FModelDataOptimizer();
     aOptimizer->Convert(&aTemp, &aData);
     delete aOptimizer;
     aOptimizer = NULL;
     */
    
    
}


FModelDataPacked *FModelDataPackedSequence::GetModel(float pFrame) {
    FModelDataPacked *aResult = NULL;
    int aIndex = (int)(pFrame + 0.01f);
    if (mList.mCount > 0) {
        if (aIndex < 0) { aIndex = 0; }
        if (aIndex >= mList.mCount) { aIndex = (mList.mCount - 1); }
        aResult = (FModelDataPacked *)(mList.mData[aIndex]);
    }
    return aResult;
}

float FModelDataPackedSequence::GetMaxFrame() {
    return (float)(mList.mCount);
}