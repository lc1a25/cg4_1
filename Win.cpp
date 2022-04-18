#include "Win.h"

LRESULT Win::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// ���b�Z�[�W�ŕ���
	switch (msg) {
	case WM_DESTROY: // �E�B���h�E���j�����ꂽ
		PostQuitMessage(0); // OS�ɑ΂��āA�A�v���̏I����`����
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); // �W���̏������s��
}

void Win::WinCreate()
{

	
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = (WNDPROC)WindowProc; // �E�B���h�E�v���V�[�W����ݒ�
	windowClass.lpszClassName = L"GO GO HighWay"; // �E�B���h�E�N���X��
	windowClass.hInstance = GetModuleHandle(nullptr); // �E�B���h�E�n���h��
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // �J�[�\���w��

	// �E�B���h�E�N���X��OS�ɓo�^
	RegisterClassEx(&windowClass);
	// �E�B���h�E�T�C�Y{ X���W Y���W ���� �c�� }
	RECT wrc = { 0, 0, window_width, window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false); // �����ŃT�C�Y�␳

	// �E�B���h�E�I�u�W�F�N�g�̐���
	 hwnd = CreateWindow(windowClass.lpszClassName, // �N���X��
		L"GO GO HighWay",			// �^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	// �W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,			// �\��X���W�iOS�ɔC����j
		CW_USEDEFAULT,			// �\��Y���W�iOS�ɔC����j
		wrc.right - wrc.left,	// �E�B���h�E����
		wrc.bottom - wrc.top,	// �E�B���h�E�c��
		nullptr,				// �e�E�B���h�E�n���h��
		nullptr,				// ���j���[�n���h��
		windowClass.hInstance,	// �Ăяo���A�v���P�[�V�����n���h��
		nullptr);				// �I�v�V����

	// �E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);

	
}
void Win::WinFinalize()
{
	// �E�B���h�E�N���X��o�^����
	UnregisterClass(windowClass.lpszClassName , windowClass.hInstance);
}

bool Win::ProcessMessage()
{
	MSG msg{};
	// ���b�Z�[�W������H
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg); // �L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg); // �v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	// ?�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}
