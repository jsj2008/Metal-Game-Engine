#include "FApp.hpp"
#include "FSprite.h"
#include "FTexture.hpp"
#include "FVertexBuffer.h"
#include "FStringBuffer.h"
#include "core_includes.h"

//TODO: Turn off for release...
bool gSpriteListEnabled = true;
FList gSpriteList;
FList gSpriteSequenceList;

FSprite::FSprite() {
    mTexture = 0;
    mWidth=0;
    mHeight=0;
    mAddToSpriteList = true;
    mDidLoad = false;
    mDidLoadFromBundle = false;
    mDidLoadFromResource = false;
    mDidLoadSingle = false;
}

FSprite::~FSprite() {
    Kill();
}

void FSprite::Kill() {
    //
    SetTexture(0);
    //
    mDidLoad = false;
    mDidLoadFromBundle = false;
    mDidLoadFromResource = false;
    mDidLoadSingle = false;
    //
    mWidth = 0;
    mHeight = 0;
    //
}

void FSprite::SetTexture(FTexture *pTexture) {
    if (mTexture) {
        if (pTexture != mTexture) {
            if(gTextureCache.mAutoMode == true) {
                gTextureCache.TextureBindRemove(mTexture);
                mTexture = 0; }
        }
    }
    if (pTexture) {
        mTexture = pTexture;
        if(gTextureCache.mAutoMode == true) {
            gTextureCache.TextureBindAdd(mTexture);
        }
    }
}

void FSprite::LoadNode(FImageBundler *pImageBundler, FImageBundlerLoadNode *pNode) {
    if (mDidLoad) {
        Log("Preventing Double Load [__NODE__]\n");
        return;
    }
    
    //Log("Sprite Loading With Node [%d %d %d %d]\n", pNode->mX, pNode->mY, pNode->mWidth, pNode->mHeight);
    
    Kill();
    
    if (pImageBundler == 0) return;
    if (pNode == 0) return;

    FTexture *aTexture = gTextureCache.GetTexture(pImageBundler->mBundleName.c());

    SetTexture(aTexture);

    //aStartU,aStartV,aEndU,aEndV;
    //aLeft, aTop, aRight, aBottom;

    float aStartU = pNode->mSpriteUStart;
    float aStartV = pNode->mSpriteVStart;
    float aEndU = pNode->mSpriteUEnd;
    float aEndV = pNode->mSpriteVEnd;

    float aScale = 1.0f / (float)aTexture->mScale;
    
    
    float aLeft = pNode->mSpriteLeft * aScale;
    float aRight = pNode->mSpriteRight * aScale;
    float aTop = pNode->mSpriteTop * aScale;
    float aBottom = pNode->mSpriteBottom * aScale;
    mWidth = (int)(pNode->mOriginalWidth * aScale + 0.5f);
    mHeight = (int)(pNode->mOriginalHeight * aScale + 0.5f);
    
    mTextureRect.SetQuad(aLeft, aTop, aRight, aBottom);
    mTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    
    mDidLoad = true;
    mDidLoadFromBundle = true;
    mDidLoadSingle = false;
}

void FSprite::Load(char *pName, FImageBundler *pBundler) {
    if (mDidLoad) {
        Log("Preventing Double Load [%s]\n", pName);
        return;
    }
    Kill();
    if (!pBundler) { return; }
    if (pBundler->mDidLoad == false) { return; }
    FImageBundlerLoadNode *aNode = pBundler->FetchNode(pName);
    FTexture *aTexture = gTextureCache.GetTexture(pBundler->mBundleName.c());
    if ((aNode != 0) && (aTexture != 0)) {
        LoadNode(pBundler, aNode);
    }
}

void FSprite::Load(char *pFile) {
    if (mDidLoad) {
        Log("Preventing Double Load [%s]\n", pFile);
        return;
    }
    
    Kill();
    
    mFileName = pFile;
    mFileName.RemovePath();
    mFileName.RemoveExtension();
    
    if (gImageBundler.mAutoBundle) {
        if (gImageBundler.mBundleName.mLength > 0) {
            //FImage aImage;
            //aImage.Load(pFile);

            gImageBundler.AddImage(pFile);
        }
    }

    Load(pFile, &gImageBundler);

    if (mWidth > 0 && mHeight > 0) {
        mDidLoad = true;
        mDidLoadFromBundle = true;
        mDidLoadSingle = false;
        if (gSpriteListEnabled == true) {
            gSpriteList.Add(this);
        }
        return;
    }

    Load(gTextureCache.GetTexture(mFileName.c()));

    if (mWidth > 0 && mHeight > 0) {
        mDidLoad = true;
        mDidLoadFromBundle = false;
        mDidLoadSingle = true;
        if (gSpriteListEnabled == true) {
            gSpriteList.Add(this);
        }
    }
}

