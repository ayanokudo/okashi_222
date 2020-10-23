//=============================================================================
//
// �f�o�b�O���� [debug.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "debug.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"

//******************************************************************************
// �ÓI�����o�ϐ���`
//******************************************************************************
LPD3DXFONT CDebug::m_pFont = NULL;          // �t�H���g�ւ̃|�C���^
char CDebug::m_astr[1024] = {};

//=============================================================================
// [CDebug] �R���X�g���N�^
//=============================================================================
CDebug::CDebug()
{

}

//=============================================================================
// [~CDebug] �f�X�g���N�^
//=============================================================================
CDebug::~CDebug()
{

}

//=============================================================================
// [Create] �I�u�W�F�N�g�̐���
//=============================================================================
CDebug *CDebug::Create(void)
{
    // �ϐ��錾
    CDebug *pDebug = NULL;
    if (pDebug == NULL)
    {
        // �������̊m��
        pDebug = new CDebug();
        pDebug->Init();
    }
    return pDebug;
}

//=============================================================================
// [Init] ����������
//=============================================================================
void CDebug::Init()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    // �f�o�b�O���\���p�t�H���g�̐���
    D3DXCreateFont(pDevice, 22, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//=============================================================================
// [Uninit] �I������
//=============================================================================
void CDebug::Uninit()
{
    if (m_pFont != NULL)
    {
        m_pFont->Release();
        m_pFont = NULL;
    }
}

//=============================================================================
// [Print] ��ʂɕ\��
//=============================================================================
//void CDebug::Print(int nX, int nY, D3DCOLOR color, const char* pFormat, ...)
//{
//    va_list apList;// �ϒ������𑀍삷�邽�߂̕ϐ�
//
//
//    char temp[MAX_PATH];
//
//    va_start(apList, pFormat);                   // �ϒ�������1�̕ϐ��ɂ܂Ƃ߂�
//    vsprintf_s(temp, pFormat, apList);
//    va_end(apList);
//
//    DrawText(nX, nY, color, ()temp);
//
//}

//=============================================================================
// [Draw] �`�揈��
//=============================================================================
void CDebug::Draw()
{
    RECT rect = { 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
    char str[256];
    D3DXVECTOR3 pos = CGame::GetPlayer()->GetPos();
    sprintf(str, "���W:%.1f,%.1f,%.1f\n", pos.x,pos.y,pos.z);

    // �e�L�X�g�`��
    m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
}