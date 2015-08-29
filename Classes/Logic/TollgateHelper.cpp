#include "TollgateHelper.h"
#include "BagDataManager.h"
#include "PlayerInfoDataManager.h"
#include "AchievementHelper.h"
#include "GoodsHelper.h"
TollgateHelper* TollgateHelper::s_mTollgateHelper = nullptr;

TollgateHelper::TollgateHelper()
{

}

TollgateHelper* TollgateHelper::getHelper()
{
	if (! s_mTollgateHelper) s_mTollgateHelper = new TollgateHelper;
	return s_mTollgateHelper;
}

const vector<Season>* TollgateHelper::getAllTollgate()
{
	return TollgateDataManager::getManager()->getAllTollgate();
}

const Season* TollgateHelper::getOneTollgateSeason(unsigned int seasonId)//һ����ؿ�
{
	return TollgateDataManager::getManager()->getOneSeason(seasonId);
}
const Section* TollgateHelper::getOneTollgateSection(unsigned int seasonId, unsigned int sectionId)//����е�һ��С�ؿ�
{
	return TollgateDataManager::getManager()->getOneSection(seasonId,sectionId);
}

TollgateInfor::TollgatePassLevel TollgateHelper::getOneSectionPassLevel(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv)
{
	const TollgateInfor* info = TollgateDataManager::getManager()->getTollgateInfor(seasonId,sectionId);
	
	if (info && info->passLevel_gotRewards.size() > lv)
		return (TollgateInfor::TollgatePassLevel)info->passLevel_gotRewards[lv].first;
	else //û��������ݣ���ô����Ϊ����Ĺؿ�
		return TollgateInfor::eUnfinish;
}
void TollgateHelper::setGotAward(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv)
{
	if (!isPassed(seasonId,sectionId,lv)){
		return;
	}

	const Section* oneSection = this->getOneTollgateSection(seasonId,sectionId);
	const TollgateInfor *info = TollgateDataManager::getManager()->getTollgateInfor(seasonId, sectionId);
	if (info)
	{
		TollgateInfor temp = *info;
		if (temp.passLevel_gotRewards.size() > lv && oneSection->levels.size() > lv)
		{
			temp.passLevel_gotRewards[lv].second = 1;//got 
			TollgateDataManager::getManager()->setTollgateInfor(&temp);
			//���ڽ���������ģ�ֱ���� ������淢��
			//BagDataManager::getManager()->changeOneUnitCount(oneSection->levels[lv].awardUnitID,oneSection->levels[lv].awardUnitCount);
		}
		else
		{
			CCASSERT(false, "why no have this difficult infor");
			return;
		}
	}
	else
	{
		CCASSERT(false, "why no have this section infor");
		return;
	}
}
bool TollgateHelper::isGotAward(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv)
{
	const TollgateInfor *info = TollgateDataManager::getManager()->getTollgateInfor(seasonId, sectionId);
	if (info && info->passLevel_gotRewards.size() > lv)
	{
		return (info->passLevel_gotRewards[lv].second != 0 ? true : false);
	}
	return false;
}

void TollgateHelper::completeTollgateSection(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv, TollgateInfor::TollgatePassLevel star)
{
	if (!isPassed(seasonId,sectionId,lv))
	{
		const TollgateInfor *pInfo = TollgateDataManager::getManager()->getTollgateInfor(seasonId, sectionId);
		TollgateInfor temp;
		if (!pInfo){//û������ؿ�������
			temp.seasonId = seasonId;
			temp.sectionId = sectionId;
			temp.passLevel_gotRewards.push_back(make_pair(0,0));
		}else {
			temp = *pInfo;
			if(temp.passLevel_gotRewards.size() <= lv){ //û������Ѷȵ�����
				temp.passLevel_gotRewards.push_back(make_pair(0,0));
			}
		}

		if(temp.passLevel_gotRewards.size() <= lv){//��������
			//CCASSERT(false,"error infor");
			return;
		}
		temp.passLevel_gotRewards[lv].first = star;
		TollgateDataManager::getManager()->setTollgateInfor(&temp);
	}
}

