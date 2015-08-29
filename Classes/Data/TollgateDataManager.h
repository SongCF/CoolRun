//============================================================
//�ؿ�����
//============================================================

#pragma once

#include "UnitDefine.h"
#include "XReadJson.h"


//1.������Ϣ
//��ؿ��е�һϵ��С��
struct Section
{
	//ͨ��������1���������㣬2�÷֣�3·��",
	enum PassConditionType
	{
		PassType_End = 1,
		PassType_Score,
		PassType_Meter,
	};
	//�Ѷ�����
	enum Difficulty
	{
		eNormal = 0, //����vector���±�,���Բ�Ҫ�������ֵ
		eDifficult,
	};
	//����
	typedef struct{
		unsigned int awardUnitID;
		unsigned int awardUnitCount;
		vector<float> probability; //ÿһ�ػ��ж��������û�ֽ��������Լ��ĳ��ָ��ʣ�ͨ������Խ�߸���Խ�ߣ�
	}award;
	//��ͬ�Ѷ�
	typedef struct{
		string lvDescribe;// �� �� ����
		float speed;  //��ͼ�����ٶ�
		vector<award> awardList;
	}levelInfor;


	unsigned int sectionId;
	string name;
	string mapName;
	PassConditionType passType;
	vector<levelInfor> levels;  //��ͬ�ѶȵĽ�����   ��ͨ������


	Section(){
		this->sectionId = 0; 
		this->passType = PassType_End;
	}
	Section(const Section& _in){
		this->sectionId = _in.sectionId;
		this->name = _in.name; 
		this->mapName = _in.mapName; 
		this->passType = _in.passType;
		this->levels = _in.levels;
	}
	const Section& operator=(const Section& _in){
		this->sectionId = _in.sectionId;
		this->name = _in.name; 
		this->mapName = _in.mapName; 
		this->passType = _in.passType;
		this->levels = _in.levels;
		return *this;
	}
};
//��ؿ�
struct Season
{
	unsigned int seasonId;
	int unlockCondition;   //������Ҫ��ǰ�������ܺʹﵽ����
	vector<Section> sectionList;

	Season(){
		seasonId = 0;
		unlockCondition = 0xffffff;
	}
	Season(const Season& _in){
		this->seasonId = _in.seasonId;
		this->unlockCondition = _in.unlockCondition;
		this->sectionList = _in.sectionList;
	}
	const Season& operator=(const Season& _in){
		this->seasonId = _in.seasonId;
		this->unlockCondition = _in.unlockCondition;
		this->sectionList = _in.sectionList;
		return *this;
	}
};

//2. �û���Ϣ
struct TollgateInfor
{
	enum TollgatePassLevel
	{
		eUnfinish = 0, //δ���
		eGood = 1,
		eNice,
		ePerfect,
	};
	unsigned int seasonId;
	unsigned int sectionId;
	vector<std::pair<int,int>> passLevel_gotRewards;  //��ͬ�Ѷ�ͨ������ //�Ƿ���ȡ�˽���
	TollgateInfor(){
		seasonId = 0;
		sectionId = 0;
	}
	TollgateInfor(const TollgateInfor& _in){
		this->seasonId = _in.seasonId;
		this->sectionId = _in.sectionId;
		this->passLevel_gotRewards = _in.passLevel_gotRewards;
	}
	const TollgateInfor& operator=(const TollgateInfor& _in){
		this->seasonId = _in.seasonId;
		this->sectionId = _in.sectionId;
		this->passLevel_gotRewards = _in.passLevel_gotRewards;
		return *this;
	}
};

//3.
class TollgateDataManager
{
private:
	static TollgateDataManager* s_mTollgateManager;
	TollgateDataManager();
	void initData();
	void initMapConfigFile();
	void initUserDataInfor();

	void saveData();
public:
	static TollgateDataManager* getManager();

	//config map
	const vector<Season>* getAllTollgate();
	const Season* getOneSeason(unsigned int seasonId);
	const Section* getOneSection(unsigned int seasonId, unsigned int sectionId);

	//infor
	const vector<TollgateInfor>* getTollgateInforList();
	//��Ϊû��Ĺؿ���һ��season���û���Ϣ�ǲ�ȫ�ģ����Բ��ṩ��ȡ����season��info
	//vector<TollgateInfor> getTollgateInfor(unsigned int seasonId);
	const TollgateInfor* getTollgateInfor(unsigned int seasonId, unsigned int sectionId);
	void setTollgateInfor(const TollgateInfor* newInfor);

private:
	/*
	//pref: 
	// ���е�get��Ϊ˳��������ң�����ʹ���±�ֱ�ӷ��ʡ����еĹؿ�����û����Ӧ��������Ϣ��ֱ�ӷ��ʿ��ܻ��ճ�����Խ�磩
	*/
	vector<Season>				mTollgateMapList;
	vector<TollgateInfor>		mTollgateInforList;
};