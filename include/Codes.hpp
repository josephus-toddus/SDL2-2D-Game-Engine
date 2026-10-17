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

    

    
};

}