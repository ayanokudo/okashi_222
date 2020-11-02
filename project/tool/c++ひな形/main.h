//=============================================================================
//
// メインヘッダ [main.h]
// Author : 
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
//エラー除け
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800	// 警告対処用("dinput.h"の直前に定義)

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <WinSock2.h>
#include <windows.h>
#include "d3dx9.h"
#include <dinput.h>
#include <xaudio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <functional>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "ws2_32.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WINDOW_CLASS_NAME "AppClass" // ウインドウのクラス名
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define SCREEN_WIDTH 1280  // 画面サイズ 横
#define SCREEN_HEIGHT 720  // 画面サイズ 縦
#define NUM_POLYGON 2      // 一描画のポリゴン数
#define NUM_VERTEX 4       // 一描画の頂点数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DVECTOR pos;   // 位置
	float rhw;       // rhw
	D3DCOLOR col;    // 色
	D3DXVECTOR2 tex; // テクスチャのUV座標
}VERTEX_2D;

//ポリゴンの頂点情報
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;	//色
	D3DXVECTOR2 tex;//テクスチャのUV座標
}VERTEX_3D;

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************
#ifdef _DEBUG
int GetFps(void);
#endif

#endif