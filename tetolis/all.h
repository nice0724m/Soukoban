#pragma once

#include <windows.h>

// <vector>��Tetris.h�������include����
#include <vector>
using namespace std;

#include "Block.h"
#include "Tetris.h"
#include "MainWindow.h"

extern HWND hMainWnd;
/*
 * TIMER_FREE_FALL��1�b�o�߂��邲�Ƃ�1������
 * TIMER_SOFT_DROP�͉��{�^���������Ă���ԋ}������������
 * TIMER_DROP_LINES�͉����Ƀu���b�N�������Ƃ��ɂ����Ȃ��̃u���b�N�������Ă���̂ł͂Ȃ��Ԃ��󂯂�
 */
#define TIMER_FREE_FALL  100
#define TIMER_SOFT_DROP  200
#define TIMER_DROP_LINES 300


