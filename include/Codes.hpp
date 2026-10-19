#pragma once

namespace cpuEng

{
    
enum class Code 
{
    /*
    
    format:
        Category_Subcategory__SpecificError

    */


    // Scene errors
        // Scene init
        Scene_Init__SuccessfullyLoaded,
        Scene_Init__AlreadyExists,
        Scene_Init__ReadFailed,

        // Scene change
        Scene_Change__SuccessfullyChanged,
        Scene_Change__DoesNotExist,

        // Scene json errors
        Scene_JSON__FileOpenFailed,
        Scene_JSON__JSONSyntaxError,
        Scene_JSON__EntityHasNoEID,
        Scene_JSON__FormattingWrong,
        Scene_JSON__UnknownComponent,

        //Info
        Scene_JSON__EmptyScene,
        Scene_JSON__EntityHasNoComponents,
        Scene_JSON__EntitySuccessfullyCreated,

    // Texture Manager errors

        TextureManager_SceneDoesNotExist_AddTexture,
        TextureManager_SceneDoesNotExist_AddTextureAlwaysLoaded,
        TextureManager_TextureAlreadyExists_AddTexture,
        TextureManager_TextureAlreadyExists_AddTextureAlwaysLoaded,
        TextureManager_AnimationHasNoFrames_AddAnimation,
        TextureManager_SceneDoesNotExist_AddAnimation,
        TextureManager_TextureAlreadyExists_AddAnimation,
        TextureManager_AnimationHasNoFrames_AddAnimationAlwaysLoaded,
        TextureManager_TextureAlreadyExists_AddAnimationAlwaysLoaded,
        TextureManager_SceneDoesNotExist_getTexture,
        TextureManager_TextureDoesNotExist_getTexture,
        TextureManager_TextureDoesNotExist_getTextureAlwaysLoaded,
        TextureManager_SceneDoesNotExist_getAnimation,
        TextureManager_TextureDoesNotExist_getAnimation,
        TextureManager_TextureDoesNotExist_getAnimationAlwaysLoaded,
        TextureManager_SpecifiedSceneDoesNotExist_getTexture,
        TextureManager_SpecifiedSceneDoesNotExist_getAnimation,



    

    
};

}