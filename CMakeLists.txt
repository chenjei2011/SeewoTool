cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,--subsystem,console")
set(CMAKE_WIN32_EXECUTABLE ON)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_PREFIX_PATH "D:/code/SDL2-mingw/SDL2-2.30.11/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED CONFIG)   # CONFIG 可省略

# ImGui 路径
set(IMGUI_DIR D:/code/imgui-1.92.3)

# 包含目录
include_directories(
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    D:/code/SDL2/include
    ${CMAKE_SOURCE_DIR}/include
)

# 源文件
add_executable(demo
    main.cpp
    gui.cpp
    IsUsb.cpp
    csv.cpp
    LittleWindow.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

# 链接库
target_link_libraries(demo
    SDL2::SDL2main
    SDL2::SDL2
    # Windows 系统库
    kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib
)

# 解决运行时库冲突（可选）
set_property(TARGET demo PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")


