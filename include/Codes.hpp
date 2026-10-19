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
        Scene_JSON__EntitySuccessfullyCreated
    
    

    

    
};

}