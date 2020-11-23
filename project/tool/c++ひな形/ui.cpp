//=============================================================================
//
// UIクラス [ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "ui.h"

#ifdef IMGUI_ON     // ImGuiをオンにしているか

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "file.h"

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

    ImGuiIO& io = ImGui::GetIO();
    //// 日本語対応
    //io.Fonts->AddFontFromFileTTF(NULL, 10.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

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

    // IMGUI開始
    ImGui::Begin("Test");

    static int Value = 0;
    static int Count = 0;

    static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    bool bGridMode = CObject::GetGridMode();



        // ボタン
        if (ImGui::Button(" SAVE 保存ほぞん"))
        {
            CFile::Writing();
        }
        //ImGui::InputInt("value", &Value);// カウンタ

        ImGui::DragFloat3("POS", pos, 0.1f, 0.0f, 500.0f);      // 位置
        ImGui::DragFloat3("ROT", pos, 0.1f, 0.0f, 500.0f);      // 角度

        // グリッドモード変更
        if (ImGui::Checkbox("GridMode", &bGridMode))
        {
            CObject::GridTransform();
        }

        ImGui::Text("%d", Count);

        ImGui::DragInt("Value", &Value, 1, 0, 100);// バーのやつ

        Manual();// 操作方法表示

    ImGui::End();// 終わり
    ImGui::EndFrame();

    // 値の設定
    CObject::SetGridMode(bGridMode);
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CUI::Draw(void)
{
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


//=============================================================================
// [Manual] 操作方法
//=============================================================================
void CUI::Manual(void)
{
    // IMGUI開始
    ImGui::Begin("Manual");
    ImGui::Text("F1:SAVE");
    ImGui::Text("W.A,S,D:MOVE");
    ImGui::Text("ArrowKey:CAMERA");
    ImGui::End();// 終わり
}
#endif // IMGUI_ON
