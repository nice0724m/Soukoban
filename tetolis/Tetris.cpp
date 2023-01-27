
#include "all.h"
#include <time.h>

/// <summary>
/// LeftTopBlockPosition�ɍ��W���Z�b�g���Ă��܂����A
/// ����̓E�B���h�E�̂Ȃ��̃u���b�N���\������镔���̍���̍��W��]�������������������̂ł��̂悤�ɂ��܂���
/// </summary>

Tetris::Tetris()
{
    LeftTopBlockPosition.x = 150;
    LeftTopBlockPosition.y = 70;

    Init();
}

void Tetris::Init()
{
    InitFixedBlocks();

    // �Q�[���J�n���ɂ̓z�[���h����Ă���e�g���~�m�͑��݂��Ȃ�
    // �Q�[���J�n����͂��ł��z�[���h�͉\�ł���
    m_holdTetrimino = TetriminoTypes::None;
    m_CanHold = TRUE;

    for (int i = 0; i < 4; i++)
        m_DeleteLineNumbers[i] = -1;

    unsigned int now = (unsigned int)time(0);
    srand(now);

    CreateBag();
    NewTetrimino();
}

void Tetris::InitFixedBlocks()
{
    for (int row = 0; row < 20; row++)
    {
        for (int column = 0; column < 10; column++)
        {
            delete m_FixedBlocks[row][column];
            m_FixedBlocks[row][column] = NULL;
        }
    }
}

void Tetris::ResetTimer()
{
    // �^�C�}�[�����Z�b�g���A�����ɃZ�b�g����
    KillTimer(hMainWnd, TIMER_FREE_FALL);
    SetTimer(hMainWnd, TIMER_FREE_FALL, 1000, NULL);
}

Color Tetris::GetTetriminoColor()
{
    if (m_CurTetriminoType == TetriminoTypes::I)
        return Color::Aqua;
    else if (m_CurTetriminoType == TetriminoTypes::J)
        return Color::Blue;
    else if (m_CurTetriminoType == TetriminoTypes::L)
        return Color::Orange;
    else if (m_CurTetriminoType == TetriminoTypes::O)
        return Color::Yellow;
    else if (m_CurTetriminoType == TetriminoTypes::S)
        return Color::Green;
    else if (m_CurTetriminoType == TetriminoTypes::T)
        return Color::Violet;
    else if (m_CurTetriminoType == TetriminoTypes::Z)
        return Color::Red;
    else
        return Color::Gray;
}

COLORREF Tetris::GetColor(Color color)
{
    if (color == Color::Aqua)
        return 0x00FFFF00;
    else if (color == Color::Blue)
        return 0x00FF0000;
    else if (color == Color::Green)
        return 0x0000FF00;
    else if (color == Color::Orange)
        return 0x000045FF;
    else if (color == Color::Red)
        return 0x000000FF;
    else if (color == Color::Violet)
        return 0x00800080;
    else if (color == Color::Yellow)
        return 0x0000FFFF;
    else if (color == Color::Gray)
        return 0x00808080;
    else
        return 0x00AAAAAA;
}

// Tetris�N���X�̃����o�ϐ�
int m_TetriminoPositionX = 0;
int m_TetriminoPositionY = 0;
TetriminoTypes m_CurTetriminoType = TetriminoTypes::I;
TetriminoAngle m_TetriminoAngle = TetriminoAngle::Angle0;

void Tetris::GetTetriminosPosition(TetriminoPosition pos[], int size)
{
    // m_TetriminoPositionX��m_TetriminoPositionY��0�̂Ƃ���TetriminoPosition�̔z��𓾂�
    if (m_CurTetriminoType == TetriminoTypes::I)
        GetInitBlocksPositionI(pos, size);
    else if (m_CurTetriminoType == TetriminoTypes::J)
        GetInitBlocksPositionJ(pos, size);
    else if (m_CurTetriminoType == TetriminoTypes::L)
        GetInitBlocksPositionL(pos, size);
    else if (m_CurTetriminoType == TetriminoTypes::O)
        GetInitBlocksPositionO(pos, size);
    else if (m_CurTetriminoType == TetriminoTypes::S)
        GetInitBlocksPositionS(pos, size);
    else if (m_CurTetriminoType == TetriminoTypes::T)
        GetInitBlocksPositionT(pos, size);
    else if (m_CurTetriminoType == TetriminoTypes::Z)
        GetInitBlocksPositionZ(pos, size);

    // ��]������BO�~�m�͉�]���Ȃ��BI�~�m�ȊO��3�~3�AI�~�m��4�~4�Ȃ̂ŕ����ď���������
    if (m_CurTetriminoType != TetriminoTypes::I)
        GetInitBlocksRotate33(pos, size, m_TetriminoAngle);
    else if (m_CurTetriminoType == TetriminoTypes::I)
        GetInitBlocksRotate44(pos, size, m_TetriminoAngle);

    // m_TetriminoPositionX��m_TetriminoPositionY�����݂̒l�̏ꍇ��TetriminoPosition�̔z��𓾂�
    for (int i = 0; i < size; i++)
    {
        pos[i].m_column += m_TetriminoPositionX;
        pos[i].m_row += m_TetriminoPositionY;
    }
}