bool TollgateHelper::isPassed(unsigned int seasonId, Section::Difficulty lv)
{
	const Season* oneSeason = getOneTollgateSeason(seasonId);
	if (!oneSeason){
		return false;
	}

	for (int i=0,count=oneSeason->sectionList.size(); i<count; ++i)
	{
		const TollgateInfor *info = TollgateDataManager::getManager()->getTollgateInfor(seasonId, i+1);
		if (!info){
			return false;
		}
		if (info->passLevel_gotRewards.size() <= lv){
			return false;
		}
		if (info->passLevel_gotRewards[lv].first == TollgateInfor::eUnfinish){
			return false;
		}
	}

	return true;
}
bool TollgateHelper::isPassed(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv)
{
	const TollgateInfor *info = TollgateDataManager::getManager()->getTollgateInfor(seasonId, sectionId);
	if (!info){
		return false;
	}
	if (info->passLevel_gotRewards.size() <= lv){
		return false;
	}
	if (info->passLevel_gotRewards[lv].first == TollgateInfor::eUnfinish){
		return false;
	}
	return true;
}
bool TollgateHelper::isCanStart(unsigned int seasonId, unsigned int sectionId, Section::Difficulty lv)
{
	//1. season �����  ---> ��ͨ����һ��season�Ƿ�ȫ��ͨ�أ��������ܺʹﵽunlockҪ�� ���ѣ���ͨ���Ƿ�ȫ��ͨ��
	//2. section �����   ---�� ��һ��section�Ƿ�ͨ��
	
	if (sectionId == 1) // --- ��ǰseason����������
	{
		if (lv == Section::eNormal)
		{
			if (seasonId == 1) return true;//��һ��seasonĬ�Ͽ���
			else if (isPassed(seasonId-1, Section::eNormal)) return true;
			else return false;
		}
		else if (lv == Section::eDifficult)
		{
			const Season* pSeason = this->getOneTollgateSeason(seasonId);
			int lastStarCount = 0;	
			for (int i=0; i<pSeason->sectionList.size(); ++i)
			{//0  1  2  3 
				lastStarCount += TollgateHelper::getHelper()->getOneSectionPassLevel(seasonId-1, pSeason->sectionList[i].sectionId, Section::eDifficult);
			}
			if (isPassed(seasonId, Section::eNormal) &&  pSeason->unlockCondition <= lastStarCount) return true;
			else return false;
		}
	}
	else if (sectionId > 1) // --- ��һ��section�������
	{
		const TollgateInfor *info = TollgateDataManager::getManager()->getTollgateInfor(seasonId, sectionId-1);
		if (info && info->passLevel_gotRewards.size() > lv && info->passLevel_gotRewards[lv].first > TollgateInfor::eUnfinish)
		{
			return true;
		}
	}

	return false;
}

vector<int> TollgateHelper::getProgress(Section::Difficulty lv)
{
	vector<int> ret(2,1);
	const vector<Season>* vec = this->getAllTollgate();
	for (int i=0,count=vec->size(); i<count; ++i)
	{
		if (vec->at(i).seasonId >= ret[0])
		{
			for (int isectionIdx=0; isectionIdx<vec->at(i).sectionList.size(); ++isectionIdx)
			{
				if (vec->at(i).sectionList.at(isectionIdx).sectionId > ret[1] 
					&& isCanStart(vec->at(i).seasonId, vec->at(i).sectionList.at(isectionIdx).sectionId, lv))
				{
					ret[0] = vec->at(i).seasonId;
					ret[1] = vec->at(i).sectionList.at(isectionIdx).sectionId;
				}
			}
		}
	}
	return ret;
}

int TollgateHelper::getSeasonProgress(int seasonId, Section::Difficulty lv)
{
	int ret = 0;
	const Season* pSeason = this->getOneTollgateSeason(seasonId);
	for (int i=0,count=pSeason->sectionList.size(); i<count; ++i)
	{
		if (pSeason->sectionList[i].sectionId > ret
			&& this->isPassed(seasonId, pSeason->sectionList[i].sectionId, lv))
		{
			ret = pSeason->sectionList[i].sectionId;
		}
	}
	return ret;
}