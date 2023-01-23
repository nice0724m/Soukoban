#pragma once


/*** Action�N���X ***/
class RESULT
{
public:
	
	RESULT()
	{
		Sta_PosX = STG_X_MIN;

		MainChar.Pos.X = CHA_POS_X_INI;
		MainChar.Pos.Y = CHA_POS_Y_INI;
		MainChar.Pos.Yin = CHA_POS_Y_INI;
		MainChar.Dir = DIR_NONE;
		MainChar.PicDir = DIR_RI;
		MainChar.Touch = DIR_NONE;
		MainChar.Fall = FALSE;
		Mov.JumpState = JUMP_OFF;
		Mov.Y = 0;
		Cou = 0;

		Enem1.Pos.X = ENE1_POS_X_INI;
		Enem1.Pos.Y = ENE1_POS_Y_INI;
		Enem1.Dir = DIR_RI;
		Enem1.Touch = DIR_NONE;

		Enem2.Pos.X = ENE2_POS_X_INI;
		Enem2.Pos.Y = ENE2_POS_Y_INI;
		Enem2.Dir = DIR_RI;
		Enem2.Touch = DIR_NONE;
	

		Goal = FALSE;
		EndFlag = FALSE;
	}

	/*** �X�V�p�֐� ***/
	void Update()
	{
		MainChar.Dir = DIR_NONE;
		MainChar.Touch = DIR_NONE;
		MainChar.Move = MainChar.Move;

		/*** ���C���L�����̎l�p���W���X�V ***/
		MainChar.Cor.RiUp.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y];
		MainChar.Cor.RiDo.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y + CELL - 1];
		MainChar.Cor.LeUp.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y];
		MainChar.Cor.LeDo.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y + CELL - 1];
	}

	/*** ���� ***/
	void Judge()
	{
		
		if (abs(Sta_PosX) < Act.MainChar.move )
		{
			Mov.Dash = OFF;
			Mov.X = MOVEX * 3;		// X�����ړ��ʁi�ʏ펞�j
		}
		if (abs(Sta_PosX) > Act.MainChar.move )
		{
			Mov.X = 0;
		
		}

		

		/*** �ړ��������� ***/
		if ((Key.input[KEY_INPUT_W] == 1 || Key.input[KEY_INPUT_UP] == 1)	// W(or��)�����i�������͖����j
#ifdef DEF_JOYPAD_VALID
			|| ((JPad.input.Buttons[1] == 128) && (JPad.input_X_Z1 == 0)) // JoyPad�u�~�v�����iJPad.input.Buttons[1]==128�j
#endif /* DEF_JOYPAD_VALID */
			)
		{
			if ((Mov.JumpState == JUMP_OFF) && ((MainChar.Touch & DIR_DO) == DIR_DO)) // �W�����v���Ă��Ȃ��Ƃ��A���n�ʂɐڂ��Ă�Ƃ�
			{
				Mov.JumpState = JUMP_UP; // �W�����v����

#ifdef DEF_SOUND_VALID
				/*** Jump���Đ� ***/
				Snd.PlayJumpSound();
#endif /*  DEF_SOUND_VALID */
			}
		}
		else if ((Key.input[KEY_INPUT_D] > 0 || Key.input[KEY_INPUT_RIGHT] > 0) // D(or��)�����i���������L���j
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.POV[0] > 0 && JPad.input.POV[0] < 18000) // JoyPad�u���v����
#endif /* DEF_JOYPAD_VALID */
			)
		{
			MainChar.Dir = DIR_RI;		// ���C���L�����E����
			MainChar.PicDir = DIR_RI;	// ���C���L�����E�����i�`��p�j
		}
		else if ((Key.input[KEY_INPUT_A] > 0 || Key.input[KEY_INPUT_LEFT] > 0) // A(or��)�����i���������L���j
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.POV[0] > 18000 && JPad.input.POV[0] < 36000) // JoyPad�u���v����
#endif /* DEF_JOYPAD_VALID */
			)
		{
			MainChar.Dir = DIR_LE;		// ���C���L����������
			MainChar.PicDir = DIR_LE;	// ���C���L�����������i�`��p�j
		}
		if (abs(Sta_PosX) > GOAL_POS_X)
		{
			Goal = TRUE;
		}
		/*** �S�[������ ***/
		if (Key.input[KEY_INPUT_ESCAPE] > 0)
		{
			EndFlag = TRUE;
			
		}
		
	}

	/*** �ړ��v�Z ***/
	void Cal()
	{
		/*** �G1�ړ� ***/
		if (Enem1.Dir == DIR_RI)
		{
			Enem1.Pos.X = Enem1.Pos.X + Mov.X; /* ���̓G�̓��C���L�����̃_�b�V���������C���ɍ��킹�đ��x��ς��� */
			if (Enem1.Pos.X >= WIN_MAX_X - CELL)
			{
				Enem1.Dir = DIR_LE;
			}
		}
		else
		{
			Enem1.Pos.X = Enem1.Pos.X - Mov.X; /* ���̓G�̓��C���L�����̃_�b�V���������C���ɍ��킹�đ��x��ς��� */
			if (Enem1.Pos.X <= WIN_MIN_X)
			{
				Enem1.Dir = DIR_RI;
			}
		}

		/*** �G1�ڐG����E ***/
		if ((MainChar.Pos.X + CELL >= Enem1.Pos.X + ENEMY_HIT_RANGE) &&
			(MainChar.Pos.X + CELL < Enem1.Pos.X + CELL) &&
			(MainChar.Pos.Y >= Enem1.Pos.Y) &&
			(MainChar.Pos.Y < Enem1.Pos.Y + CELL))
		{
			Enem1.Touch = DIR_RI;
		}
		/*** �G1�ڐG���荶 ***/
		else if ((MainChar.Pos.X >= Enem1.Pos.X) &&
			(MainChar.Pos.X < Enem1.Pos.X + CELL - ENEMY_HIT_RANGE) &&
			(MainChar.Pos.Y >= Enem1.Pos.Y) &&
			(MainChar.Pos.Y < Enem1.Pos.Y + CELL))
		{
			Enem1.Touch = DIR_LE;
		}

		/*** �G2�ړ� ***/
		if (Enem2.Dir == DIR_RI)
		{
			Enem2.Pos.X = Enem2.Pos.X + Mov.X; /* ���̓G�̓��C���L�����̃_�b�V���������C���ɍ��킹�đ��x��ς��� */
			if (Enem2.Pos.X >= WIN_MAX_X - CELL)
			{
				Enem2.Dir = DIR_LE;
			}
		}
		else
		{
			Enem2.Pos.X = Enem2.Pos.X - Mov.X; /* ���̓G�̓��C���L�����̃_�b�V���������C���ɍ��킹�đ��x��ς��� */
			if (Enem2.Pos.X <= WIN_MIN_X)
			{
				Enem2.Dir = DIR_RI;
			}
		}

		/*** �G2�ڐG����E ***/
		if ((MainChar.Pos.X + CELL >= Enem2.Pos.X + ENEMY_HIT_RANGE) &&
			(MainChar.Pos.X + CELL < Enem2.Pos.X + CELL) &&
			(MainChar.Pos.Y >= Enem2.Pos.Y) &&
			(MainChar.Pos.Y < Enem2.Pos.Y + CELL))
		{
			Enem2.Touch = DIR_RI;
		}
		/*** �G2�ڐG���荶 ***/
		else if ((MainChar.Pos.X >= Enem2.Pos.X) &&
			(MainChar.Pos.X < Enem2.Pos.X + CELL - ENEMY_HIT_RANGE) &&
			(MainChar.Pos.Y >= Enem2.Pos.Y) &&
			(MainChar.Pos.Y < Enem2.Pos.Y + CELL))
		{
			Enem2.Touch = DIR_LE;
		}

		/*** X�����ړ��v�Z ***/
		/* �E�ړ� */
		if (MainChar.Dir == DIR_RI)
		{
			if ((MainChar.Touch & DIR_RI) != DIR_RI) // �E�ɍs�����Ƃ��Ă��ڐG���Ȃ���
			{
				if (MainChar.Pos.X < WIN_MAX_X / 2)														// �L������X�ʒu���E�B���h�E������荶�̏ꍇ
				{
					MainChar.Pos.X = MainChar.Pos.X + Mov.X;											// �L�������E�ɓ�����
				}
				else if ((MainChar.Pos.X >= WIN_MAX_X / 2) && (abs(Sta_PosX) < STG_X_MAX - WIN_MAX_X))	// �L������X�ʒu���E�B���h�E�����ȏ�E�ŁA�X�e�[�W�̈�ԉE�ɓ��B���Ă��Ȃ��ꍇ
				{
																			// �X�e�[�W�����ɓ�����
				}
				MainChar.Move.move = true;
			}
		}
		
		/* ���ړ� */
		
		else if (MainChar.Dir == DIR_LE)
		{
			if ((MainChar.Touch & DIR_LE) != DIR_LE) // ���ɍs�����Ƃ��Ă��ڐG���Ȃ���
			{
				if (MainChar.Pos.X > STG_X_MIN)										// �L��������ԍ��ɂ��Ȃ��ꍇ�i�L������X�ʒu���X�e�[�W�̈�ԍ����E�j
				{
					MainChar.Pos.X = MainChar.Pos.X - Mov.X;						// �L���������ɓ�����
				}
				
			}
		}
		
		Sta_PosX = Sta_PosX - Mov.X;

		/*** Y�����ړ��v�Z ***/
		/* �W�����v�㏸ */
		if (Mov.JumpState == JUMP_UP)
		{
			Cou = Cou + 1;
			T = T_k * ((double)Cou / 50.0);
			// HUMAN PosY cal
			Mov.Y = (int)(pow(T, 1.0));
			for (int y = 1; y <= Mov.Y; y++)
			{
				if ((MOVEY_H_MAX == MainChar.Pos.Yin - MainChar.Pos.Y) ||									// �W�����v�̍ő卂����
					(Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y - 1] != PIC_BACK) ||			// ����ɉ�������
					(Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y - 1] != PIC_BACK))	// �E��ɉ�������
				{
					Mov.JumpState = JUMP_GRAVITY;				// ���R�����Ɉڍs
					Cou = 0;
					break;
				}
				else
				{
					MainChar.Pos.Y = MainChar.Pos.Y - 1;
				}
			}
		}
		/* ���R�����܂��͐ڐG����i���j�Ȃ� */
		else if ((Mov.JumpState == JUMP_GRAVITY) || (MainChar.Touch & DIR_DO) != DIR_DO)
		{
			/* �������Ă��Ȃ����ǂ������� */
			if (MainChar.Pos.Y < STG_FALL_Y)
			{
				Cou = Cou + 1;
				T = T_k * ((double)Cou / 50.0);
				// HUMAN PosY cal
				Mov.Y = (int)(pow(T, 1.0));
				for (int y = 1; y <= Mov.Y; y++)
				{
					if ((Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y + CELL] != PIC_BACK) ||				// �����ɉ�������
						(Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y + CELL] != PIC_BACK))	// �E���ɉ�������
					{
						MainChar.Pos.Yin = MainChar.Pos.Y;	// ����Y�ʒu������Y�ʒu�ɐݒ肵�Ȃ����i�W�����v�I����̏����ʒu�ݒ�j
						Mov.JumpState = JUMP_OFF;
						Cou = 0;
						break;
					}
					else // �����Ȃ���Έړ��ł���̂�Y�ʒu���X�V
					{
						MainChar.Pos.Y = MainChar.Pos.Y + 1;
					}
				}
			}
			else // ����
			{
				MainChar.Fall = TRUE;
			}
		}
	}

	

	/*** �\���n�`�� ***/
	void Disp()
	{
		/*** �N���A�^�C���̕`�� ***/
		for (int i = 0; i < RANK_DISP_NUM; i++)
		{
			DrawFormatStringFToHandle(RANK_POS_X, static_cast<float>(RANK_POS_Y + i * 10), Col.Black, Fon.FH[10], "No.%d:%6.2f s", i + 1, Sta.Rank[i]);
		}
		/*** ���݃^�C���̕`�� ***/
		DrawFormatStringFToHandle(TIME_POS_X, TIME_POS_Y, Col.Black, Fon.FH[10], "Time:%6.2f s", static_cast<float>((GetNowCount() - Sta.StartCount) / MillSecond));
		DrawFormatStringFToHandle(TIT_ENTER_POS_X, TIT_ENTER_POS_Y, Col.Black, Fon.FH[30], "Press Esc");
	
		/*** �R�}���h�����̕`�� ***/
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y, Col.Black, Fon.FH[10], "�E�ړ��F[��]or[D]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 10, Col.Black, Fon.FH[10], "���ړ��F[��]or[A]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 20, Col.Black, Fon.FH[10], "�W�����v�F[��]or[W]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 30, Col.Black, Fon.FH[10], "�_�b�V���F[F]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 40, Col.Black, Fon.FH[10], "Title�ɖ߂�F[Esc]");
	}

	/*** Act�V�[���I���������� ***/
	void EndInit()
	{
		/*** ������ ***/
		Sta_PosX = STG_X_MIN;

		MainChar.Pos.X = CHA_POS_X_INI;
		MainChar.Pos.Y = CHA_POS_Y_INI;
		MainChar.Pos.Yin = CHA_POS_Y_INI;
		MainChar.Dir = DIR_NONE;
		MainChar.PicDir = DIR_RI;
		MainChar.Touch = DIR_NONE;
		MainChar.Fall = FALSE;
		Mov.JumpState = JUMP_OFF;
		Mov.Y = 0;
		Cou = 0;

		Enem1.Pos.X = ENE1_POS_X_INI;
		Enem1.Pos.Y = ENE1_POS_Y_INI;
		Enem1.Dir = DIR_RI;
		Enem1.Touch = DIR_NONE;

		Enem2.Pos.X = ENE2_POS_X_INI;
		Enem2.Pos.Y = ENE2_POS_Y_INI;
		Enem2.Dir = DIR_RI;
		Enem2.Touch = DIR_NONE;

		Goal = FALSE;
		EndFlag = FALSE;
	}

	/*** Res�V�[���{���� ***/
	int Out()
	{
		int ret = SCE::SCE_04_RES;

		/*** �X�V ***/
		Update();

		/*** ���� ***/
		Judge();

		/*** �ړ��v�Z ***/
		Cal();
		
		/*** �X�e�[�W�`�� ***/
		Sta.Out(&Sta_PosX);

	

		/*** �\���n�`�� ***/
		Disp();
		if (EndFlag == TRUE)
		{

			if (Goal == TRUE)
			{

				Sta.UpdateTime();
				ret = SCE::SCE_03_CLE;
		}
			/*** �^�C�g���V�[���Ɉڍs ***/
			else
			{
				Sta.UpdateTime();
				ret = SCE::SCE_00_TIT;
			}

	}
		return ret;
	}

	// �X�e�[�WX���W
	int Sta_PosX = STG_X_MIN;

	// ���C���L�����\����
	struct
	{
		struct 
		{
			int move = 0;
		}Move;
		struct
		{
			int X = CHA_POS_X_INI;
			int Y = CHA_POS_Y_INI;
			int Yin = Y;			// Y�����ړ��O�����l
		}Pos;
		struct
		{
			struct
			{
				int Ri = 0;
				int Up = 0;
				int Ce2 = 0;
			}RiUp;
			struct
			{
				int Le = 0;
				int Up = 0;
				int Ce2 = 0;
			}LeUp;
			struct
			{
				int Ri = 0;
				int Do = 0;
				int Ce2 = 0;
			}RiDo;
			struct
			{
				int Le = 0;
				int Do = 0;
				int Ce2 = 0;
			}LeDo;
		}Cor;

		int Dir = DIR_NONE;
		int PicDir = DIR_RI;
		int Touch = DIR_NONE;
		int Fall = FALSE;
	}MainChar;

	// �G�L�����\����
	struct ENEMY
	{
		struct
		{
			int X = 0;
			int Y = STG_X_MAX - 3 * CELL;
		}Pos;
		struct
		{
			struct
			{
				int Ri = 0;
				int Up = 0;
				int Ce = 0;
			}RiUp;
			struct
			{
				int Le = 0;
				int Up = 0;
				int Ce = 0;
			}LeUp;
			struct
			{
				int Ri = 0;
				int Do = 0;
				int Ce = 0;
			}RiDo;
			struct
			{
				int Le = 0;
				int Do = 0;
				int Ce = 0;
			}LeDo;
		}Cor;

		int Dir = DIR_NONE;
		int Touch = DIR_NONE;
	};

	// �ړ��p�\����
	struct
	{
		int X = MOVEX;				// X�����ړ���
		int Y = 0;					// Y�����ړ���
		int JumpState = JUMP_OFF;	// �W�����v���
		bool Dash = OFF;			// �_�b�V��
	}Mov;

	ENEMY Enem1;
	ENEMY Enem2;
private:
	int Goal = FALSE;
	int EndFlag = FALSE;

	// 2���֐��W�����v�p�ϐ�
	int Cou = 0;
	double T = 0.0;
	const double T_k = 20.0;

}Res;