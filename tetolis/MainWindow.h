#pragma once

class MainWindow
{
    HWND m_hWnd = NULL;
    HINSTANCE m_hInstance = NULL;

    const WCHAR* m_szClassNme = L"MyClassName1";
    const WCHAR* m_szTitle = L"C++�e�g���X";

    Tetris m_Tetris; // �Q�[���̖{�̂ɂȂ�I�u�W�F�N�g

public:
    MainWindow(HINSTANCE hInstance);

    void Create();

    static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
    LRESULT WndProc(UINT msg, WPARAM wp, LPARAM lp);

    LRESULT OnCreate(WPARAM wp, LPARAM lp);
    LRESULT OnDestroy(WPARAM wp, LPARAM lp);

    LRESULT OnPaint(WPARAM wp, LPARAM lp);

    LRESULT OnTimer(WPARAM wp, LPARAM lp);
    LRESULT OnKeyDown(WPARAM wp, LPARAM lp);
    LRESULT OnKeyUp(WPARAM wp, LPARAM lp);
};