void FSprite::LoadN(const char *pFileStart, int pIndex) {
    Load(FString(pFileStart) + FString(pIndex));
}

void FSprite::LoadN(const char *pFileStart, int pIndex, const char *pFileEnd) {
    Load(FString(pFileStart) + FString(pIndex) + FString(pFileEnd));
}

void FSprite::LoadN(const char *pFileStart, int pIndex1, const char *pFileEnd, int pIndex2) {
    Load(FString(pFileStart) + FString(pIndex1) + FString(pFileEnd) + FString(pIndex2));
}

void FSprite::LoadN(const char *pFileStart, int pIndex1, const char *pFileMiddle, int pIndex2, const char *pFileEnd) {
    Load(FString(pFileStart) + FString(pIndex1) + FString(pFileMiddle) + FString(pIndex2) + FString(pFileEnd));
}

void FSprite::Load(FImage *pImage) {
    if(pImage)
    {
        Load(pImage, pImage->mOffsetX, pImage->mOffsetY, pImage->mWidth, pImage->mHeight);
        //Load(pImage, 0, 0, pImage->mWidth, pImage->mHeight);
    }
}

void FSprite::Load(FImage *pImage, int pX, int pY, int pWidth, int pHeight) {
    Kill();
    if(!pImage)return;
    if((pImage->mWidth <= 0) || (pImage->mHeight <=0 ))return;
    Load(pImage->GetTexture(), pX, pY, pWidth, pHeight);
}

void FSprite::Load(FTexture *pTexture) {
    if (pTexture) {
        Load(pTexture, pTexture->mOffsetX, pTexture->mOffsetY, pTexture->mWidth, pTexture->mHeight);
    }
}

void FSprite::Load(FTexture *pTexture, int pX, int pY, int pWidth, int pHeight) {
    if (mDidLoad) {
        Log("Preventing Double Load [_TEXTURE_RECT]\n");
        return;
    }
    
    //Log("Sprite Loading With Texture [%d %d %d %d]\n", pX, pY, pWidth, pHeight);
    
    Kill();
    if (pTexture) {
        
        
        if ((pTexture->mExpandedWidth > 0) && (pTexture->mExpandedHeight > 0)) {
            SetTexture(pTexture);
            
            float aScale = 1.0f / (float)pTexture->mScale;
            
            mWidth = (int)(pWidth * aScale + 0.5f);
            mHeight = (int)(pHeight * aScale + 0.5f);
            
            float aStartU = (float)pX / (float)pTexture->mExpandedWidth;
            float aStartV = (float)pY / (float)pTexture->mExpandedHeight;
            float aEndU = (float)(pX + pWidth) / (float)pTexture->mExpandedWidth;
            float aEndV = (float)(pY + pHeight) / (float)pTexture->mExpandedHeight;

            mTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
            
            float aHeight2 = ((float)mHeight) * 0.5f;
            float aWidth2 = ((float)mWidth) * 0.5f;
            mTextureRect.SetQuad(-aWidth2, -aHeight2, aWidth2, aHeight2);
        }
    }
}

bool FSprite::DidLoad() {
    bool aResult = true;
    if(mTexture == 0)aResult = false;
    if((mWidth <= 0.0f) || (mHeight <= 0.0f))aResult = false;
    return aResult;
}

float FSprite::ScaleFitH(float pWidth) {
    float aResult = 1.0f;
    if (mWidth > 0.0f) {
        if (pWidth >= 0.25f) {
            aResult = pWidth / mWidth;
        }
    }
    return aResult;
}

float FSprite::ScaleFitV(float pHeight)
{
    float aResult = 1.0f;
    
    if(mHeight > 0.0f)
    {
        if(pHeight >= 0.25f)
        {
            aResult = pHeight / mHeight;
        }
    }
    
    return aResult;
}

