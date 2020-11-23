//=============================================================================
//
// UI�N���X [ui.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "ui.h"

#ifdef IMGUI_ON     // ImGui���I���ɂ��Ă��邩

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "file.h"

//=============================================================================
// [CUI] �R���X�g���N�^
//=============================================================================
CUI::CUI()
{
}

//=============================================================================
// [~CUI] �f�X�g���N�^
//=============================================================================
CUI::~CUI()
{
}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
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
// [Init] ����������
//=============================================================================
void CUI::Init(HWND hWnd)
{
    // IMGUI�̐ݒ�
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    //// ���{��Ή�
    //io.Fonts->AddFontFromFileTTF(NULL, 10.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());

}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CUI::Uninit(void)
{
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

//=============================================================================
// [Update] �X�V����
//=============================================================================
void CUI::Update(void)
{

    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // IMGUI�J�n
    ImGui::Begin("Test");

    static int Value = 0;
    static int Count = 0;

    static D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    bool bGridMode = CObject::GetGridMode();



        // �{�^��
        if (ImGui::Button(" SAVE �ۑ��ق���"))
        {
            CFile::Writing();
        }
        //ImGui::InputInt("value", &Value);// �J�E���^

        ImGui::DragFloat3("POS", pos, 0.1f, 0.0f, 500.0f);      // �ʒu
        ImGui::DragFloat3("ROT", pos, 0.1f, 0.0f, 500.0f);      // �p�x

        // �O���b�h���[�h�ύX
        if (ImGui::Checkbox("GridMode", &bGridMode))
        {
            CObject::GridTransform();
        }

        ImGui::Text("%d", Count);

        ImGui::DragInt("Value", &Value, 1, 0, 100);// �o�[�̂��

        Manual();// ������@�\��

    ImGui::End();// �I���
    ImGui::EndFrame();

    // �l�̐ݒ�
    CObject::SetGridMode(bGridMode);
}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CUI::Draw(void)
{
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}


//=============================================================================
// [Manual] ������@
//=============================================================================
void CUI::Manual(void)
{
    // IMGUI�J�n
    ImGui::Begin("Manual");
    ImGui::Text("F1:SAVE");
    ImGui::Text("W.A,S,D:MOVE");
    ImGui::Text("ArrowKey:CAMERA");
    ImGui::End();// �I���
}
#endif // IMGUI_ON
