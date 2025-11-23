cmake_minimum_required(VERSION 3.10)
project(demo)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,--subsystem,console")
set(CMAKE_WIN32_EXECUTABLE ON)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_PREFIX_PATH "D:/code/SDL2-mingw/SDL2-2.30.11/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED CONFIG)   # CONFIG 可省略

# ImGui 路径
set(IMGUI_DIR D:/code/imgui)

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
    D:/code/imgui/backends/imgui_impl_opengl3.cpp
)

# 链接库
target_link_libraries(demo
    SDL2::SDL2main
    SDL2::SDL2
    # Windows 系统库
    kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib
    opengl32
)

# 解决运行时库冲突（可选）
set_property(TARGET demo PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")


# ========== 安装规则配置 ==========
# 安装可执行文件
install(TARGETS demo
    RUNTIME DESTINATION bin
)

# 自动收集并安装SDL2.dll (CMake 3.21+)
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.21")
    install(IMPORTED_RUNTIME_ARTIFACTS SDL2::SDL2
        RUNTIME DESTINATION bin
    )
else()
    # 兼容旧版CMake：手动获取DLL路径
    get_target_property(SDL2_DLL_PATH SDL2::SDL2 IMPORTED_LOCATION)
    if(EXISTS "${SDL2_DLL_PATH}")
        install(FILES ${SDL2_DLL_PATH} DESTINATION bin)
    endif()
endif()

# 安装资源文件夹（如果有）
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ 
    DESTINATION share/demo/assets
    OPTIONAL  # 如果assets不存在也不报错
)

# ========== CPack 安装程序配置 ==========
set(CPACK_PACKAGE_NAME "Demo")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VENDOR "Your Company")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SDL2 + ImGui Demo Application")

# Windows NSIS 安装程序配置
set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Demo")
set(CPACK_NSIS_DISPLAY_NAME "Demo Application")
set(CPACK_NSIS_PACKAGE_NAME "Demo")
set(CPACK_NSIS_HELP_LINK "https://your-website.com")
set(CPACK_NSIS_URL_INFO_ABOUT "https://your-website.com")
set(CPACK_NSIS_CONTACT "your-email@example.com")

# 创建桌面快捷方式和开始菜单
set(CPACK_NSIS_CREATE_DESKTOP_SHORTCUT "demo.exe")
set(CPACK_NSIS_MENU_LINKS "bin/demo.exe" "Demo" "Uninstall.exe" "Uninstall")

# 启用自动卸载旧版本
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

# 设置安装图标（可选，需要.ico文件）
# set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/installer.ico")

# 设置许可证文件（可选）
# set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")

# 必须放在最后
include(CPack)


