#ifndef _MSGSTRUCTINFO_H_
#define _MSGSTRUCTINFO_H_
#include <string>
using namespace std;

#define DWORD unsigned long
#define BYTE unsigned char
#define WORD unsigned int


#define PROCESS_FRAME_DATA_LENGTH  1024 //���ݴ���֡����

#define FSF_LEGHTH 20  //���ͷ�ռλ����

#define JSF_LEGHTH 20 //���շ�ռλ����

#define SJCD_LEGHT 2 //���ݳ���ռλ����

#define TIME_CHECK_SELF 5 //�Լ�Ƶ��Ϊ5��

#define PARAME_LENGTH 50 //�ַ��������ĳ���

#define LIST_COUNT_WAIT_FOR_SEND  20  //�����д�ŵ�����

enum{
	TX_NULL = 0,
	TX_FWJQ,		//�����Ȩ 01
	TX_KFQQ,		//�۷����� 02
	TX_JQJG,		//��Ȩ��Ϣ 03
};

typedef struct tagBstxMsg
{
	//��������
	WORD nType;

	//��Ȩ����
	DWORD nAuthenticationId;
	//��ҵ���
	string sQtsentid;
	//��������
	WORD	 nCategory;
	//���շ�
	DWORD nRecvId;

//	DWORD dwSerialID;			//�������
//	WORD nQtscardnumber;	//IC����
//	WORD		 nCategory;		//��Ʒ����

}BstxMsg;

enum ResEnum{ PERMISSION, NOCATEGORY, NOMONEY, STATEERROR, TEACHDATE, NOREGISTER };
typedef struct tagBsResMsg
{
	
	DWORD nAuthenticationId;   //��Ȩ����
	ResEnum nRes;				//��֤���		0:ok,1:state error,2:no money,3:teach date,4:no register,5 no category
	string sQtsentid;
	//WORD nQtscardnumber;		//IC����
	//char cQtsproductid[20]; //��Ʒ��ʶ
	//float fQtdamount;			//���
	//char cTimestamp[20];	//�۷�ʱ��
}BsresMsg;

 
#endif
