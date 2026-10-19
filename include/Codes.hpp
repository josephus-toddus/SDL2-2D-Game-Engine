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
        Scene_JSON_FileOpenFailed,
        Scene_JSON_JSONSyntaxError,
        Scene_JSON_EntityHasNoEID,
        Scene_JSON_FormattingWrong,
        Scene_JSON_UnknownComponent,

        //Info
        Scene_JSON_EmptyScene,
        Scene_JSON_EntityHasNoComponents,
        Scene_JSON_EntitySuccessfullyCreated
    
    

    

    
};

}