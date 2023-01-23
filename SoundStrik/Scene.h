#pragma once

/*** Sceneクラス ***/
class
{
public:
	/* シーン出力 */
	void Out()
	{
		switch (now)
		{
		case SCE::SCE_00_TIT:
			/* タイトルシーン出力 */
			Res.EndInit();
			Act.EndInit();
			now = Tit.Out();
			break;
		case SCE::SCE_01_ACT:
			/* アクションシーン出力 */
			now = Act.Out();
			break;
		case SCE::SCE_03_CLE:
			/* クリアシーン出力 */
			now = Cle.Out();
			break;
		case SCE::SCE_04_RES:
			/* クリアシーン出力 */
			now = Res.Out();
			break;
		default:
			break;
		}
	}

	// 現在のシーン
	int now = SCE::SCE_00_TIT;

}Sce;