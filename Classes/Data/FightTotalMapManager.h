//============================================================
//* ս���������ù�����
//* ���ù������õ����г�����Ϣ�ɸ���������
//* ���� 1��Զ������ͼ�� 2���������������
//============================================================


#pragma once

#include "UnitDefine.h"
#include <vector>
#include <map>
#include <string>
#include "XReadJson.h"
#include "GameDirector.h"
using std::string;
using std::map;
using std::vector;

class FightTotalMapManager
{
private:
	static FightTotalMapManager* s_mFightTotalMapManager;
	FightTotalMapManager();
	~FightTotalMapManager();
	void initData();
public:
	static FightTotalMapManager* getManager();

	unsigned int getMaxMeter();

	vector<string> *getTotalFightSceneItems();

protected:

	unsigned int					m_nMaxMeter;

	vector<string>					m_lTotalSceneItemList;

};