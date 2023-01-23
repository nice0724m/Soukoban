#pragma once


/*** Actionクラス ***/
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

	/*** 更新用関数 ***/
	void Update()
	{
		MainChar.Dir = DIR_NONE;
		MainChar.Touch = DIR_NONE;
		MainChar.Move = MainChar.Move;

		/*** メインキャラの四角座標情報更新 ***/
		MainChar.Cor.RiUp.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y];
		MainChar.Cor.RiDo.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y + CELL - 1];
		MainChar.Cor.LeUp.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y];
		MainChar.Cor.LeDo.Ce2 = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y + CELL - 1];
	}

	/*** 判定 ***/
	void Judge()
	{
		
		if (abs(Sta_PosX) < Act.MainChar.move )
		{
			Mov.Dash = OFF;
			Mov.X = MOVEX * 3;		// X方向移動量（通常時）
		}
		if (abs(Sta_PosX) > Act.MainChar.move )
		{
			Mov.X = 0;
		
		}

		

		/*** 移動方向判定 ***/
		if ((Key.input[KEY_INPUT_W] == 1 || Key.input[KEY_INPUT_UP] == 1)	// W(or↑)押下（長押しは無効）
#ifdef DEF_JOYPAD_VALID
			|| ((JPad.input.Buttons[1] == 128) && (JPad.input_X_Z1 == 0)) // JoyPad「×」押下（JPad.input.Buttons[1]==128）
#endif /* DEF_JOYPAD_VALID */
			)
		{
			if ((Mov.JumpState == JUMP_OFF) && ((MainChar.Touch & DIR_DO) == DIR_DO)) // ジャンプしていないとき、かつ地面に接してるとき
			{
				Mov.JumpState = JUMP_UP; // ジャンプする

#ifdef DEF_SOUND_VALID
				/*** Jump音再生 ***/
				Snd.PlayJumpSound();
#endif /*  DEF_SOUND_VALID */
			}
		}
		else if ((Key.input[KEY_INPUT_D] > 0 || Key.input[KEY_INPUT_RIGHT] > 0) // D(or→)押下（長押しも有効）
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.POV[0] > 0 && JPad.input.POV[0] < 18000) // JoyPad「→」押下
#endif /* DEF_JOYPAD_VALID */
			)
		{
			MainChar.Dir = DIR_RI;		// メインキャラ右向き
			MainChar.PicDir = DIR_RI;	// メインキャラ右向き（描画用）
		}
		else if ((Key.input[KEY_INPUT_A] > 0 || Key.input[KEY_INPUT_LEFT] > 0) // A(or←)押下（長押しも有効）
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.POV[0] > 18000 && JPad.input.POV[0] < 36000) // JoyPad「←」押下
#endif /* DEF_JOYPAD_VALID */
			)
		{
			MainChar.Dir = DIR_LE;		// メインキャラ左向き
			MainChar.PicDir = DIR_LE;	// メインキャラ左向き（描画用）
		}
		if (abs(Sta_PosX) > GOAL_POS_X)
		{
			Goal = TRUE;
		}
		/*** ゴール判定 ***/
		if (Key.input[KEY_INPUT_ESCAPE] > 0)
		{
			EndFlag = TRUE;
			
		}
		
	}

	/*** 移動計算 ***/
	void Cal()
	{
		/*** 敵1移動 ***/
		if (Enem1.Dir == DIR_RI)
		{
			Enem1.Pos.X = Enem1.Pos.X + Mov.X; /* この敵はメインキャラのダッシュしたい気分に合わせて速度を変える */
			if (Enem1.Pos.X >= WIN_MAX_X - CELL)
			{
				Enem1.Dir = DIR_LE;
			}
		}
		else
		{
			Enem1.Pos.X = Enem1.Pos.X - Mov.X; /* この敵はメインキャラのダッシュしたい気分に合わせて速度を変える */
			if (Enem1.Pos.X <= WIN_MIN_X)
			{
				Enem1.Dir = DIR_RI;
			}
		}

		/*** 敵1接触判定右 ***/
		if ((MainChar.Pos.X + CELL >= Enem1.Pos.X + ENEMY_HIT_RANGE) &&
			(MainChar.Pos.X + CELL < Enem1.Pos.X + CELL) &&
			(MainChar.Pos.Y >= Enem1.Pos.Y) &&
			(MainChar.Pos.Y < Enem1.Pos.Y + CELL))
		{
			Enem1.Touch = DIR_RI;
		}
		/*** 敵1接触判定左 ***/
		else if ((MainChar.Pos.X >= Enem1.Pos.X) &&
			(MainChar.Pos.X < Enem1.Pos.X + CELL - ENEMY_HIT_RANGE) &&
			(MainChar.Pos.Y >= Enem1.Pos.Y) &&
			(MainChar.Pos.Y < Enem1.Pos.Y + CELL))
		{
			Enem1.Touch = DIR_LE;
		}

		/*** 敵2移動 ***/
		if (Enem2.Dir == DIR_RI)
		{
			Enem2.Pos.X = Enem2.Pos.X + Mov.X; /* この敵はメインキャラのダッシュしたい気分に合わせて速度を変える */
			if (Enem2.Pos.X >= WIN_MAX_X - CELL)
			{
				Enem2.Dir = DIR_LE;
			}
		}
		else
		{
			Enem2.Pos.X = Enem2.Pos.X - Mov.X; /* この敵はメインキャラのダッシュしたい気分に合わせて速度を変える */
			if (Enem2.Pos.X <= WIN_MIN_X)
			{
				Enem2.Dir = DIR_RI;
			}
		}

		/*** 敵2接触判定右 ***/
		if ((MainChar.Pos.X + CELL >= Enem2.Pos.X + ENEMY_HIT_RANGE) &&
			(MainChar.Pos.X + CELL < Enem2.Pos.X + CELL) &&
			(MainChar.Pos.Y >= Enem2.Pos.Y) &&
			(MainChar.Pos.Y < Enem2.Pos.Y + CELL))
		{
			Enem2.Touch = DIR_RI;
		}
		/*** 敵2接触判定左 ***/
		else if ((MainChar.Pos.X >= Enem2.Pos.X) &&
			(MainChar.Pos.X < Enem2.Pos.X + CELL - ENEMY_HIT_RANGE) &&
			(MainChar.Pos.Y >= Enem2.Pos.Y) &&
			(MainChar.Pos.Y < Enem2.Pos.Y + CELL))
		{
			Enem2.Touch = DIR_LE;
		}

		/*** X方向移動計算 ***/
		/* 右移動 */
		if (MainChar.Dir == DIR_RI)
		{
			if ((MainChar.Touch & DIR_RI) != DIR_RI) // 右に行こうとしても接触しないか
			{
				if (MainChar.Pos.X < WIN_MAX_X / 2)														// キャラのX位置がウィンドウ中央より左の場合
				{
					MainChar.Pos.X = MainChar.Pos.X + Mov.X;											// キャラを右に動かす
				}
				else if ((MainChar.Pos.X >= WIN_MAX_X / 2) && (abs(Sta_PosX) < STG_X_MAX - WIN_MAX_X))	// キャラのX位置がウィンドウ中央以上右で、ステージの一番右に到達していない場合
				{
																			// ステージを左に動かす
				}
				MainChar.Move.move = true;
			}
		}
		
		/* 左移動 */
		
		else if (MainChar.Dir == DIR_LE)
		{
			if ((MainChar.Touch & DIR_LE) != DIR_LE) // 左に行こうとしても接触しないか
			{
				if (MainChar.Pos.X > STG_X_MIN)										// キャラが一番左にいない場合（キャラのX位置がステージの一番左より右）
				{
					MainChar.Pos.X = MainChar.Pos.X - Mov.X;						// キャラを左に動かす
				}
				
			}
		}
		
		Sta_PosX = Sta_PosX - Mov.X;

		/*** Y方向移動計算 ***/
		/* ジャンプ上昇 */
		if (Mov.JumpState == JUMP_UP)
		{
			Cou = Cou + 1;
			T = T_k * ((double)Cou / 50.0);
			// HUMAN PosY cal
			Mov.Y = (int)(pow(T, 1.0));
			for (int y = 1; y <= Mov.Y; y++)
			{
				if ((MOVEY_H_MAX == MainChar.Pos.Yin - MainChar.Pos.Y) ||									// ジャンプの最大高さか
					(Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y - 1] != PIC_BACK) ||			// 左上に何かある
					(Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y - 1] != PIC_BACK))	// 右上に何かある
				{
					Mov.JumpState = JUMP_GRAVITY;				// 自由落下に移行
					Cou = 0;
					break;
				}
				else
				{
					MainChar.Pos.Y = MainChar.Pos.Y - 1;
				}
			}
		}
		/* 自由落下または接触判定（下）なし */
		else if ((Mov.JumpState == JUMP_GRAVITY) || (MainChar.Touch & DIR_DO) != DIR_DO)
		{
			/* 落下していないかどうか判定 */
			if (MainChar.Pos.Y < STG_FALL_Y)
			{
				Cou = Cou + 1;
				T = T_k * ((double)Cou / 50.0);
				// HUMAN PosY cal
				Mov.Y = (int)(pow(T, 1.0));
				for (int y = 1; y <= Mov.Y; y++)
				{
					if ((Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y + CELL] != PIC_BACK) ||				// 左下に何かある
						(Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y + CELL] != PIC_BACK))	// 右下に何かある
					{
						MainChar.Pos.Yin = MainChar.Pos.Y;	// このY位置を初期Y位置に設定しなおす（ジャンプ終了後の初期位置設定）
						Mov.JumpState = JUMP_OFF;
						Cou = 0;
						break;
					}
					else // 何もなければ移動できるのでY位置を更新
					{
						MainChar.Pos.Y = MainChar.Pos.Y + 1;
					}
				}
			}
			else // 落下
			{
				MainChar.Fall = TRUE;
			}
		}
	}

	

	/*** 表示系描画 ***/
	void Disp()
	{
		/*** クリアタイムの描画 ***/
		for (int i = 0; i < RANK_DISP_NUM; i++)
		{
			DrawFormatStringFToHandle(RANK_POS_X, static_cast<float>(RANK_POS_Y + i * 10), Col.Black, Fon.FH[10], "No.%d:%6.2f s", i + 1, Sta.Rank[i]);
		}
		/*** 現在タイムの描画 ***/
		DrawFormatStringFToHandle(TIME_POS_X, TIME_POS_Y, Col.Black, Fon.FH[10], "Time:%6.2f s", static_cast<float>((GetNowCount() - Sta.StartCount) / MillSecond));
		DrawFormatStringFToHandle(TIT_ENTER_POS_X, TIT_ENTER_POS_Y, Col.Black, Fon.FH[30], "Press Esc");
	
		/*** コマンド説明の描画 ***/
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y, Col.Black, Fon.FH[10], "右移動：[→]or[D]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 10, Col.Black, Fon.FH[10], "左移動：[←]or[A]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 20, Col.Black, Fon.FH[10], "ジャンプ：[↑]or[W]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 30, Col.Black, Fon.FH[10], "ダッシュ：[F]");
		DrawFormatStringFToHandle(COMD_POS_X, COMD_POS_Y + 40, Col.Black, Fon.FH[10], "Titleに戻る：[Esc]");
	}

	/*** Actシーン終了時初期化 ***/
	void EndInit()
	{
		/*** 初期化 ***/
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

	/*** Resシーン本処理 ***/
	int Out()
	{
		int ret = SCE::SCE_04_RES;

		/*** 更新 ***/
		Update();

		/*** 判定 ***/
		Judge();

		/*** 移動計算 ***/
		Cal();
		
		/*** ステージ描画 ***/
		Sta.Out(&Sta_PosX);

	

		/*** 表示系描画 ***/
		Disp();
		if (EndFlag == TRUE)
		{

			if (Goal == TRUE)
			{

				Sta.UpdateTime();
				ret = SCE::SCE_03_CLE;
		}
			/*** タイトルシーンに移行 ***/
			else
			{
				Sta.UpdateTime();
				ret = SCE::SCE_00_TIT;
			}

	}
		return ret;
	}

	// ステージX座標
	int Sta_PosX = STG_X_MIN;

	// メインキャラ構造体
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
			int Yin = Y;			// Y方向移動前初期値
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

	// 敵キャラ構造体
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

	// 移動用構造体
	struct
	{
		int X = MOVEX;				// X方向移動量
		int Y = 0;					// Y方向移動量
		int JumpState = JUMP_OFF;	// ジャンプ状態
		bool Dash = OFF;			// ダッシュ
	}Mov;

	ENEMY Enem1;
	ENEMY Enem2;
private:
	int Goal = FALSE;
	int EndFlag = FALSE;

	// 2次関数ジャンプ用変数
	int Cou = 0;
	double T = 0.0;
	const double T_k = 20.0;

}Res;