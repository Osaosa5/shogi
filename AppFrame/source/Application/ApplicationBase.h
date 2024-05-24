
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"

// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"


class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool BeforeDXLib_Init() { return true; }	// DXLib_Init() ���s�O�ɍs����������������΃I�[�o�[���C�h

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _lpInstance; }
	virtual int GetKey() { return _gKey; }
	virtual int GetKey(int plNum) { return _mPad[plNum]._key; }
	virtual int GetTrg() { return _gTrg; }
	virtual int GetTrg(int plNum) { return _mPad[plNum]._trg; }

protected:
	static	ApplicationBase	*_lpInstance;

	int		_gKey, _gTrg;

	// �����Q�[���p�b�h�p�̏ꍇ
	struct MULTIPAD {
		int _key;			// �L�[���͂̏��
		int _trg;			// �g���K���͂̏��
	};
#define	MUTIPAD_MAX		(17)	// �ő�ŁA�p�b�h16�{�L�[�{�[�h��17��
	MULTIPAD	_mPad[MUTIPAD_MAX];


	ModeServer* _serverMode;

};