void Tetris::GetInitBlocksPositionI(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 0;
    pos[0].m_row = 1;

    pos[1].m_column = 1;
    pos[1].m_row = 1;

    pos[2].m_column = 2;
    pos[2].m_row = 1;

    pos[3].m_column = 3;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksPositionJ(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 0;
    pos[0].m_row = 0;

    pos[1].m_column = 0;
    pos[1].m_row = 1;

    pos[2].m_column = 1;
    pos[2].m_row = 1;

    pos[3].m_column = 2;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksPositionL(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 2;
    pos[0].m_row = 0;

    pos[1].m_column = 0;
    pos[1].m_row = 1;

    pos[2].m_column = 1;
    pos[2].m_row = 1;

    pos[3].m_column = 2;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksPositionO(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 1;
    pos[0].m_row = 0;

    pos[1].m_column = 1;
    pos[1].m_row = 1;

    pos[2].m_column = 2;
    pos[2].m_row = 0;

    pos[3].m_column = 2;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksPositionS(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 1;
    pos[0].m_row = 0;

    pos[1].m_column = 2;
    pos[1].m_row = 0;

    pos[2].m_column = 0;
    pos[2].m_row = 1;

    pos[3].m_column = 1;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksPositionT(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 1;
    pos[0].m_row = 0;

    pos[1].m_column = 0;
    pos[1].m_row = 1;

    pos[2].m_column = 1;
    pos[2].m_row = 1;

    pos[3].m_column = 2;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksPositionZ(TetriminoPosition pos[], int size)
{
    if (size != 4)
        return;

    pos[0].m_column = 0;
    pos[0].m_row = 0;

    pos[1].m_column = 1;
    pos[1].m_row = 0;

    pos[2].m_column = 1;
    pos[2].m_row = 1;

    pos[3].m_column = 2;
    pos[3].m_row = 1;
}

void Tetris::GetInitBlocksRotate33(TetriminoPosition pos[], int size, TetriminoAngle angle)
{
    if (size != 4)
        return;

    if (angle == TetriminoAngle::Angle90)
    {
        for (int i = 0; i < size; i++)
        {
            int x = pos[i].m_column;
            int y = pos[i].m_row;
            pos[i].m_column = 3 - y - 1;
            pos[i].m_row = x;
        }
    }
    else if (angle == TetriminoAngle::Angle180)
    {
        for (int i = 0; i < size; i++)
        {
            int x = pos[i].m_column;
            int y = pos[i].m_row;
            pos[i].m_column = 3 - x - 1;
            pos[i].m_row = 3 - y - 1;
        }
    }
    else if (angle == TetriminoAngle::Angle270)
    {
        for (int i = 0; i < size; i++)
        {
            int x = pos[i].m_column;
            int y = pos[i].m_row;
            pos[i].m_column = y;
            pos[i].m_row = 3 - x - 1;
        }
    }
}

void Tetris::GetInitBlocksRotate44(TetriminoPosition pos[], int size, TetriminoAngle angle)
{
    if (size != 4)
        return;

    if (angle == TetriminoAngle::Angle90)
    {
        for (int i = 0; i < size; i++)
        {
            int x = pos[i].m_column;
            int y = pos[i].m_row;
            pos[i].m_column = 4 - y - 1;
            pos[i].m_row = x;
        }
    }
    else if (angle == TetriminoAngle::Angle180)
    {
        for (int i = 0; i < size; i++)
        {
            int x = pos[i].m_column;
            int y = pos[i].m_row;
            pos[i].m_column = 4 - x - 1;
            pos[i].m_row = 4 - y - 1;
        }
    }
    else if (angle == TetriminoAngle::Angle270)
    {
        for (int i = 0; i < size; i++)
        {
            int x = pos[i].m_column;
            int y = pos[i].m_row;
            pos[i].m_column = y;
            pos[i].m_row = 4 - x - 1;
        }
    }
}

void Tetris::DrawBlock(HDC hdc, int column, int row, Color color)
{
    if (row < 0) {
        return;

    }
    COLORREF colorref = GetColor(color);

    // �y���ƃu���V�𐶐��E�I��
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hBrush = CreateSolidBrush(colorref);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    // 0�s0��̈ʒu�������E�B���h�E�̓����Ɉړ�������
    int x = column * BLOCK_SIZE + LeftTopBlockPosition.x;
    int y = row * BLOCK_SIZE + LeftTopBlockPosition.y;
    ::Rectangle(hdc, x, y, x + BLOCK_SIZE, y + BLOCK_SIZE);

    // �y���ƃu���V�����Ƃɖ߂�
    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    // �����ō쐬�����y���ƃu���V���폜����
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Tetris::DrawOutsideBlocks(HDC hdc)
{
    for (int row = 0; row < ROW_MAX + 1; row++)
    {
        DrawBlock(hdc, -1, row, Color::Gray);
        DrawBlock(hdc, COLUMN_MAX, row, Color::Gray);
    }
    for (int colum = -1; colum < COLUMN_MAX + 1; colum++)
        DrawBlock(hdc, colum, ROW_MAX, Color::Gray);
}

void Tetris::DrawFixedBlock(HDC hdc)
{
    for (int row = 0; row < ROW_MAX; row++)
    {
        for (int column = 0; column < COLUMN_MAX; column++)
        {
            Block* pBlock = m_FixedBlocks[row][column];

            // NULL�łȂ���΃u���b�N�����݂���Ƃ������ƂȂ̂ŕ`�悷��
            if (pBlock != NULL)
                DrawBlock(hdc, column, row, pBlock->color);
        }
    }
}

BOOL Tetris::MoveRight()
{
    if (CanMove(1, 0))
    {
        m_TetriminoPositionX += 1;
        m_TetriminoPositionY += 0;
        ResetTimer();
        return TRUE;
    }
    return FALSE;
}

BOOL Tetris::MoveUp()
{
    return 0;
}

BOOL Tetris::MoveLeft()
{
    if (CanMove(-1, 0))
    {
        m_TetriminoPositionX += -1;
        m_TetriminoPositionY += 0;
        ResetTimer();
        return TRUE;
    }
    return FALSE;
}

BOOL Tetris::MoveDown()
{
    if (CheckDeletingLines())
        return FALSE;
    
    // �\�t�g�h���b�v��1���������邽�т�1�_�ǉ�
    if (m_IsSoftDrop)
    {
        m_Score++;

        // �X�R�A���\�������̈���X�V����
        RECT rect;
        rect.left = 0;
        rect.top = 0;
        rect.right = 300;
        rect.bottom = 70;
        InvalidateRect(hMainWnd, &rect, TRUE);
    }

    ResetTimer();

    if (CanMove(0, 1))
    {
        m_TetriminoPositionX += 0;
        m_TetriminoPositionY += 1;
    }
    else
    {
        FixBlocks();
        CheckLine();
        NewTetrimino();
    }
    return TRUE;
}

void Tetris::FixBlocks()
{
    TetriminoPosition blocks[4];
    GetTetriminosPosition(blocks, 4);
    for (int i = 0; i < 4; i++)
    {
        Block* pBlock = new Block();
        pBlock->color = GetTetriminoColor();
        m_FixedBlocks[blocks[i].m_row][blocks[i].m_column] = pBlock;
    }
    m_CanHold = TRUE;
}

void Tetris::NewTetrimino()
{
    m_TetriminoAngle = TetriminoAngle::Angle0;
    m_TetriminoPositionX = 3;
    m_TetriminoPositionY = -1;
    SetNewBlockType();

    if (!CanMove(0, 0)) // ���łɌŒ肳��Ă���u���b�N�ƏՓ˂��Ă��Ȃ����H
        m_IsGameOver = TRUE;
}

void Tetris::CheckLine()
{
    int index = 0;

    // �`�F�b�N����O�ɔz��m_DeleteLineNumbers��-1�ŏ���������
    for (int i = 0; i < 4; i++)
        m_DeleteLineNumbers[i] = -1;

    for (int row = 0; row < ROW_MAX; row++)
    {
        BOOL isComplete = TRUE;
        for (int column = 0; column < COLUMN_MAX; column++)
        {
            // �����s�ɂЂƂł�NULL������΂��̕������󂢂Ă���
            // ���Ȃ킿������Ă��Ȃ�
            if (m_FixedBlocks[row][column] == NULL)
            {
                isComplete = FALSE;
                break;
            }
        }
        // ���[�v���甲�����Ƃ�isComplete == TRUE�ł���΂��̒i�̓u���b�N��������Ă���Ƃ�����
        // ���̏ꍇ�͔z��ɂ��̍s�̔ԍ����i�[����
        if (isComplete)
        {
            m_DeleteLineNumbers[index] = row;
            index++;
        }
    }

    // �u���b�N���폜����B���ۂɍ폜�̏����������Ȃ�ꂽ��DeleteLines�֐���TRUE��Ԃ�
    BOOL ret = DeleteLines(m_DeleteLineNumbers, 4);
    if (ret)
    {
        // DeleteLines�֐������s���ꂽ��E�B���h�E�S�̂��ĕ`�悷��
        // �����Ƀ^�C�}�[���Z�b�g����0.1�b��ɏ�̒i�ɂ���u���b�N�����Ɉړ�������
        SetTimer(hMainWnd, TIMER_DROP_LINES, 100, NULL);
        InvalidateRect(hMainWnd, NULL, TRUE);
    }
}

BOOL Tetris::DeleteLines(int lineNumbers[], int size)
{
    BOOL done = FALSE;
    for (int i = 0; i < size; i++)
    {
        // �v�f��-1�̂Ƃ��͂Ȃɂ����Ȃ�
        // �Ȃɂ������Ƃ��͂��̊֐���TRUE��Ԃ�
        int lineNumber = lineNumbers[i];
        if (lineNumber == -1)
            continue;

        done = TRUE;

        for (int x = 0; x < COLUMN_MAX; x++)
        {
            // delete��������NULL�����B�����ɂ̓u���b�N�͂Ȃ��ƔF�������
            delete m_FixedBlocks[lineNumber][x];
            m_FixedBlocks[lineNumber][x] = NULL;
        }
    }
    return done;
}

BOOL Tetris::CheckDeletingLines()
{
    for (int i = 0; i < 4; i++)
    {
        int lineNumber = m_DeleteLineNumbers[i];
        if (lineNumber != -1)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL Tetris::CanRotate(BOOL isRight, int x, int y)
{
    TetriminoAngle nextAngle;
    if(isRight)
        nextAngle = TetriminoAngle::Angle90;
    else
        nextAngle = TetriminoAngle::Angle270;

    TetriminoPosition tetri[4];

    // m_TetriminoPositionX == 0 m_TetriminoPositionY == 0�̏�Ԃɖ߂��čl����
    GetTetriminosPosition(tetri, 4);
    for (int i = 0; i < 4; i++)
    {
        tetri[i].m_column -= m_TetriminoPositionX;
        tetri[i].m_row -= m_TetriminoPositionY;
    }

    if(m_CurTetriminoType != TetriminoTypes::I && m_CurTetriminoType != TetriminoTypes::O)
        GetInitBlocksRotate33(tetri, 4, nextAngle);
    else if (m_CurTetriminoType == TetriminoTypes::I)
        GetInitBlocksRotate44(tetri, 4, nextAngle);

    // SRS��K�p�����ꍇ�̉�]���̃Y����������
    for (int i = 0; i < 4; i++)
    {
        tetri[i].m_column += x;
        tetri[i].m_row += y;
    }

    // ���݂�m_TetriminoPositionX��m_TetriminoPositionY�̕��������s�ړ�������
    for (int i = 0; i < 4; i++)
    {
        tetri[i].m_column += m_TetriminoPositionX;
        tetri[i].m_row += m_TetriminoPositionY;
    }

    // ����ŉ�]��̃u���b�N�̍��W���擾�ł���
    //�@��͓����蔻��������Ȃ�
    // �t�B�[���h�̊O�ɏo����A���łɌŒ肳��Ă���u���b�N������ꍇ�͈ړ��E��]�ł��Ȃ�
    for (int i = 0; i < 4; i++)
    {
        if (tetri[i].m_column > COLUMN_MAX - 1)
            return FALSE;
        if (tetri[i].m_column < 0)  
            return FALSE;
        if (tetri[i].m_row > ROW_MAX - 1)
            return FALSE;
        if (m_FixedBlocks[tetri[i].m_row][tetri[i].m_column] != NULL)
            return FALSE;
    }
    return TRUE;
}
BOOL Tetris::RotateRight()
{
    BOOL ret = FALSE;
    if (m_CurTetriminoType != TetriminoTypes::I && m_CurTetriminoType != TetriminoTypes::O)
    {
        ret = RotateRight3();
        if (ret)
            ResetTimer();
    }
    else if (m_CurTetriminoType == TetriminoTypes::I)
    {
        ret = RotateRightI();
        if (ret)
            ResetTimer();
    }

    return ret;
}

BOOL Tetris::RotateRight3()
{
    if (CanRotate(TRUE, 0, 0))
        return RotateRight(0, 0);

    if (m_TetriminoAngle == TetriminoAngle::Angle0)
    {
        if (CanRotate(TRUE, -1, 0))
            return RotateRight(-1, 0);
        if (CanRotate(TRUE, -1, -1))
            return RotateRight(-1, -1);
        if (CanRotate(TRUE, 0, 2))
            return RotateRight(0, 2);
        if (CanRotate(TRUE, -1, 2))
            return RotateRight(-1, 2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle90)
    {
        if (CanRotate(TRUE, 1, 0))
            return RotateRight(1, 0);
        if (CanRotate(TRUE, 1, 1))
            return RotateRight(1, 1);
        if (CanRotate(TRUE, 0, -2))
            return RotateRight(0, -2);
        if (CanRotate(TRUE, 1, -2))
            return RotateRight(1, -2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle180)
    {
        if (CanRotate(TRUE, 1, 0))
            return RotateRight(1, 0);
        if (CanRotate(TRUE, 1, -1))
            return RotateRight(1, -1);
        if (CanRotate(TRUE, 0, 2))
            return RotateRight(0, 2);
        if (CanRotate(TRUE, 1, 2))
            return RotateRight(1, 2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle270)
    {
        if (CanRotate(TRUE, -2, 0))
            return RotateRight(-2, 0);
        if (CanRotate(TRUE, -2, 1))
            return RotateRight(-2, 1);
        if (CanRotate(TRUE, 0, -2))
            return RotateRight(0, -2);
        if (CanRotate(TRUE, -1, -2))
            return RotateRight(-1, -2);
    }
    return FALSE;
}

BOOL Tetris::RotateRightI()
{
    if (CanRotate(TRUE, 0, 0))
        return RotateRight(0, 0);

    if (m_TetriminoAngle == TetriminoAngle::Angle0)
    {
        if (CanRotate(TRUE, -2, 0))
            return RotateRight(-2, 0);
        if (CanRotate(TRUE, 1, 0))
            return RotateRight(1, 0);
        if (CanRotate(TRUE, -2, 1))
            return RotateRight(-2, 1);
        if (CanRotate(TRUE, 1, -2))
            return RotateRight(1, -2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle90)
    {
        if (CanRotate(TRUE, -1, 0))
            return RotateRight(-1, 0);
        if (CanRotate(TRUE, 2, 0))
            return RotateRight(2, 0);
        if (CanRotate(TRUE, -1, -2))
            return RotateRight(-1, -2);
        if (CanRotate(TRUE, 2, 1))
            return RotateRight(2, 1);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle180)
    {
        if (CanRotate(TRUE, 2, 0))
            return RotateRight(2, 0);
        if (CanRotate(TRUE, -1, 0))
            return RotateRight(-1, 0);
        if (CanRotate(TRUE, 2, -1))
            return RotateRight(2, -1);
        if (CanRotate(TRUE, -1, 2))
            return RotateRight(-1, 2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle270)
    {
        if (CanRotate(TRUE, -2, 0))
            return RotateRight(-2, 0);
        if (CanRotate(TRUE, 1, 0))
            return RotateRight(1, 0);
        if (CanRotate(TRUE, 1, 2))
            return RotateRight(1, 2);
        if (CanRotate(TRUE, -2, -1))
            return RotateRight(-2, -1);
    }
    return FALSE;
}

BOOL Tetris::RotateRight(int x, int y)
{
    m_TetriminoPositionX += x;
    m_TetriminoPositionY += y;

    if (m_TetriminoAngle == TetriminoAngle::Angle0)
        m_TetriminoAngle = TetriminoAngle::Angle90;
    else if (m_TetriminoAngle == TetriminoAngle::Angle90)
        m_TetriminoAngle = TetriminoAngle::Angle180;
    else if (m_TetriminoAngle == TetriminoAngle::Angle180)
        m_TetriminoAngle = TetriminoAngle::Angle270;
    else if (m_TetriminoAngle == TetriminoAngle::Angle270)
        m_TetriminoAngle = TetriminoAngle::Angle0;

    return TRUE;
}

BOOL Tetris::RotateLeft()
{
    BOOL ret = FALSE;
    if (m_CurTetriminoType != TetriminoTypes::I && m_CurTetriminoType != TetriminoTypes::O)
    {
        ret = RotateLeft3();
        if (ret)
            ResetTimer();
    }
    else if (m_CurTetriminoType == TetriminoTypes::I)
    {
        ret = RotateLeftI();
        if (ret)
            ResetTimer();
    }
    return ret;
}

BOOL Tetris::RotateLeft3()
{
    if (CanRotate(FALSE, 0, 0))
        return RotateLeft(0, 0);

    if (m_TetriminoAngle == TetriminoAngle::Angle0)
    {
        if (CanRotate(FALSE, 1, 0))
            return RotateLeft(1, 0);
        if (CanRotate(FALSE, 1, -1))
            return RotateLeft(1, -1);
        if (CanRotate(FALSE, 0, 2))
            return RotateLeft(0, 2);
        if (CanRotate(FALSE, 1, 2))
            return RotateLeft(1, 2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle90)
    {
        if (CanRotate(FALSE, 1, 0))
            return RotateLeft(1, 0);
        if (CanRotate(FALSE, 1, 1))
            return RotateLeft(1, 1);
        if (CanRotate(FALSE, 0, -2))
            return RotateLeft(0, -2);
        if (CanRotate(FALSE, 1, -2))
            return RotateLeft(1, -2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle180)
    {
        if (CanRotate(FALSE, -1, 0))
            return RotateLeft(-1, 0);
        if (CanRotate(FALSE, -1, -1))
            return RotateLeft(-1, -1);
        if (CanRotate(FALSE, 0, 2))
            return RotateLeft(0, 2);
        if (CanRotate(FALSE, -1, 2))
            return RotateLeft(-1, 2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle270)
    {
        if (CanRotate(FALSE, -1, 0))
            return RotateLeft(-1, 0);
        if (CanRotate(FALSE, -1, 1))
            return RotateLeft(-1, 1);
        if (CanRotate(FALSE, 0, -2))
            return RotateLeft(0, -2);
        if (CanRotate(FALSE, -1, -2))
            return RotateLeft(-1, -2);
    }
    return FALSE;
}

BOOL Tetris::RotateLeftI()
{
    if (CanRotate(FALSE, 0, 0))
        return RotateLeft(0, 0);

    if (m_TetriminoAngle == TetriminoAngle::Angle0)
    {
        if (CanRotate(FALSE, -1, 0))
            return RotateLeft(-1, 0);
        if (CanRotate(FALSE, 2, 0))
            return RotateLeft(2, 0);
        if (CanRotate(FALSE, -2, -2))
            return RotateLeft(-2, -2);
        if (CanRotate(FALSE, 2, 1))
            return RotateLeft(2, 1);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle90)
    {
        if (CanRotate(FALSE, 2, 0))
            return RotateLeft(2, 0);
        if (CanRotate(FALSE, -1, 0))
            return RotateLeft(-1, 0);
        if (CanRotate(FALSE, 2, -1))
            return RotateLeft(2, -1);
        if (CanRotate(FALSE, -1, 2))
            return RotateLeft(-1, 2);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle180)
    {
        if (CanRotate(FALSE, 1, 0))
            return RotateLeft(1, 0);
        if (CanRotate(FALSE, -2, 0))
            return RotateLeft(-2, 0);
        if (CanRotate(FALSE, 1, 2))
            return RotateLeft(1, 2);
        if (CanRotate(FALSE, -2, -1))
            return RotateLeft(-2, -1);
    }
    else if (m_TetriminoAngle == TetriminoAngle::Angle270)
    {
        if (CanRotate(FALSE, 1, 0))
            return RotateLeft(1, 0);
        if (CanRotate(FALSE, -2, 0))
            return RotateLeft(-2, 0);
        if (CanRotate(FALSE, -2, 1))
            return RotateLeft(-2, 1);
        if (CanRotate(FALSE, 1, -2))
            return RotateLeft(1, -2);
    }
    return FALSE;
}

BOOL Tetris::RotateLeft(int x, int y)
{
    m_TetriminoPositionX += x;
    m_TetriminoPositionY += y;

    if (m_TetriminoAngle == TetriminoAngle::Angle0)
        m_TetriminoAngle = TetriminoAngle::Angle270;
    else if (m_TetriminoAngle == TetriminoAngle::Angle90)
        m_TetriminoAngle = TetriminoAngle::Angle0;
    else if (m_TetriminoAngle == TetriminoAngle::Angle180)
        m_TetriminoAngle = TetriminoAngle::Angle90;
    else if (m_TetriminoAngle == TetriminoAngle::Angle270)
        m_TetriminoAngle = TetriminoAngle::Angle180;

    return TRUE;
}

int Tetris::GetHardDropCount()
{
    TetriminoPosition blocks[4];
    GetTetriminosPosition(blocks, 4);

    int count = 0;
    while (true)
    {
        BOOL failure = FALSE;
        for (int i = 0; i < 4; i++)
        {
            blocks[i].m_row++;

            if (0 <= blocks[i].m_row && blocks[i].m_row < ROW_MAX && 0 <= blocks[i].m_column && blocks[i].m_column < COLUMN_MAX)
            {
                if (blocks[i].m_row < ROW_MAX && m_FixedBlocks[blocks[i].m_row][blocks[i].m_column] != NULL)
                {
                    failure = TRUE;
                }
            }
            else
                failure = TRUE;

            if (failure)
                break;
        }
        if (!failure)
            count++;
        else
            break;
    }
    return count;
}

void Tetris::Draw(HDC hdc)
{
    DrawGhostBlocks(hdc);

    DrawFixedBlock(hdc);
    DrawOutsideBlocks(hdc);
    DrawTetrimino(hdc);

    ShowScore(hdc);
    ShowNext(hdc);
    ShowHold(hdc);

    if (m_IsGameOver)
        ShowGameOver(hdc);
}

void Tetris::DrawGhostBlock(HDC hdc, int column, int row, Color color)
{
    COLORREF colorref = GetGhostColor(color);

    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hBrush = CreateSolidBrush(colorref);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    int x = column * BLOCK_SIZE + LeftTopBlockPosition.x;
    int y = row * BLOCK_SIZE + LeftTopBlockPosition.y;
    ::Rectangle(hdc, x, y, x + BLOCK_SIZE, y + BLOCK_SIZE);

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);

    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Tetris::DrawGhostBlocks(HDC hdc)
{
   /* for (int row = 0; row < ROW_MAX + 1; row++)
    {
        DrawBlock(hdc, -1, row, Color::Gray);
        DrawBlock(hdc, COLUMN_MAX, row, Color::Gray);
    }
    for (int colum = -1; colum < COLUMN_MAX + 1; colum++)
        DrawBlock(hdc, colum, ROW_MAX, Color::Gray);*/

    Block blocks[4];
    GetGhostBlocks(blocks, 4);
    for (int i = 0; i < 4; i++)
        DrawGhostBlock(hdc, blocks[i].m_column, blocks[i].m_row, blocks[i].color);
}

void Tetris::DrawTetrimino(HDC hdc)
{
    TetriminoPosition position[4];

    // ���݂̃e�g���~�m�̈ʒu�ƐF���擾����
    GetTetriminosPosition(position, 4);
    Color color = GetTetriminoColor();

    // �擾�����ʒu��DrawBlock�֐��ɂ킽���ĕ`�悷��
    for (int i = 0; i < 4; i++)
        DrawBlock(hdc, position[i].m_column, position[i].m_row, color);

    for (int row = 0; row < ROW_MAX; row++)
    {
        for (int column = 0; column < COLUMN_MAX; column++)
        {
            Block* pBlock = m_FixedBlocks[row][column];

            // NULL�łȂ���΃u���b�N�����݂���Ƃ������ƂȂ̂ŕ`�悷��
            if (pBlock != NULL)
                DrawBlock(hdc, column, row, pBlock->color);
        }
    }
}

void Tetris::GetGhostBlocks(Block* blocks, int size)
{
    TetriminoPosition pos[4];
    GetTetriminosPosition(pos, 4);
    int fallCount = GetHardDropCount();

    for (int i = 0; i < 4; i++)
    {
        blocks[i].m_column = pos[i].m_column;
        blocks[i].m_row = pos[i].m_row + fallCount;
        blocks[i].color = GetTetriminoColor(); // �������̃e�g���~�m�̐F���i�[���Ă���
    }
}

COLORREF Tetris::GetGhostColor(Color color)
{
    if (color == Color::Aqua)
        return 0x00404000;
    else if (color == Color::Blue)
        return 0x00800000;
    else if (color == Color::Green)
        return 0x00004000;
    else if (color == Color::Orange)
        return 0x00001040;
    else if (color == Color::Red)
        return 0x00000040;
    else if (color == Color::Violet)
        return 0x00200020;
    else if (color == Color::Yellow)
        return 0x00004040;
    else
        return 0x00808080;
}

void Tetris::GetRect(RECT* pRect)
{
    pRect->left = LeftTopBlockPosition.x;
    pRect->top = LeftTopBlockPosition.y;
    pRect->right = LeftTopBlockPosition.x + BLOCK_SIZE * COLUMN_MAX;
    pRect->bottom = LeftTopBlockPosition.y + BLOCK_SIZE * ROW_MAX;
}

BOOL Tetris::HardDrop()
{
    int fallCount = GetHardDropCount();
    m_Score += fallCount * 2; //�@�X�R�A�ǉ�

    m_TetriminoPositionY += fallCount;
    InvalidateRect(hMainWnd, NULL, TRUE);
    FixBlocks();
    return TRUE;
}

void Tetris::DropLines()
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        // �z�� m_DeleteLineNumbers�̂Ȃ���-1�ȊO�̒l������ꍇ�A
        // ���̍s�͏�ɂ���u���b�N�ŋl�߂���
        int lineNumber = m_DeleteLineNumbers[i];
        if (lineNumber == -1)
        {
            continue;
        }

        for (int x = 0; x < COLUMN_MAX; x++)
        {
            // ���̍s���ЂƂ�ɂ���u���b�N�Ŗ��߂�
            for (int row = lineNumber; row >= 1; row--)
            {
                m_FixedBlocks[row][x] = m_FixedBlocks[row - 1][x];
            }
            // ��ԏ�̍s��NULL��������B�K����ԏ�̍s����
            m_FixedBlocks[0][x] = NULL;
        }
        count++;
        m_DeleteLineNumbers[i] = -1;
    }

    // 1�񂾂��������ꍇ��40�_�A2��:100�_�A3��:300�_�A4��:1200�_
    if (count == 1)
        m_Score += 40;
    if (count == 2)
        m_Score += 100;
    if (count == 3)
        m_Score += 300;
    if (count == 4)
        m_Score += 1200;

    KillTimer(hMainWnd, TIMER_DROP_LINES);
}

void Tetris::CreateBag()
{
    if (m_vectorTetriminoTypes.size() > 7)
        return;

    vector<TetriminoTypes> v;
    v.push_back(TetriminoTypes::I);
    v.push_back(TetriminoTypes::J);
    v.push_back(TetriminoTypes::L);
    v.push_back(TetriminoTypes::O);
    v.push_back(TetriminoTypes::S);
    v.push_back(TetriminoTypes::T);
    v.push_back(TetriminoTypes::Z);

    while (true)
    {
        int size = v.size();
        if (size == 0)
            break;
        int type = rand() % size;
        TetriminoTypes selectedType = v[type];
        m_vectorTetriminoTypes.push_back(selectedType);
        v.erase(v.begin() + type);
    }
}

void Tetris::SetNewBlockType()
{
    if (m_IsGameOver)
        return;

    m_CurTetriminoType = m_vectorTetriminoTypes[0];
    m_vectorTetriminoTypes.erase(m_vectorTetriminoTypes.begin());

    CreateBag();
    InvalidateRect(hMainWnd, NULL, TRUE);
}

void Tetris::ShowNext(HDC hdc)
{
    // ������u�m�d�w�s�v��\��
    SetTextColor(hdc, RGB(255, 255, 255));
    HFONT hFont = SetScoreFont(hdc, 16);
    HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);
    const WCHAR* str = L"�m�d�w�s";

    TextOut(hdc, 400, 50, str, lstrlen(str));
    SelectObject(hdc, hFontOld);
    DeleteObject(hFont);

    // �e�g���~�m��\������ꏊ�����߂�
    // ���܂̂Ƃ���i400, 100�j�A���Ƃ͂x���W��80�����₵�Ă����̂��悳����
    POINT leftTop;
    leftTop.x = 400;
    leftTop.y = 100;
    DrawNextBlock(hdc, leftTop, m_vectorTetriminoTypes[0]);

    leftTop.y = 180;
    DrawNextBlock(hdc, leftTop, m_vectorTetriminoTypes[1]);

    leftTop.y = 260;
    DrawNextBlock(hdc, leftTop, m_vectorTetriminoTypes[2]);

    leftTop.y = 340;
    DrawNextBlock(hdc, leftTop, m_vectorTetriminoTypes[3]);
}

void Tetris::DrawNextBlock(HDC hdc, POINT leftTpo, TetriminoTypes tetriminoType)
{
    COLORREF colorref = GetColor(GetTetriminoColor(tetriminoType));
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
    HBRUSH hBrush = CreateSolidBrush(colorref);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

    int columns[4];
    int rows[4];
    GetColumnsRowsNextBlock(tetriminoType, columns, rows, 4);

    int blockSize = 16; // �t�B�[���h�ɕ\������Ă�����́i=20�j����⏬���߂̃T�C�Y��
    for (int i = 0; i < 4; i++)
    {
        int x = columns[i] * blockSize + leftTpo.x;
        int y = rows[i] * blockSize + leftTpo.y;
        ::Rectangle(hdc, x, y, x + blockSize, y + blockSize);
    }

    SelectObject(hdc, hOldPen);
    SelectObject(hdc, hOldBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

void Tetris::GetColumnsRowsNextBlock(TetriminoTypes tetriminoType, int columns[], int rows[], int size)
{
    if (size != 4)
        return;

    if (tetriminoType == TetriminoTypes::I)
    {
        columns[0] = 0;
        columns[1] = 1;
        columns[2] = 2;
        columns[3] = 3;
        rows[0] = 1;
        rows[1] = 1;
        rows[2] = 1;
        rows[3] = 1;
        return;
    }
    if (tetriminoType == TetriminoTypes::J)
    {
        columns[0] = 0;
        columns[1] = 0;
        columns[2] = 1;
        columns[3] = 2;
        rows[0] = 0;
        rows[1] = 1;
        rows[2] = 1;
        rows[3] = 1;
        return;
    }
    if (tetriminoType == TetriminoTypes::L)
    {
        columns[0] = 0;
        columns[1] = 1;
        columns[2] = 2;
        columns[3] = 2;
        rows[0] = 1;
        rows[1] = 1;
        rows[2] = 1;
        rows[3] = 0;
        return;
    }
    if (tetriminoType == TetriminoTypes::O)
    {
        columns[0] = 0;
        columns[1] = 0;
        columns[2] = 1;
        columns[3] = 1;
        rows[0] = 0;
        rows[1] = 1;
        rows[2] = 0;
        rows[3] = 1;
        return;
    }
    if (tetriminoType == TetriminoTypes::S)
    {
        columns[0] = 0;
        columns[1] = 1;
        columns[2] = 1;
        columns[3] = 2;
        rows[0] = 1;
        rows[1] = 0;
        rows[2] = 1;
        rows[3] = 0;
        return;
    }
    if (tetriminoType == TetriminoTypes::T)
    {
        columns[0] = 0;
        columns[1] = 1;
        columns[2] = 1;
        columns[3] = 2;
        rows[0] = 1;
        rows[1] = 0;
        rows[2] = 1;
        rows[3] = 1;
        return;
    }
    if (tetriminoType == TetriminoTypes::Z)
    {
        columns[0] = 0;
        columns[1] = 1;
        columns[2] = 1;
        columns[3] = 2;
        rows[0] = 0;
        rows[1] = 0;
        rows[2] = 1;
        rows[3] = 1;
        return;
    }
}

Color Tetris::GetTetriminoColor(TetriminoTypes tetriminoType)
{
    if (tetriminoType == TetriminoTypes::I)
        return Color::Aqua;
    else if (tetriminoType == TetriminoTypes::J)
        return Color::Blue;
    else if (tetriminoType == TetriminoTypes::L)
        return Color::Orange;
    else if (tetriminoType == TetriminoTypes::O)
        return Color::Yellow;
    else if (tetriminoType == TetriminoTypes::S)
        return Color::Green;
    else if (tetriminoType == TetriminoTypes::T)
        return Color::Violet;
    else if (tetriminoType == TetriminoTypes::Z)
        return Color::Red;
    else
        return Color::Gray;
}

BOOL Tetris::CanMove(int x, int y)
{
    // �ړ����TetriminoPosition�̔z����擾����
    TetriminoPosition pos[4];
    GetTetriminosPosition(pos, 4);

    // �O�ɏo����Œ肳��Ă���u���b�N�ƂԂ����Ă��܂��ꍇ�͈ړ��s�Ƃ���
    for (int i = 0; i < 4; i++)
    {
        if (pos[i].m_column + x > COLUMN_MAX - 1)
            return FALSE;
        if (pos[i].m_column + x < 0)
            return FALSE;
        if (pos[i].m_row + y > ROW_MAX - 1)
            return FALSE;

        if (pos[i].m_row + y < 0) // ���̏ꍇ�͕]�����Ȃ�
            continue;

        if (m_FixedBlocks[pos[i].m_row + y][pos[i].m_column + x] != NULL)
            return FALSE;
    }
    return TRUE;
}

void Tetris::ShowHold(HDC hdc)
{
    // ������u�g�n�k�c�v��\��
    SetTextColor(hdc, RGB(255, 255, 255));
    HFONT hFont = SetScoreFont(hdc, 16);
    HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);
    const WCHAR* str = L"�g�n�k�c";

    TextOut(hdc, 30, 50, str, lstrlen(str));
    SelectObject(hdc, hFontOld);
    DeleteObject(hFont);

    POINT leftTop;
    leftTop.x = 40;
    leftTop.y = 100;
    if (m_holdTetrimino != TetriminoTypes::None)
        DrawNextBlock(hdc, leftTop, m_holdTetrimino);
}

BOOL Tetris::Hold()
{
    // �z�[���h�ł��Ȃ��ꍇ�͂Ȃɂ����Ȃ�
    if (m_CanHold == FALSE)
      return FALSE;
        
    

    // �z�[���h������ݒu�����܂Ńz�[���h�͂ł��Ȃ��Ȃ�
    m_CanHold = FALSE;

    // �Ȃɂ��z�[���h����Ă��Ȃ��ꍇ�͗������̃e�g���~�m���z�[���h���Ď��̃e�g���~�m���~�点��
    // ���łɂȂɂ����z�[���h����Ă���ꍇ�͗������̃e�g���~�m���z�[���h����
    // ���܂܂Ńz�[���h����Ă����e�g���~�m����ԏォ��~�点��
    if (m_holdTetrimino == TetriminoTypes::None)
    {
        m_holdTetrimino = m_CurTetriminoType;
        NewTetrimino();
    }
    else
    {
        TetriminoTypes oldHold = m_holdTetrimino;
        m_holdTetrimino = m_CurTetriminoType;
        m_TetriminoAngle = TetriminoAngle::Angle0;
        m_TetriminoPositionX = 3;
        m_TetriminoPositionY = -1;

        m_CurTetriminoType = oldHold;
    }
    InvalidateRect(hMainWnd, NULL, TRUE);
    return TRUE;
}

BOOL Tetris::IsGameOver()
{
    return m_IsGameOver;
}

void Tetris::Retry()
{
    m_Score = 0;
    m_CanHold = TRUE;
    m_holdTetrimino = TetriminoTypes::None;
    m_IsGameOver = FALSE;
    m_vectorTetriminoTypes.clear();

    Init();
}

void Tetris::ShowGameOver(HDC hdc)
{
    HFONT hFont = SetScoreFont(hdc, 20);
    HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(255, 255, 255));

    const WCHAR* str1 = L"�f�`�l�d �n�u�d�q";
    TextOut(hdc, 160, 100, str1, lstrlen(str1));
    SelectObject(hdc, hFontOld);
    DeleteObject(hFont);

    hFont = SetScoreFont(hdc, 15);
    hFontOld = (HFONT)SelectObject(hdc, hFont);
    const WCHAR* str2 = L"�o�q�d�r�r �r �j�d�x";
    TextOut(hdc, 170, 130, str2, lstrlen(str2));
    SelectObject(hdc, hFontOld);
    DeleteObject(hFont);
}

HFONT Tetris::SetScoreFont(HDC hdc, int height)
{
    HFONT hFont;
    hFont = CreateFont(height, // �t�H���g����
        0, 0, 0,    // �������A�e�L�X�g�̊p�x�A�x�[�X���C���Ƃ����Ƃ̊p�x
        FW_BOLD, FALSE, FALSE, FALSE, // �t�H���g�̑����A�C�^���b�N�́A�A���_�[���C���A�ł�������
        SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,  //�����Z�b�g�A�o�͐��x�A�N���b�s���O���x
        PROOF_QUALITY, FIXED_PITCH | FF_MODERN, // �o�͕i���A�s�b�`�ƃt�@�~���[
        L"�l�r �S�V�b�N");    //���̖�
    return hFont;
};

void Tetris::ShowScore(HDC hdc)
{
    WCHAR scoreText[32];
    wsprintf(scoreText, L"SCORE  %d", m_Score);

    HFONT hFont = SetScoreFont(hdc, 20);
    HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);

    SetBkColor(hdc, RGB(0, 0, 0));
    SetTextColor(hdc, RGB(255, 255, 255));

    TextOut(hdc, 20, 20, scoreText, lstrlen(scoreText));

    SelectObject(hdc, hFontOld);
    DeleteObject(hFont);
}