float FSprite::ScaleFitH(float pWidth, float pOffset) {
    return ScaleFitH(pWidth - pOffset);
}

float FSprite::ScaleFitV(float pHeight, float pOffset) {
    return ScaleFitV(pHeight - pOffset);
}

void FSprite::Draw() {
    //
    
    Graphics::DrawSprite(mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
    
    
    /*
    if (mBufferIndexPosition == -1) {
        WriteBuffers();
    }
    //
    if (mBufferIndexPosition != -1) {
        BindBuffers();
        Graphics::TextureBind(mTexture);
        Graphics::DrawTriangleStrips(4);
    }
    //
    */
}

void FSprite::Center(float x, float y)
{
    Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::Draw(float x, float y)
{
    Graphics::DrawSprite(x + mWidth/2.0f, y + mHeight/2.0f, 1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawStretchedV(float x, float y, float pHeight)
{
    /*
     
     mVertex[0]=0;
     mVertex[1]=0;
     mVertex[2]=mWidth;
     mVertex[3]=0;
     mVertex[4]=0;
     mVertex[5]=pHeight;
     mVertex[6]=mWidth;
     mVertex[7]=pHeight;
     
     Graphics::MatrixPush();
     Graphics::Translate(x,y);
     Draw();
     Graphics::MatrixPop();
     */
    
}


void FSprite::DrawStretchedH(float x, float y, float pWidth)
{
    /*
     
     mVertex[0]=0;
     mVertex[1]=0;
     mVertex[2]=pWidth;
     mVertex[3]=0;
     mVertex[4]=0;
     mVertex[5]=mHeight;
     mVertex[6]=pWidth;
     mVertex[7]=mHeight;
     
     Graphics::MatrixPush();
     Graphics::Translate(x,y);
     Draw();
     Graphics::MatrixPop();
     */
    
}

/*
 void FSprite::DrawExtended(FVec2 pOrigin, FVec2 pTranslate, FVec2 pCenter, float pRotationAboutOrigin, float pRotationAboutCenter, float pScale, bool pFlip)
 {
 Graphics::MatrixPush();
	Graphics::Translate(pOrigin);
	Graphics::Rotate(pRotationAboutOrigin);
	
	if(pFlip)
	{
 Graphics::Scale(-pScale, pScale, pScale);
	}
	else
	{
 Graphics::Scale(pScale, pScale, pScale);
	}
	
	Graphics::Translate(pTranslate);
	Graphics::Rotate(pRotationAboutCenter);
	
	FVec2 aCenter=FVec2(mVertex[6],mVertex[7]);
	FVec2 aShift=aCenter-pCenter;
 
	Graphics::Translate(aShift);
 
	Draw();
 Graphics::MatrixPop();
 }
 */

void FSprite::CenterRotated(float x, float y, float pRotationDegrees)
{
    Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, pRotationDegrees, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::Draw(float x, float y, float pScale, float pRotationDegrees)
{
    Graphics::DrawSprite(x, y, pScale, pScale, 1.0f, pRotationDegrees, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing)
{
    if(pFacing < 1)DrawFlippedH(x, y, pScale, pRotationDegrees);
    else Draw(x, y, pScale, pRotationDegrees);
}

void FSprite::Center(float x, float y, int pFacing)
{
    Graphics::DrawSprite(x, y, pFacing<0 ? (-1.f) : (1.0f) , 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawFlippedH(float x, float y)
{
    Graphics::DrawSprite(x + mWidth/2.0f, y + mHeight/2.0f, -1.0f, 1.0f, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawFlippedH(float x, float y, float pScale, float pRotationDegrees)
{
    Graphics::DrawSprite(x, y, -pScale, pScale, 1.0f, pRotationDegrees, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawFlippedV(float x, float y)
{
    
}

void FSprite::DrawFlippedV(float x, float y, float pScale, float pRotationDegrees)
{
    
}

FTextureRect cSliceTextureRect;

void FSprite::DrawQuad(float pX1, float pY1,
                       float pX2, float pY2,
                       float pX3, float pY3,
                       float pX4, float pY4)
{
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    cSliceTextureRect.SetQuad(pX1, pY1, pX2, pY2, pX3, pY3, pX4, pY4);
    
    Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawQuad(float pLeft, float pTop,
                       float pRight, float pBottom)
{
    DrawQuad(pLeft, pTop, pRight, pTop, pLeft, pBottom, pRight, pBottom);
}

void FSprite::CenterQuad(float pCenterX, float pCenterY, float pLeft, float pTop,
                       float pRight, float pBottom)
{
    float aWidth2 = (pRight - pLeft) * 0.5f;
    float aHeight2 = (pBottom - pTop) * 0.5f;
    
    
    DrawQuad(pCenterX - aWidth2, pCenterY - aHeight2, pCenterX + aWidth2, pCenterY + aHeight2);
}



void FSprite::DrawQuadRect(float pX, float pY, float pWidth, float pHeight)
{
    float aX1 = pX;
    float aX2 = pX + pWidth;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + pHeight;
    float aY4 = aY3;
    
    DrawQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    
}

void FSprite::DrawQuadRectOffset(float pX, float pY, float pWidth, float pHeight, float pOffset)
{
    float aOffset2 = pOffset * 2.0f;
    DrawQuadRect(pX - pOffset, pY - pOffset, pWidth + aOffset2, pHeight + aOffset2);
}

void FSprite::DrawTripletH(float pX, float pY, float pInsetLeft, float pInsetRight, float pLength, bool pDrawLeft, bool pDrawMiddle, bool pDrawRight)
{
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aLengthCenter = (pLength - (pInsetLeft + pInsetRight));
    
    float aTripletLeftX = pX;
    float aTripletCenterX1 = pX + pInsetLeft;
    float aTripletCenterX2 = aTripletCenterX1 + aLengthCenter;
    float aTripletRightX = pX + pLength;
    
    float aTripletCenterU1 = aStartU;
    float aTripletCenterU2 = aEndU;
    //float aTripletRightU = aEndU;
    
    if(mWidth > 0.0f)
    {
        //aTripletLeftU = 0.0f;
        aTripletCenterU1 = pInsetLeft / mWidth;
        aTripletCenterU2 = (mWidth - pInsetRight) / mWidth;
        //aTripletRightU
        
        aTripletCenterU1 = (aStartU + ((aEndU - aStartU) * aTripletCenterU1));
        aTripletCenterU2 = (aStartU + ((aEndU - aStartU) * aTripletCenterU2));
    }
    
    
    float aX1 = aTripletLeftX;
    float aX2 = aTripletCenterX1;
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = pY;
    float aY2 = aY1;
    float aY3 = pY + mHeight;
    float aY4 = aY3;
    
    if(pDrawLeft)
    {
        cSliceTextureRect.SetUVQuad(aStartU, aStartV, aTripletCenterU1, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
    }
    
    aX1 = aTripletCenterX1;
    aX2 = aTripletCenterX2;
    aX3 = aX1;
    aX4 = aX2;
    
    if(pDrawMiddle)
    {
        cSliceTextureRect.SetUVQuad(aTripletCenterU1, aStartV, aTripletCenterU2, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
    }
    
    aX1 = aTripletCenterX2;
    aX2 = aTripletRightX;
    aX3 = aX1;
    aX4 = aX2;
    
    if(pDrawRight)
    {
        cSliceTextureRect.SetUVQuad(aTripletCenterU2, aStartV, aEndU, aEndV);
        cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
        Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
    }
}

void FSprite::Draw9x9(float pX, float pY, float pWidth, float pHeight, float pScale, float pRotation, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft)
{
    if(mWidth < 1.0)return;
    if(mHeight < 1.0)return;
    
    float aX[4];
    float aY[4];
    float aU[4];
    float aV[4];
    
    float aWidth = pWidth * pScale;
    float aHeight = pHeight * pScale;
    
    float aQuadInsetLeft = pInsetLeft * pScale;
    float aQuadInsetRight = pInsetRight * pScale;
    float aQuadInsetTop = pInsetTop * pScale;
    float aQuadInsetBottom = pInsetBottom * pScale;
    
    float aQuadRight = pX + aWidth;
    float aQuadBottom = pY + aHeight;
    
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    float aSpanU = (aEndU - aStartU);
    float aSpanV = (aEndV - aStartV);
    
    aX[0] = pX;
    aX[1] = pX + aQuadInsetLeft;
    aX[3] = aQuadRight;
    aX[2] = (aQuadRight - aQuadInsetRight);
    
    aY[0] = pY;
    aY[1] = pY + aQuadInsetLeft;
    aY[3] = aQuadBottom;
    aY[2] = (aQuadBottom - aQuadInsetBottom);
    
    aU[0] = aStartU;
    aU[3] = aEndU;
    aV[0] = aStartV;
    aV[3] = aEndV;
    
    aU[1] = (pInsetLeft / mWidth);
    aU[2] = ((mWidth - pInsetRight) / mWidth);
    aV[1] = (pInsetTop / mHeight);
    aV[2] = ((mHeight - pInsetBottom) / mHeight);
    
    
    aU[1] = (aU[1] * aSpanU) + aStartU;
    aU[2] = (aU[2] * aSpanU) + aStartU;
    aV[1] = (aV[1] * aSpanV) + aStartV;
    aV[2] = (aV[2] * aSpanV) + aStartV;
    
    
    for(int i=1;i<4;i++)
    {
        for(int n=1;n<4;n++)
        {
            cSliceTextureRect.SetUVQuad(aU[i - 1], aV[n - 1], aU[i], aV[n]);
            cSliceTextureRect.SetQuad(aX[i - 1], aY[n - 1], aX[i], aY[n]);
            Graphics::DrawSprite(cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
        }
    }
}

void FSprite::DrawShiftedCorners(float x, float y, float pScale, float pRotationDegrees, FVec2 pShiftUL, FVec2 pShiftUR, FVec2 pShiftDL, FVec2 pShiftDR) {
    float aX1 = mTextureRect.GetStartX();
    float aX2 = mTextureRect.GetEndX();
    float aX3 = aX1;
    float aX4 = aX2;
    
    float aY1 = mTextureRect.GetStartY();
    float aY2 = aY1;
    float aY3 = mTextureRect.GetEndY();
    float aY4 = aY3;
    
    
    aX1 += pShiftUL.mX;
    aY1 += pShiftUL.mY;
    
    aX2 += pShiftUR.mX;
    aY2 += pShiftUR.mY;
    
    aX3 += pShiftDL.mX;
    aY3 += pShiftDL.mY;
    
    aX4 += pShiftDR.mX;
    aY4 += pShiftDR.mY;
    
    cSliceTextureRect.SetQuad(aX1, aY1, aX2, aY2, aX3, aY3, aX4, aY4);
    
    float aStartU = mTextureRect.GetStartU();
    float aStartV = mTextureRect.GetStartV();
    
    float aEndU = mTextureRect.GetEndU();
    float aEndV = mTextureRect.GetEndV();
    
    cSliceTextureRect.SetUVQuad(aStartU, aStartV, aEndU, aEndV);
    
    Graphics::DrawSprite(x, y, 1.0f, 1.0f, 1.0f, pRotationDegrees, cSliceTextureRect.mVertex, cSliceTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawSliceTo(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY)
{
    if((mWidth > 0.0f) && (mHeight > 0.0f) && (pTextureRect != 0))
    {
        
        float aBaseStartU = mTextureRect.GetStartU();
        float aBaseStartV = mTextureRect.GetStartV();
        
        float aBaseEndU = mTextureRect.GetEndU();
        float aBaseEndV = mTextureRect.GetEndV();
        
        float aBaseRangeU = aBaseEndU - aBaseStartU;
        float aBaseRangeV = aBaseEndV - aBaseStartV;
        
        float aStartU = pStartX / mWidth;
        float aEndU = pEndX / mWidth;
        
        float aStartV = pStartY / mHeight;
        float aEndV = pEndY / mHeight;
        
        aStartU = aBaseStartU + aBaseRangeU * aStartU;
        aEndU = aBaseStartU + aBaseRangeU * aEndU;
        
        aStartV = aBaseStartV + aBaseRangeV * aStartV;
        aEndV = aBaseStartV + aBaseRangeV * aEndV;
        
        
        pTextureRect->SetQuad(pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
        pTextureRect->SetUVQuad(aStartU, aStartV, aEndU, aEndV);
        
        Graphics::DrawSprite(pTextureRect->mVertex, pTextureRect->mTextureCoord, mTexture);
    }
}

static FTextureTriangle cRadialTriangle;
void FSprite::DrawAngleRange(float pX, float pY, float pScale, float pRotation, float pStartRotation, float pEndRotation)
{
    float aAngleDiff = (pEndRotation - pStartRotation);
    
    if(aAngleDiff <= 0.0f) { return; }
    
    if(aAngleDiff >= 360.0f) {
        Draw(pX, pY, pScale, pRotation);
        return;
    }
    
    if (pStartRotation < 0 || pStartRotation >= 360.0f) {
        pStartRotation = fmodf(pStartRotation, 360.0f);
        if(pStartRotation < 0)pStartRotation += 360.0f;
    }
    
    if (pEndRotation < 0 || pEndRotation >= 360.0f) {
        pEndRotation = fmodf(pEndRotation, 360.0f);
        if(pEndRotation < 0)pEndRotation += 360.0f;
    }
    
    float aStartU = GetStartU();
    float aStartV = GetStartV();
    
    float aEndU = GetEndU();
    float aEndV = GetEndV();
    
    float aStartX = GetStartX();
    float aStartY = GetStartY();
    
    float aEndX = GetEndX();
    float aEndY = GetEndY();
    
    float aX[4] = {aStartX, aEndX, aEndX, aStartX};
    float aY[4] = {aStartY, aStartY, aEndY, aEndY};
    
    float aURange = (aEndU - aStartU);
    float aVRange = (aEndV - aStartV);
    
    float aXRange = (aEndX - aStartX);
    float aYRange = (aEndY - aStartY);
    
    float aCenterU = aStartU + aURange * 0.5f;
    float aCenterV = aStartV + aVRange * 0.5f;
    
    float aLineStartX, aLineStartY, aLineEndX, aLineEndY;
    
    float aLineDirX, aLineDirY;
    float aLineNormX, aLineNormY;
    
    float aPlaneLength;
    
    float aDirX1 = Sin(pStartRotation);
    float aDirY1 = -Cos(pStartRotation);
    
    float aDirX2 = Sin(pEndRotation);
    float aDirY2 = -Cos(pEndRotation);
    
    float aCheckLength1, aCheckLength2;
    
    int aHitLine1 = -1;
    int aHitLine2 = -1;
    
    float aBestLength1 = 9999000000000.0f;
    float aBestLength2 = 9999000000000.0f;
    
    float aNumer, aDenom;
    
    int aStart = 3;
    int aEnd = 0;
    while (aEnd < 4) {
        aLineStartX = aX[aStart];
        aLineStartY = aY[aStart];
        
        aLineEndX = aX[aEnd];
        aLineEndY = aY[aEnd];
        
        aLineDirX = (aLineEndX - aLineStartX);
        aLineDirY = (aLineEndY - aLineStartY);
        
        aLineNormX = (-aLineDirY);
        aLineNormY = aLineDirX;
        
        aPlaneLength = (aLineDirX * aLineDirX) + (aLineDirY * aLineDirY);
        
        if(aPlaneLength > 0.01f)
        {
            aPlaneLength = sqrtf(aPlaneLength);
            
            aLineDirX /= aPlaneLength;
            aLineDirY /= aPlaneLength;
        }
        
        aNumer = (-(aLineNormX * aLineStartX + aLineNormY * aLineStartY));
        aDenom = (aDirX1 * aLineNormX + aDirY1 * aLineNormY);
        aCheckLength1 = -(aNumer / aDenom);
        
        //return
        
        if(aCheckLength1 > 0)
        {
            if(aCheckLength1 < aBestLength1)
            {
                aBestLength1 = aCheckLength1;
                aHitLine1 = aStart;
            }
        }
        
        aDenom = (aDirX2 * aLineNormX + aDirY2 * aLineNormY);
        aCheckLength2 = -(aNumer / aDenom);
        
        if(aCheckLength2 > 0)
        {
            if(aCheckLength2 < aBestLength2)
            {
                aBestLength2 = aCheckLength2;
                aHitLine2 = aStart;
            }
        }
        
        aStart = aEnd;
        aEnd++;
    }
    
    if((aHitLine1 == -1) || (aHitLine2 == -1)) { return; }
    
    float aEdgeX1 = aDirX1 * aBestLength1;
    float aEdgeY1 = aDirY1 * aBestLength1;
    
    float aEdgeX2 = aDirX2 * aBestLength2;
    float aEdgeY2 = aDirY2 * aBestLength2;
    
    float aEdgeU1 = aStartU + ((aEdgeX1 - aStartX) / aXRange) * aURange;
    float aEdgeV1 = aStartV + ((aEdgeY1 - aStartY) / aYRange) * aVRange;
    float aEdgeU2 = aStartU + ((aEdgeX2 - aStartX) / aXRange) * aURange;
    float aEdgeV2 = aStartV + ((aEdgeY2 - aStartY) / aYRange) * aVRange;
    
    float aOctantX[8] = {0.0f, aEndX, aEndX, aEndX, 0.0f, aStartX, aStartX, aStartX};
    float aOctantY[8] = {aStartY, aStartY, 0.0f, aEndY, aEndY, aEndY, 0.0f, aStartY};
    float aOctantU[8] = {aCenterU,aEndU,aEndU,aEndU,aCenterU,aStartU, aStartU, aStartU};
    float aOctantV[8] = {aStartV, aStartV, aCenterV, aEndV, aEndV, aEndV, aCenterV, aStartV};
    bool aOctantDraw[8] = {false, false, false, false, false, false, false, false};
    
    aOctantDraw[0] = false;aOctantDraw[1] = false;aOctantDraw[2] = false;aOctantDraw[3] = false;aOctantDraw[4] = false;aOctantDraw[5] = false;aOctantDraw[6] = false;aOctantDraw[7] = false;
    
    int aOctantStart = 7;
    int aOctantEnd = 7;
    
    if(aHitLine1 == 0)
    {
        if(aEdgeX1 >= 0)aOctantStart = 0;
        else aOctantStart = 7;
    }
    
    if(aHitLine1 == 1)
    {
        if(aEdgeY1 <= 0)aOctantStart = 1;
        else aOctantStart = 2;
    }
    
    if(aHitLine1 == 2)
    {
        if(aEdgeX1 > 0)aOctantStart = 3;
        else aOctantStart = 4;
    }
    
    if(aHitLine1 == 3)
    {
        if(aEdgeY1 < 0)aOctantStart = 6;
        else aOctantStart = 5;
    }
    
    if(aHitLine2 == 0)
    {
        if(aEdgeX2 >= 0)aOctantEnd = 0;
        else aOctantEnd = 7;
    }
    
    if(aHitLine2 == 1)
    {
        if(aEdgeY2 <= 0)aOctantEnd = 1;
        else aOctantEnd = 2;
    }
    
    if(aHitLine2 == 2)
    {
        if(aEdgeX2 > 0)aOctantEnd = 3;
        else aOctantEnd = 4;
    }
    
    if(aHitLine2 == 3)
    {
        if(aEdgeY2 < 0)aOctantEnd = 6;
        else aOctantEnd = 5;
    }
    
    
    
    if(aOctantStart == aOctantEnd)
    {
        if(pEndRotation < pStartRotation)
        {
            int aDrawOctant1 = aOctantStart;
            int aDrawOctant2 = aDrawOctant1 + 1;
            if(aDrawOctant2 == 8)aDrawOctant2 = 0;
            
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aOctantX[aDrawOctant2], aOctantY[aDrawOctant2]);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aOctantU[aDrawOctant2], aOctantV[aDrawOctant2]);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mVertex, cRadialTriangle.mTextureCoord, mTexture);
            
            
            aDrawOctant1 = aOctantEnd;
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aDrawOctant1], aOctantY[aDrawOctant1], aEdgeX2, aEdgeY2);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aDrawOctant1], aOctantV[aDrawOctant1], aEdgeU2, aEdgeV2);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mVertex, cRadialTriangle.mTextureCoord, mTexture);
            
            
            for(int i=0;i<8;i++)
            {
                if(i != aOctantStart)
                {
                    aOctantDraw[i] = true;
                }
            }
        } else {
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aEdgeX2, aEdgeY2);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aEdgeU2, aEdgeV2);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mVertex, cRadialTriangle.mTextureCoord, mTexture);
        }
    }
    else
    {
        int aDrawOctant1 = aOctantStart;
        int aDrawOctant2 = aDrawOctant1 + 1;
        if(aDrawOctant2 == 8)aDrawOctant2 = 0;
        
        cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aEdgeX1, aEdgeY1, aOctantX[aDrawOctant2], aOctantY[aDrawOctant2]);
        cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aEdgeU1, aEdgeV1, aOctantU[aDrawOctant2], aOctantV[aDrawOctant2]);
        Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mVertex, cRadialTriangle.mTextureCoord, mTexture);
        
        
        aDrawOctant1 = aOctantEnd;
        cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aDrawOctant1], aOctantY[aDrawOctant1], aEdgeX2, aEdgeY2);
        cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aDrawOctant1], aOctantV[aDrawOctant1], aEdgeU2, aEdgeV2);
        Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mVertex, cRadialTriangle.mTextureCoord, mTexture);
        
        int aOctant = aOctantStart;
        for (int i=0;i<8;i++) {
            aOctant++;
            if(aOctant == 8)aOctant = 0;
            if(aOctant == aOctantEnd)break;
            aOctantDraw[aOctant] = true;
        }
    }
    
    for (int aOctant=0;aOctant<8;aOctant++) {
        if (aOctantDraw[aOctant]) {
            int aOctant2 = aOctant + 1;
            if(aOctant2 == 8)aOctant2 = 0;
            cRadialTriangle.SetXYTriangle(0.0f, 0.0f, aOctantX[aOctant], aOctantY[aOctant], aOctantX[aOctant2], aOctantY[aOctant2]);
            cRadialTriangle.SetUVTriangle(aCenterU, aCenterV, aOctantU[aOctant], aOctantV[aOctant], aOctantU[aOctant2], aOctantV[aOctant2]);
            Graphics::DrawSpriteTriangle(pX, pY, pScale, pScale, pScale, pRotation, cRadialTriangle.mVertex, cRadialTriangle.mTextureCoord, mTexture);
        }
    }
}

