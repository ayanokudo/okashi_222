//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 増澤 未来
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラス宣言
//*****************************************************************************

// サウンドクラス
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_BGM_TITLE = 0,			//タイトルBGM
		SOUND_BGM_GAME,					//ゲームBGM
		SOUND_BGM_BOSS_GAME,			//ボスバトル中BGM
		SOUND_BGM_RESULT_LOSE,			//リザルト負け兼ランキングBGM
		SOUND_BGM_RESULT_WIN,			//リザルト勝利BGM
		SOUND_BGM_TUTORIAL,				//チュートリアルBGM
		SOUND_SE_SELECT,				//選択SE
		SOUND_SE_DECISION,				//決定SE
		SOUND_SE_PL_ATTACK_BREATH,		//プレイヤー鳴き声攻撃SE
		SOUND_SE_PL_ATTACK_NAIL,		//プレイヤー引っ掻く攻撃SE
		SOUND_SE_PL_DASH,				//ダッシュ時SE
		SOUND_SE_PL_DAMAGE,				//プレイヤーダメージ時SE
		SOUND_SE_EN_ATTACK_NAIL,		//敵噛みつきSE
		SOUND_SE_EN_DAMAGE,				//敵ダメージ時SE
		SOUND_SE_BOSS_ATTACK_BREATH,	//ボスブレス攻撃SE
		SOUND_SE_BOSS_ATTACK_TAIL,		//ボス尻尾攻撃SE
		SOUND_SE_BOSS_ATTACK_NAIL,		//ボス引っ掻き攻撃SE
		SOUND_SE_ITEM_CANDY,			//キャンディ獲得時SE
		SOUND_SE_ITEM_KOBAN,			//小判獲得時SE
		SOUND_SE_ITEM_LIFE,				//回復アイテム獲得時SE
		SOUND_SE_ROGO_BGM,
		SOUND_SE_START,             // 開始時SE
		SOUND_LABEL_MAX,
	}LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);
private:
	// プロトタイプ宣言
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	// メンバ変数
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

	IXAudio2 *m_pXAudio2;								    // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice ;			    // マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
};
#endif