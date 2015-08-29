//============================================================
//* ����ؿ���
//============================================================

#pragma once

#include "UnitDefine.h"
#include <vector>
#include "TollgateDataManager.h"
class TollgateHelper
{
private:
	static TollgateHelper* s_mTollgateHelper;
	TollgateHelper();
public:
	static TollgateHelper* getHelper();

	//*********************************************
	//��ȡ��ص�������Ϣ
	//*********************************************
	const vector<Season>* getAllTollgate();
	const Season* getOneTollgateSeason(unsigned int seasonId);//һ����ؿ�
	const Section* getOneTollgateSection(unsigned int seasonId, unsigned int sectionId);//����е�һ��С�ؿ�


	//*********************************************
	//��ȡ��ص��û���Ϣ
	//��ȡͨ���Ǽ�
	//*********************************************
	TollgateInfor::TollgatePassLevel getOneSectionPassLevel(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv);
	//��������ȡͨ�ؽ�������ǰ�汾��ֱ���ڽ������䷢���������Թؿ���������ʹ�õ��ýӿڣ�
	//�ýӿ�����ÿ�µ�ʮ��ͨ�غ� �����Ĳ廭��Ϣ��
	void setGotAward(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv);
	bool isGotAward(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv);//��ȡ�Ƿ��Ѿ���ȡ����	
	//pref : ���һ���ؿ�����������
	//seasonId��ؿ�id
	//sectionIdС�ؿ�id
	//lv �Ѷ�
	//star �������
	void completeTollgateSection(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv, TollgateInfor::TollgatePassLevel star=TollgateInfor::eGood);
	bool isPassed(unsigned int seasonId, Section::Difficulty lv); //������ؿ�ĳ�Ѷ��Ƿ�ͨ��
	bool isPassed(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv);//ĳ�Ѷ��Ƿ��Ѿ�ͨ��
	bool isCanStart(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv);//ĳ�Ѷ��Ƿ���Կ���
	//��ȡ��ǰ����  season section
	//���ص�ǰ�Ѷȿɴ�����һ�أ��磺�մ��1-1 ��ô����1-2��
	vector<int> getProgress(Section::Difficulty lv);
	//��ȡ��ǰ�½ڿɴ�������һ��
	int getSeasonProgress(int seasonId, Section::Difficulty lv);
};