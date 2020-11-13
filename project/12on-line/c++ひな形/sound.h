//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : ���V ����
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X�錾
//*****************************************************************************

// �T�E���h�N���X
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_BGM_TITLE = 0,			//�^�C�g��BGM
		SOUND_BGM_GAME,					//�Q�[��BGM
		SOUND_BGM_BOSS_GAME,			//�{�X�o�g����BGM
		SOUND_BGM_RESULT_LOSE,			//���U���g�����������L���OBGM
		SOUND_BGM_RESULT_WIN,			//���U���g����BGM
		SOUND_BGM_TUTORIAL,				//�`���[�g���A��BGM
		SOUND_SE_SELECT,				//�I��SE
		SOUND_SE_DECISION,				//����SE
		SOUND_SE_PL_ATTACK_BREATH,		//�v���C���[�����U��SE
		SOUND_SE_PL_ATTACK_NAIL,		//�v���C���[�����~���U��SE
		SOUND_SE_PL_DASH,				//�_�b�V����SE
		SOUND_SE_PL_DAMAGE,				//�v���C���[�_���[�W��SE
		SOUND_SE_EN_ATTACK_NAIL,		//�G���݂�SE
		SOUND_SE_EN_DAMAGE,				//�G�_���[�W��SE
		SOUND_SE_BOSS_ATTACK_BREATH,	//�{�X�u���X�U��SE
		SOUND_SE_BOSS_ATTACK_TAIL,		//�{�X�K���U��SE
		SOUND_SE_BOSS_ATTACK_NAIL,			//�{�X�����~���U��SE
		SOUND_SE_ITEM_CANDY,			//�L�����f�B�l����SE
		SOUND_SE_ITEM_KOBAN,			//�����l����SE
		SOUND_SE_ITEM_LIFE,				//�񕜃A�C�e���l����SE
		SOUND_LABEL_MAX,
	}LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);
private:
	// �v���g�^�C�v�錾
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	// �����o�ϐ�
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];

	IXAudio2 *m_pXAudio2;								    // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice ;			    // �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif