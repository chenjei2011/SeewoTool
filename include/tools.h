#pragma once

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include <iostream>
#include<string>

using String = std::string;

enum SEEWOTOOL
{
    HOME,
    TIME,
    DOTIME,
    SETTING
};