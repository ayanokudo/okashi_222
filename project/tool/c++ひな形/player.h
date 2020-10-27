//=============================================================================
//
// player�w�b�_ [player.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************
// �C���N���[�h
//*****************************
#include "main.h"
#include "model.h"

//*****************************
// �N���X��`
//*****************************
// �v���C���[�N���X
class CPlayer : public CModel
{
public:
    // ���f���̏��
    typedef enum
    {
        MODEL_PLAYER,
        MODEL_ENEMY,
        MODEL_MAX
    }MODEL;      // ���f���̃t�@�C����

	//�����o�֐�
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
    // �����o�֐�
	void Controll(void);
	// �����o�ϐ�
    static char*              m_apModelData[MODEL_MAX];// ���f���̏��
	static LPD3DXMESH         m_pMeshModel[MODEL_MAX];	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER       m_pBuffMatModel[MODEL_MAX];	//�}�e���A�����ւ̃|�C���^
	static DWORD              m_nNumMatModel[MODEL_MAX];	//�}�e���A�����̐�
	static LPDIRECT3DTEXTURE9 m_apTexture; // �e�N�X�`��
	D3DXVECTOR3 m_move;        // �ړ���


};

#endif