//
//  GameObject.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/28/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "GFXApp.hpp"
#include "FObject.h"
#include "FModelDataPacked.hpp"
#include "FSprite.h"
#include "FUniforms.hpp"
#include "FAnimation.h"

class GameObject : public FObject {
public:
    GameObject();
    virtual ~GameObject();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Draw3D();
    virtual void                            Kill();
    
    FModelDataPacked                        *mModel;
    FSprite                                 *mSprite;
    
    //Each "Game Object" gets its own model view matrix,
    //which will automatically set the uniform's model
    //view matrix to the game object's MVM...
    FMatrix                                 mModelView;
    
    //Rule for how "Game Objects" control a uniform...
    //1.) They MAY NOT modify the projection matrix.
    //2.) They may entirely replace the model view matrix...
    //3.) The native draw functionality will ALWAYS bind
    //    the uniform before a draw, which means... DO NOT
    //    use the built in Graphics::MatrixModelViewSet, etc...
    FUniforms                               *mUniform;
    
    FVec2                                   GetScreenPos();
    
    //These will be the actual coordinates...
    void                                    SetPos(FVec3 pPos) { mX = pPos.mX; mY = pPos.mY; mZ = pPos.mZ; }
    void                                    SetPos(FVec2 pPos) { mX = pPos.mX; mY = pPos.mY; mZ = 0.0f; }
    
    FColor                                  mColor;
    
    float                                   mX;
    float                                   mY;
    float                                   mZ;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    float                                   mOffsetZ;
    
    float                                   mOffsetRotation2D;
    
    float                                   mOffsetRotationX;
    float                                   mOffsetRotationZ;
    
    
    
    //Rotation about Y axis (spinning around merry-go-round)
    float                                   mSpin;
    
    //Rotation about Z axis (2-D normal rotation).
    float                                   mRotation2D;
    
    float                                   mScale;
    float                                   mScaleX;
    float                                   mScaleY;
    float                                   mScaleZ;
    
    //
    float                                   mOffsetScale;
    
};

#endif /* GameObject_hpp */