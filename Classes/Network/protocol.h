
#ifndef SIMPLEPROTOCOLCMD_H
#define SIMPLEPROTOCOLCMD_H

// #include <arpa/inet.h>
// #include "utils.h"
#include "cocos2d.h"
using namespace cocos2d;
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

#include <assert.h>

#define Current_ProtocolVersion 1


#define SimpleProtocol_Tag_Server 21335
#define SimpleProtocol_Tag_Client 21336

// ��ЧId
#define INVALID_ID 0
    
//�ͻ��˵�¼
#define ClientAccountMaxLen 32
#define ClientPswMaxLen     16


/* ���ذ���Ϣ������� */
enum MessageErrorCode {
    Success             	= 0,	//�ɹ�
    Error               	= 1,	//����
};


/* Э��ָ�� */
enum MessageCmd {
    /* �������� */
    ReqCmdStart             = 0,
    
    // ��½
    Req_Regist				= ReqCmdStart + 1,
    Req_Login,
    Req_AlterInfo,
    Req_UpdateInfo,

    //�ʼ�
    Req_QueryMail			= ReqCmdStart + 10,
    Req_ReadMail,
    
    //���а�
    Req_QueryRankBonus		= ReqCmdStart + 20,
    Req_QueryRankList,
    
    //ϵͳ����
    Req_QuerySystemBonus	= ReqCmdStart + 30,
    Req_GetSystemBonus,
    
    //���
    Req_QueryGiftBag	    = ReqCmdStart + 40,
    
    ReqCmdEnd,


    /* �������� */
    RspCmdStart             = 20000,
    
    //��½
    Rsp_Regist				= RspCmdStart + 1,
    Rsp_Login,
    Rsp_AlterInfo,
    Rsp_UpdateInfo,
    
    //�ʼ�
    Rsp_QueryMail			= RspCmdStart + 10,
    Rsp_ReadMail,
    
    //���а�
    Rsp_QueryRankBonus		= RspCmdStart + 20,
    Rsp_QueryRankList,
    
    //ϵͳ����
    Rsp_QuerySystemBonus	= RspCmdStart + 30,
    Rsp_GetSystemBonus,
    
    //���
    Rsp_QueryGiftBag	    = RspCmdStart + 40,
    
    RspCmdEnd,
        
        
    /* �������� */
    OtherCmdStart           = 60000,
    
    //ͳһ�����ַ
    Req_Unify	            = OtherCmdStart + 1,
    Rsp_Unify,
    
    //���¼�������ģ��
    Req_Reconfigure         = OtherCmdStart + 10,
    Rsp_Reconfigure,

    OtherCmdEnd,
};


#pragma pack(1)

/* ��ͷ */
struct SPHead
{
    unsigned short protocol_tag;
    unsigned short protocol_ver;
    unsigned short cmd;
    unsigned char not_use1;
    unsigned char not_use2;
    int data_len;
    //char protocol_buf_message[];
    //int check_sum;
};

inline void hton_SPHead(SPHead* head)
{
    head->protocol_tag = htons(head->protocol_tag);
    head->protocol_ver = htons(head->protocol_ver);
    head->cmd = htons(head->cmd);
    head->data_len = htonl(head->data_len);
}

inline void ntoh_SPHead(SPHead* head)
{
    head->protocol_tag = ntohs(head->protocol_tag);
    head->protocol_ver = ntohs(head->protocol_ver);
    head->cmd = ntohs(head->cmd);
    head->data_len = ntohl(head->data_len);
}

inline bool isValiedServerHead(SPHead* head)
{
	unsigned short tag = ntohs(head->protocol_tag);
	unsigned short ver = ntohs(head->protocol_ver);
	unsigned short cmd = ntohs(head->cmd);
	if (tag != SimpleProtocol_Tag_Server) return false;
	if (ver != Current_ProtocolVersion) return false;
	if ((cmd > RspCmdStart && cmd < RspCmdEnd) || (cmd > OtherCmdStart && cmd < OtherCmdEnd)) return true;
	return false;
}
inline bool isValiedClientHead(SPHead* head)
{
	unsigned short tag = ntohs(head->protocol_tag);
	unsigned short ver = ntohs(head->protocol_ver);
	unsigned short cmd = ntohs(head->cmd);
	if (tag != SimpleProtocol_Tag_Client) return false;
	if (ver != Current_ProtocolVersion) return false;
	if ((cmd > ReqCmdStart && cmd < ReqCmdEnd) || (cmd > OtherCmdStart && cmd < OtherCmdEnd)) return true;
	return false;
}

#pragma pack() //����


#endif //SIMPLEPROTOCOLCMD_H

