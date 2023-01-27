#pragma once

/*** Actionクラス ***/
class ACTION
{
public:
	ACTION()
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
		MainChar.move = MoveNo;

		

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
		MainChar.Cor.RiUp.Ce = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y];
		MainChar.Cor.RiDo.Ce = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y + CELL - 1];
		MainChar.Cor.LeUp.Ce = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y];
		MainChar.Cor.LeDo.Ce = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y + CELL - 1];
	}

	/*** 判定 ***/
	void Judge()
	{
		/*** ダッシュ判定 ***/
		if ((Key.input[KEY_INPUT_F] > 0) // F押下（長押しも有効）
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.Buttons[0] == 128) // JoyPad:「□」押下
#endif /* DEF_JOYPAD_VALID */
			)
		{
			Mov.Dash = ON;
			Mov.X = MOVEX_D;	// X方向移動量（ダッシュ時）
		}
		else
		{
			Mov.Dash = OFF;
			Mov.X = MOVEX;
			MainChar.move +=3;
			// X方向移動量（通常時）
		}

		/* メインキャラの四角の左右は、Mov.Xをもとに接触予測 */
		MainChar.Cor.RiUp.Ri = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1 + Mov.X][MainChar.Pos.Y];
		MainChar.Cor.RiDo.Ri = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1 + Mov.X][MainChar.Pos.Y + CELL - 1];
		MainChar.Cor.LeUp.Le = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX - Mov.X][MainChar.Pos.Y];
		MainChar.Cor.LeDo.Le = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX - Mov.X][MainChar.Pos.Y + CELL - 1];

		/* メインキャラの四角の上下は、Y位置の1pixel移動した場合の接触予測 */
		MainChar.Cor.RiUp.Up = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y - 1];
		MainChar.Cor.LeUp.Up = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y - 1];
		MainChar.Cor.RiDo.Do = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX + CELL - 1][MainChar.Pos.Y + CELL];
		MainChar.Cor.LeDo.Do = Sta.Cood.Pix[MainChar.Pos.X - Sta_PosX][MainChar.Pos.Y + CELL];

		/*** 接触予測判定 ***/
		// ブロック接触判定 右
		if (MainChar.Cor.RiUp.Ri != PIC_BACK || MainChar.Cor.RiDo.Ri != PIC_BACK)	// 右に行こうとした際、右上、右下の右側の属性がBack以外になるか
		{
			if (MainChar.Cor.RiUp.Ri != PIC_RECOVERY || MainChar.Cor.RiDo.Ri != PIC_RECOVERY)
			{
				MainChar.Touch |= DIR_RI;
		    }
			else
			
			{
				Gau.NowGauge += 100;
			}
			
		}
		// ブロック接触判定 左
		if (MainChar.Cor.LeUp.Le != PIC_BACK || MainChar.Cor.LeDo.Le != PIC_BACK)	// 左に行こうとした際、左上、左下の左側の属性がBack以外になるか
		{
			if (MainChar.Cor.LeUp.Le != PIC_RECOVERY || MainChar.Cor.LeDo.Le != PIC_RECOVERY)
			{
				 MainChar.Touch |= DIR_LE;
			}
			else
			{
            Gau.NowGauge += 100;
			}
			
		}
		// ブロック接触判定 上
		if (MainChar.Cor.RiUp.Up != PIC_BACK || MainChar.Cor.LeUp.Up != PIC_BACK)	// 上に行こうとした際、右上、左上の上側の属性がBack以外になるか
		{
			if (MainChar.Cor.RiUp.Up != PIC_RECOVERY || MainChar.Cor.LeUp.Up != PIC_RECOVERY)
			{
				MainChar.Touch |= DIR_UP;
			}
			else
			{
             Gau.NowGauge += 100;
			}
			
		}
		// ブロック接触判定 下
		if (MainChar.Cor.RiDo.Do != PIC_BACK || MainChar.Cor.LeDo.Do != PIC_BACK)	// 下に行こうとした際、右下、左下の下側の属性がBack以外になるか
		{
			if (MainChar.Cor.RiDo.Do != PIC_RECOVERY || MainChar.Cor.LeDo.Do != PIC_RECOVERY)
			{
			MainChar.Touch |= DIR_DO;
			}
			else
			{
             
			 Gau.NowGauge += 100;
			}
			
		}

		/*** 移動方向判定 ***/
		if ((Key.input[KEY_INPUT_W] == 1 || Key.input[KEY_INPUT_UP] == 1 )	// W(or↑)押下（長押しは無効）
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
		else if ((Key.input[KEY_INPUT_D] > 0 || Key.input[KEY_INPUT_RIGHT] > 0 ) // D(or→)押下（長押しも有効）
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.POV[0] > 0 && JPad.input.POV[0] < 18000) // JoyPad「→」押下
#endif /* DEF_JOYPAD_VALID */
			)
		{
			MainChar.Dir = DIR_RI;		// メインキャラ右向き
			MainChar.PicDir = DIR_RI;	// メインキャラ右向き（描画用）
		}
		else if ((Key.input[KEY_INPUT_A] > 0 || Key.input[KEY_INPUT_LEFT] > 0 ) // A(or←)押下（長押しも有効）
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.POV[0] > 18000 && JPad.input.POV[0] < 36000) // JoyPad「←」押下
#endif /* DEF_JOYPAD_VALID */
			)
		{
			MainChar.Dir = DIR_LE;		// メインキャラ左向き
			MainChar.PicDir = DIR_LE;	// メインキャラ左向き（描画用）
		}

		/*** ゴール判定 ***/
		if (abs(Sta_PosX) > GOAL_POS_X)
		{
			Goal = TRUE;
		}
		
		/*** 終了判定 ***/
		if ((Key.input[KEY_INPUT_ESCAPE] > 0) ||	// Esc押下
			(MainChar.Fall == TRUE) ||				// 落下判定
			(Goal == TRUE)							// ゴール判定
#ifdef DEF_JOYPAD_VALID
			|| (JPad.input.Buttons[12] == 128)		// JoyPad「PS」押下
#endif /* DEF_JOYPAD_VALID */
			)
		{
			EndFlag = TRUE;
		}
		if ((Enem1.Touch != DIR_NONE) ||			// 敵1当たり判定
			(Enem2.Touch != DIR_NONE)) 			// 敵2当たり判定
		{
			Gau.NowGauge -= 10;
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
				MainChar.Move.move = true;											// ステージを左に動かす
				}
				
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
	
	void Hp()
	{
		
		if (Gau.No >= 30)
		{
			Gau.NowGauge -= 1;
			Gau.No = 0;
		}
		Gau.No += 3;

		
	}
	void HpFitting()
	{
		if (Gau.NowGauge > 0 && Gau.NowGauge < 10)
		{
			Gau.GaugeNo = 0;
		
		}
		if (Gau.NowGauge > 10 && Gau.NowGauge < 20)
		{
			Gau.GaugeNo = 1;
		}
		if (Gau.NowGauge > 20 && Gau.NowGauge < 30)
		{
			Gau.GaugeNo = 2;
		}
		if (Gau.NowGauge > 30 && Gau.NowGauge < 40)
		{
			Gau.GaugeNo = 3;
		}
		if (Gau.NowGauge > 40 && Gau.NowGauge < 50)
		{
			Gau.GaugeNo = 4;
		}
		if (Gau.NowGauge > 50 && Gau.NowGauge < 60)
		{
			Gau.GaugeNo = 5;
		}
		if (Gau.NowGauge > 60 && Gau.NowGauge < 70)
		{
			Gau.GaugeNo = 6;
		}
		if (Gau.NowGauge > 70 && Gau.NowGauge < 100)
		{
			Gau.GaugeNo = 7;
		}
		else
		{
         Gau.GaugeNo = 7;
		}
		
	}
	/*** メインキャラ描画 ***/
	void Cha()
	{
		if (MainChar.PicDir == DIR_RI)		// 右向きの場合
		{
			DrawGraph(MainChar.Pos.X, MainChar.Pos.Y, Pic.MChara, TRUE);		// 右向きの描画
		}
		else if (MainChar.PicDir == DIR_LE)	// 左向きの場合
		{
			DrawTurnGraph(MainChar.Pos.X, MainChar.Pos.Y, Pic.MChara, TRUE);	// 左向きの描画
		}
	}

	/*** 敵描画 ***/
	void Ene()
	{
		DrawGraph(item.Pos.X, item.Pos.Y, Pic.RECOVERY, TRUE); /*** 敵1描画 ***/
		DrawGraph(Enem1.Pos.X, Enem1.Pos.Y, Pic.Enemy1, TRUE); /*** 敵1描画 ***/
		DrawGraph(Enem2.Pos.X, Enem2.Pos.Y, Pic.Enemy1, TRUE); /*** 敵2描画 ***/
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
		switch (Gau.GaugeNo)
		{
		case 0:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge, TRUE);
			EndFlag = TRUE;
			break;
		case 1:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge2, TRUE);
			break;
		case 2:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge3, TRUE);
			break;
		case 3:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge4, TRUE);
			break;
		case 4:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge5, TRUE);
			break;
		case 5:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge6, TRUE);
			break;
		case 6:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge7, TRUE);
			break;
		case 7:
			DrawGraph(TIME_POS_X / 3, TIME_POS_Y / 3, Pic.Gauge8, TRUE);
			break;
	
		}
		
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
		MainChar.move = MoveNo;

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
		Gau.NowGauge = 100;
		Gau.No = 0;
		Gau.GaugeNo = 7;
	}

	/*** Actシーン本処理 ***/
	int Out()
	{
		int ret = SCE::SCE_01_ACT;

		/*** 更新 ***/
		Update();
		Hp();
		HpFitting();
		/*** 判定 ***/
		Judge();

		/*** 移動計算 ***/
		Cal();
		
		/*** ステージ描画 ***/
		Sta.Out(&Sta_PosX);

		/*** メインキャラ描画 ***/
		Cha();

		/*** 敵描画 ***/
		Ene();
		
		/*** 表示系描画 ***/
		Disp();

		/*** ENDフラグ有効時、タイトルシーンに移行 ***/
		if (EndFlag == TRUE)
		{

			if (Goal == TRUE)
			{
				
				Sta.UpdateTime();
				ret = SCE::SCE_04_RES;
			}
			/*** タイトルシーンに移行 ***/
			else
			{
				Sta.UpdateTime();
				ret = SCE::SCE_04_RES;
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
		int PicDir = DIR_RI;
		int Touch = DIR_NONE;
		int Fall = FALSE;
		int move = 0;

	}MainChar;
	struct ITEM
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

	ITEM item;
	ENEMY Enem1;
	ENEMY Enem2;
private:
	int Goal = FALSE;
	int EndFlag = FALSE;

	// 2次関数ジャンプ用変数
	int Cou = 0;
	double T = 0.0;
	const double T_k = 20.0;

}Act;