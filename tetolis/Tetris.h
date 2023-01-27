#pragma once

// 10��20�s
#define COLUMN_MAX 10
#define ROW_MAX 20
#define BLOCK_SIZE 20

class Tetris
{
	// ������
public:
	Tetris();
	void Init();

private:
	void InitFixedBlocks();

	// �o�b�O�����邽�߂ɕK�v�ȕϐ��Ɗ֐�
private:
	vector<TetriminoTypes> m_vectorTetriminoTypes;
	void CreateBag();

private:
	void ResetTimer();

	// �������̃e�g���~�m�̈ʒu�E��Ԃ�ۑ�����ϐ�
private:
	int m_TetriminoPositionX = 0;
	int m_TetriminoPositionY = 0;
	TetriminoTypes m_CurTetriminoType = TetriminoTypes::I;
	TetriminoAngle m_TetriminoAngle = TetriminoAngle::Angle0;

	// �������̃e�g���~�m�̈ʒu�̎擾�֘A
private:
	void GetTetriminosPosition(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionI(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionJ(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionL(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionO(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionS(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionZ(TetriminoPosition tetri[], int size);
	void GetInitBlocksPositionT(TetriminoPosition tetri[], int size);
	void GetInitBlocksRotate33(TetriminoPosition tetri[], int size, TetriminoAngle angle);
	void GetInitBlocksRotate44(TetriminoPosition tetri[], int size, TetriminoAngle angle);

	// �\���F�擾�֘A
private:
	COLORREF GetColor(Color color);
	Color GetTetriminoColor();

	// �`��֘A
public:
	POINT LeftTopBlockPosition;

	void Draw(HDC hdc);
	void GetRect(RECT* pRect);

private:
	void DrawBlock(HDC hdc, int column, int row, Color color);
	void DrawOutsideBlocks(HDC hdc);
	void DrawTetrimino(HDC hdc);
	void DrawFixedBlock(HDC hdc);

	// �ړ��֘A
public:
	BOOL m_IsSoftDrop = FALSE;

	BOOL MoveLeft();
	BOOL MoveRight();
	BOOL MoveUp();
	BOOL MoveDown();

private:
	BOOL CanMove(int x, int y);

	// ��]�֘A
public:
	BOOL RotateRight();
	BOOL RotateLeft();

private:
	BOOL CanRotate(BOOL isRight, int x, int y);

	BOOL RotateRight(int x, int y);
	BOOL RotateRight3();
	BOOL RotateRightI();

	BOOL RotateLeft(int x, int y);
	BOOL RotateLeft3();
	BOOL RotateLeftI();

	// ���C���̏����֘A
public:
	void DropLines();

private:
	Block* m_FixedBlocks[ROW_MAX][COLUMN_MAX];
	int m_DeleteLineNumbers[4];
	BOOL CheckDeletingLines();

	void FixBlocks();
	void CheckLine();
	BOOL DeleteLines(int lineNumbers[], int size);

	void NewTetrimino();
	void SetNewBlockType();

public:
	BOOL HardDrop();
	void DrawGhostBlocks(HDC hdc);

private:
	int GetHardDropCount();
	COLORREF GetGhostColor(Color color);
	void GetGhostBlocks(Block* blocks, int size);
	void DrawGhostBlock(HDC hdc, int column, int row, Color color);

	// �X�R�A�\���̂��߂̃����o�ϐ��ƃ����o�֐�
private:
	int m_Score = 0;
	void ShowScore(HDC hdc);
	HFONT SetScoreFont(HDC hdc, int height);

	// NEXT�u���b�N�̕\�������邽�߂̊֐�
private:
	void ShowNext(HDC hdc);
	void DrawNextBlock(HDC hdc, POINT leftTpo, TetriminoTypes tetriminoType);
	void GetColumnsRowsNextBlock(TetriminoTypes tetriminoType, int columns[], int rows[], int size);
	Color GetTetriminoColor(TetriminoTypes tetriminoType);

	// �z�[���h�Ɋւ��郁���o�ϐ��ƃ����o�֐�
private:
	TetriminoTypes m_holdTetrimino;
	BOOL m_CanHold = TRUE;

	void ShowHold(HDC hdc);
public:
	BOOL Hold();

	// �Q�[���I�[�o�[�ƃQ�[���Ē���̏���
private:
	BOOL m_IsGameOver = FALSE;
	void ShowGameOver(HDC hdc);

public:
	BOOL IsGameOver();
	void Retry();
};







