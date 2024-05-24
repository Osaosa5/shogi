
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if(AppWindowed()){
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �������߂��Ƃ���Ń`���c�L����������iZ�[�x������Ȃ��j�΍�
	SetZBufferBitDepth(32);

	// �A�v������DXLib_Init()�O�ɂ�肽���������Ă�
	if (!BeforeDXLib_Init()) {
		return false;
	}

	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// Effekseer���I������B
	Effkseer_End();

	// DX���C�u�����J��
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gKey ^ keyold) & _gKey;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	// �����Q�[���p�b�h�p
	int padTbl[] = {
		DX_INPUT_KEY,	// 0:�L�[����
		DX_INPUT_PAD1,	// 1:�p�b�h1
		DX_INPUT_PAD2,	// 2:�p�b�h2
		DX_INPUT_PAD3,	// 3:�p�b�h3
		DX_INPUT_PAD4,	// 4:�p�b�h4
		DX_INPUT_PAD5,	// 5:�p�b�h5
		DX_INPUT_PAD6,	// 6:�p�b�h6
		DX_INPUT_PAD7,	// 7:�p�b�h7
		DX_INPUT_PAD8,	// 8:�p�b�h8
		DX_INPUT_PAD9,	// 9:�p�b�h9
		DX_INPUT_PAD10,	// 10:�p�b�h10
		DX_INPUT_PAD11,	// 11:�p�b�h11
		DX_INPUT_PAD12,	// 12:�p�b�h12
		DX_INPUT_PAD13,	// 13:�p�b�h13
		DX_INPUT_PAD14,	// 14:�p�b�h14
		DX_INPUT_PAD15,	// 15:�p�b�h15
		DX_INPUT_PAD16,	// 16:�p�b�h16
	};
	for (int i = 0; i < MUTIPAD_MAX; i++) {
		int keyold = _mPad[i]._key;
		_mPad[i]._key = GetJoypadInputState(padTbl[i]);
		_mPad[i]._trg = (_mPad[i]._key ^ keyold) & _mPad[i]._key;
	}

	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
