//=============================================================================
//
// UIクラス [ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "ui.h"

#ifdef IMGUI_ON     // ImGuiをオンにしているか
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// [CUI] コンストラクタ
//=============================================================================
CUI::CUI()
{
}

//=============================================================================
// [~CUI] デストラクタ
//=============================================================================
CUI::~CUI()
{
}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CUI* CUI::Create(HWND hWnd)
{
    CUI *pUi = NULL;
    if (!pUi)
    {
        pUi = new CUI;
        pUi->Init(hWnd);
    }
    return pUi;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
void CUI::Init(HWND hWnd)
{
    // IMGUIの設定
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

}

//=============================================================================
// [Uninit] 終了処理
//=============================================================================
void CUI::Uninit(void)
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// [Update] 更新処理
//=============================================================================
void CUI::Update(void)
{
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;//サンプルのウィンドウ
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::SetNextWindowSize(ImVec2(320, 100), 0);
    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
        show_another_window = false;
    ImGui::End();

    ImGui::EndFrame();
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CUI::Draw(void)
{
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
#endif // IMGUI_ON
