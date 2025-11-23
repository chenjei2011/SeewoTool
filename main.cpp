#include"tools.h"
#include"gui.h"
#include <SDL_opengl.h>
#include "imgui_impl_opengl3.h"

int main(int, char**)
{
    GUI gui;
    SEEWOTOOL NOW = HOME;
    
    // 1. 初始化 SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 2. 创建窗口
    SDL_Window* window = SDL_CreateWindow(
        "Hidden", // 这个窗口始终隐藏
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL); // 使用OpenGL上下文
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 创建OpenGL上下文
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // 启用VSync

    // 3. 初始化 ImGui（OpenGL后端）
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // 启用多视口（核心）
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoTaskBarIcon = true;

    
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    // 加载字体
    ImFont* cnFont = io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\simsun.ttc",
        18.0f,
        nullptr,
        io.Fonts->GetGlyphRangesChineseFull()
    );
    io.Fonts->Build();

    gui.cnFont = cnFont;

    // 4. 主循环
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) running = false;
        }

        ImGui_ImplOpenGL3_NewFrame(); 
        ImGui_ImplSDL2_NewFrame(); 
        ImGui::NewFrame();

        //状态机
        switch (NOW) {
            case HOME:     NOW = gui.HomePage(); break;
            case SETTING:  NOW = gui.SettingPage(); break;
            case TIME:     NOW = gui.TimePage(); break;
            case DOTIME:   NOW = gui.DoTime(); break;
        }
       

        // 4.3 渲染
        ImGui::Render();
        
        // 清除为透明黑
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        // 更新独立视口窗口
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        
        SDL_GL_SwapWindow(window); // 使用OpenGL交换缓冲区
    }

    // 5. 清理（OpenGL版本）
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