void FSprite::DrawSlice(FTextureRect *pTextureRect, float pStartX, float pStartY, float pEndX, float pEndY) {
    DrawSliceTo(pTextureRect, pStartX, pStartY, pEndX, pEndY, 0.0f, 0.0f, pEndX - pStartX, pEndY - pStartY);
}

void FSprite::DrawSliceTo(float pStartX, float pStartY, float pEndX, float pEndY, float pDrawStartX, float pDrawStartY, float pDrawEndX, float pDrawEndY) {
    DrawSliceTo(&cSliceTextureRect, pStartX, pStartY, pEndX, pEndY, pDrawStartX, pDrawStartY, pDrawEndX, pDrawEndY);
}

void FSprite::DrawSlice(float pStartX, float pStartY, float pEndX, float pEndY) {
    DrawSlice(&cSliceTextureRect, pStartX, pStartY, pEndX, pEndY);
}

void FSprite::DrawScaled(float pX, float pY, float pScale) {
    Draw(pX, pY, pScale, 0.0f);
}

void FSprite::DrawScaled(float pX, float pY, float pScaleX, float pScaleY) {
    Graphics::DrawSprite(pX, pY, pScaleX, pScaleY, 1.0f, 0.0f, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawScaled(float pX, float pY, float pScaleX, float pScaleY, float pRotation)
{
    Graphics::DrawSprite(pX, pY, pScaleX, pScaleY, 1.0f, pRotation, mTextureRect.mVertex, mTextureRect.mTextureCoord, mTexture);
}

void FSprite::DrawRotated(float pX, float pY, float pRotation) {
    Draw(pX, pY, 1.0f, pRotation);
}

void FSprite::PrintQuadData()
{
    FString aName = mFileName.c();
    aName.RemoveExtension();
    aName.RemovePath();
    
    Log("Sprite [ %s ] Sz(%.1fx%.1f) Tex[%.3f, %.3f, %.3f, %.3f], Rec[%.1f, %.1f, %.1f, %.1f]\n", aName.c(), mWidth, mHeight, mTextureRect.GetStartU(), mTextureRect.GetStartV(), mTextureRect.GetEndU(), mTextureRect.GetEndV(), mTextureRect.GetStartX(), mTextureRect.GetStartY(), mTextureRect.GetEndX(), mTextureRect.GetEndY());
    
    
}



