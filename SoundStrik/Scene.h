#pragma once

/*** Scene�N���X ***/
class
{
public:
	/* �V�[���o�� */
	void Out()
	{
		switch (now)
		{
		case SCE::SCE_00_TIT:
			/* �^�C�g���V�[���o�� */
			Res.EndInit();
			Act.EndInit();
			now = Tit.Out();
			break;
		case SCE::SCE_01_ACT:
			/* �A�N�V�����V�[���o�� */
			now = Act.Out();
			break;
		case SCE::SCE_03_CLE:
			/* �N���A�V�[���o�� */
			now = Cle.Out();
			break;
		case SCE::SCE_04_RES:
			/* �N���A�V�[���o�� */
			now = Res.Out();
			break;
		default:
			break;
		}
	}

	// ���݂̃V�[��
	int now = SCE::SCE_00_TIT;

}Sce;