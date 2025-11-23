#include"tools.h"
#include"gui.h"
#include"IsUsb.h"
#include<thread>
void usb();
SEEWOTOOL GUI::HomePage()
{              // 切换成带中文的字体
        ImGui::Begin(u8"开始界面");    
        if (cnFont) ImGui::PushFont(cnFont);          // u8 保证 UTF-8 字面量
        ImGui::Text(u8"请问你要干什么");
        if (ImGui::Button(u8"设置"))
         { 
         ImGui::PopFont();
         ImGui::End();
         
        return SEEWOTOOL::SETTING;
         }
        if(ImGui::Button(u8"时间"))
        {
         ImGui::PopFont();
         ImGui::End();
         
        return SEEWOTOOL::TIME;   
        }
        ImGui::PopFont();
        ImGui::End();
        
        return SEEWOTOOL::HOME;
}

SEEWOTOOL GUI::SettingPage()
{
        ImGui::Begin(u8"设置界面");
        if (cnFont) ImGui::PushFont(cnFont);
        if(ImGui::Button(u8"开启u盘检测"))
        {
                std::thread usbThread(usb);
                usbThread.detach();
        }
        if(ImGui::Button(u8"返回"))
        {
            
            ImGui::PopFont();
            ImGui::End();
            return SEEWOTOOL::HOME;
        }
        
        ImGui::PopFont();
        ImGui::End();
        return SEEWOTOOL::SETTING;

}

SEEWOTOOL GUI::TimePage()
{
    ImGui::Begin(u8"多久上课");
    if (cnFont) ImGui::PushFont(cnFont);
    if(ImGui::Button(u8"计时"))
    {
        
        ImGui::PopFont();
        ImGui::End();
        return SEEWOTOOL::DOTIME;
    }
    if(ImGui::Button(u8"返回"))
    {
        
        ImGui::PopFont();
        ImGui::End();
        return SEEWOTOOL::HOME;
    }
   
    ImGui::PopFont();
    ImGui::End();
    return SEEWOTOOL::TIME;
}

SEEWOTOOL GUI::DoTime()
{
    ImGui::Begin(u8"计时");
    if (cnFont) ImGui::PushFont(cnFont);
    static char UserTime[128] = u8"输入时间";
    static bool start = false;
    static DWORD startTick = 0;  // 新增：记录开始时的系统滴答数
    static int totalMinutes = 0; // 新增：记录总分钟数

    if (!start) {
        ImGui::InputText(u8"输入框", UserTime, IM_ARRAYSIZE(UserTime));
        if (ImGui::Button(u8"输好了")) {
            totalMinutes = atoi(UserTime);
            startTick = GetTickCount(); // 毫秒级时间戳
            start = true;
        }
    } else {
        // 每帧计算剩余时间
        DWORD elapsed = GetTickCount() - startTick; // 已过去毫秒数
        int remaining = totalMinutes * 60000 - elapsed; // 剩余毫秒数
        
        if (remaining > 0) {
            int mins = remaining / 60000;
            int secs = (remaining % 60000) / 1000;
            ImGui::Text(u8"剩余时间: %02d分%02d秒", mins, secs);
        } else {
            ImGui::Text(u8"时间到！");
        }
        
        if (ImGui::Button(u8"重置")) {
            start = false; // 允许重新输入
        }
    }

    if (ImGui::Button(u8"返回")) {
        
        ImGui::PopFont();
        ImGui::End();
        return SEEWOTOOL::TIME;
    }

    
    ImGui::PopFont();
    ImGui::End();
    return SEEWOTOOL::DOTIME;
}


void usb()
{
    static char last=0;
    while (true)
    {
        char now = FirstUsbLetter();
        if (now != last)           // 状态变化
        {
            if (now)  OpenDrive(now);
            last = now;
        }
        Sleep(1000);
    }

}