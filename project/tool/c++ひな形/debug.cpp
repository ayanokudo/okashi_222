//=============================================================================
//
// デバッグ処理 [debug.cpp]
// Author : AYANO KUDO
//
//=============================================================================
#include "debug.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "object.h"

//******************************************************************************
// 静的メンバ変数定義
//******************************************************************************
LPD3DXFONT CDebug::m_pFont = NULL;          // フォントへのポインタ
char CDebug::m_astr[1024] = {};

//=============================================================================
// [CDebug] コンストラクタ
//=============================================================================
CDebug::CDebug()
{

}

//=============================================================================
// [~CDebug] デストラクタ
//=============================================================================
CDebug::~CDebug()
{

}

//=============================================================================
// [Create] オブジェクトの生成
//=============================================================================
CDebug *CDebug::Create(void)
{
    // 変数宣言
    CDebug *pDebug = NULL;
    if (pDebug == NULL)
    {
        // メモリの確保
        pDebug = new CDebug();
        pDebug->Init();
    }
    return pDebug;
}

//=============================================================================
// [Init] 初期化処理
//=============================================================================
void CDebug::Init()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
    // デバッグ情報表示用フォントの生成
    D3DXCreateFont(pDevice, 22, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
}

//=============================================================================
// [Uninit] 終了処理
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
// [Print] 画面に表示
//=============================================================================
void CDebug::Print(int nX, int nY, D3DCOLOR color, const char* pFormat, ...)
{
    va_list apList;// 可変長引数を操作するための変数
    RECT rect = { 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT };

    char temp[MAX_PATH];

    va_start(apList, pFormat);                   // 可変長引数を1つの変数にまとめる
    vsprintf_s(temp, pFormat, apList);
    va_end(apList);

    // テキスト描画
    m_pFont->DrawText(NULL, temp, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0xff));
}

//=============================================================================
// [Draw] 描画処理
//=============================================================================
void CDebug::Draw()
{
    RECT rect = { 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT };
    char str[256];
    D3DXVECTOR3 pos = CObject::GetPlayer()->GetPos();
    sprintf(str, "座標:%.1f,%.1f,%.1f\n", pos.x,pos.y,pos.z);

    // テキスト描画
    m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x00, 0x00));
}