
/*****************************************************************************


    �ͻ���,����˹��õĽṹ�ͷ���


*****************************************************************************/



#pragma once
#include <string>
#include <vector>
#include <string.h>



//�������� PS: �ʼ������������Ҳʹ���������
enum AttachType {
	AttachType_Invalid 		= 0,	//��Ч����
	AttachType_Gold 		= 1,	//���
	AttachType_Diamond 		= 2,	//��ʯ
	AttachType_Props 		= 3,	//���� 
	AttachType_Debris 	    = 4,	//��Ƭ
	AttachType_GiftBag		= 5,	//���
	AttachType_Vitality		= 6,	//����
};


//���а���ID����
enum RankBonusID {		
	RankBonusID_Invalid     = 0,    //��Чid
	RankBonusID_1           = 1,    //��1��
	RankBonusID_2           = 2,    //��2��
	RankBonusID_3           = 3,    //��3��
	RankBonusID_4_5         = 4,    //4-5��
	RankBonusID_6_10        = 5,    //6-10��
	RankBonusID_11_20       = 6,    //11-20��
	RankBonusID_21_30       = 7,    //21-30��
};


//���а����ID����
enum RankGroupID {		
	RankGroupID_0           = 0,    //default ����
	RankGroupID_1           = 1,    //��2��
	RankGroupID_2           = 2,    //
	RankGroupID_3           = 3,    //
	RankGroupID_4           = 4,    //
	RankGroupID_5           = 5,    //
	RankGroupID_6           = 6,    //
	RankGroupID_7           = 7,    //
	RankGroupID_8           = 8,    //
	//RankGroupID_9           = 9,    //
    RankGroup_Max,                  //������
};


namespace CS
{
	/* ���а� */
	//������ȡ����id
    RankBonusID get_rank_bonus_id(int order);
}

