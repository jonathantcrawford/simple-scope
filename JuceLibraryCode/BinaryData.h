/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Background_Dark_png;
    const int            Background_Dark_pngSize = 13516;

    extern const char*   Glare_png;
    const int            Glare_pngSize = 5375;

    extern const char*   Button_FreeRun_png;
    const int            Button_FreeRun_pngSize = 2784;

    extern const char*   Button_FreeRun_Pressed_png;
    const int            Button_FreeRun_Pressed_pngSize = 2858;

    extern const char*   Button_SineDown_png;
    const int            Button_SineDown_pngSize = 2797;

    extern const char*   Button_SineDown_Pressed_png;
    const int            Button_SineDown_Pressed_pngSize = 2831;

    extern const char*   Button_SineUp_png;
    const int            Button_SineUp_pngSize = 2801;

    extern const char*   Button_SineUp_Pressed_png;
    const int            Button_SineUp_Pressed_pngSize = 2883;

    extern const char*   Buttons_Container_png;
    const int            Buttons_Container_pngSize = 1860;

    extern const char*   Dial_Background_Decay_png;
    const int            Dial_Background_Decay_pngSize = 2169;

    extern const char*   Dial_Background_Fill_png;
    const int            Dial_Background_Fill_pngSize = 2117;

    extern const char*   Dial_Background_Hue_png;
    const int            Dial_Background_Hue_pngSize = 2288;

    extern const char*   Dial_Background_xZoom_png;
    const int            Dial_Background_xZoom_pngSize = 2130;

    extern const char*   Dial_Background_yZoom_png;
    const int            Dial_Background_yZoom_pngSize = 2143;

    extern const char*   Knob_Dark_png;
    const int            Knob_Dark_pngSize = 1893;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 15;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) noexcept;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8) noexcept;
}
