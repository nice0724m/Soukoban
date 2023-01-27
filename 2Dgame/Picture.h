#pragma once

/*** PictureƒNƒ‰ƒX ***/
class
{
public:
	int Back;
	int Block1;
	int Block2;
	int Block3;
	int Block4;
	int Block5;
	int Block6;
	int Gauge;
	int Gauge2;
	int Gauge3;
	int Gauge4;
	int Gauge5;
	int Gauge6;
	int Gauge7;
	int Gauge8;
	int MChara;
	int Enemy1;
	int Title;
	int Clear;
	int RECOVERY;

	void Read()
	{
		Back = LoadGraph("./picture/Back.png");
		Block1 = LoadGraph("./picture/Block_1.png");
		Block2 = LoadGraph("./picture/Block_2.png");
		Block3 = LoadGraph("./picture/Block_3.png");		
		Block5 = LoadGraph("./picture/Block_5.png");
		Block6 = LoadGraph("./picture/Block_6.png");
		MChara = LoadGraph("./picture/MainChara.png");
		Enemy1 = LoadGraph("./picture/Enemy_1.png");
		Title = LoadGraph("./picture/Title.png");
		Gauge =  LoadGraph("./picture/Gauge.png");
		Gauge2 = LoadGraph("./picture/Gauge2.png");
		Gauge3 = LoadGraph("./picture/Gauge3.png");
		Gauge4 = LoadGraph("./picture/Gauge4.png");
		Gauge5 = LoadGraph("./picture/Gauge5.png");
		Gauge6 = LoadGraph("./picture/Gauge6.png");
		Gauge7 = LoadGraph("./picture/Gauge7.png");
		Gauge8 = LoadGraph("./picture/Gauge8.png");
		Clear = LoadGraph("./picture/Clear.png");
		RECOVERY = LoadGraph("./picture/Block_4.png");
	}

private:

}Pic;