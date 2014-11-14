#ifndef _MSGSTRUCTINFO_H_
#define _MSGSTRUCTINFO_H_

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
	CUNPACK_NULL = 0,
	CUNPACK_FWJQ,		//�����Ȩ 01
	CUNPACK_KFQQ,		//�۷����� 02
	CUNPACK_JQJG,		//��Ȩ��Ϣ 03
};

typedef struct tagBstxMsg
{
	DWORD dwSerialID;			//�������
	WORD nQtscardnumber;	//IC����
	WORD		 nCategory;		//��Ʒ����

}BstxMsg;

enum ResEnum{ PERMISSION, STATEERROR, NOMONEY, TEACHDATE, NOREGISTER, NOCATEGORY };
typedef struct tagBsResMsg
{
	DWORD dwSerialID;		//�������
	ResEnum nRes;				//��֤���		0:ok,1:state error,2:no money,3:teach date,4:no register,5 no category
	bool bIsRecord;				//�Ƿ��¼
	char cQtsentid[20];		//��ҵID
	WORD nQtscardnumber;		//IC����
	char cQtsproductid[20]; //��Ʒ��ʶ
	float fQtdamount;			//���
	//char cTimestamp[20];	//�۷�ʱ��
}BsresMsg;

 
#endif
