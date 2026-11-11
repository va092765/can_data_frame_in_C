#include<stdio.h>
#include<string.h>
#include<stdint.h>
#define CAN_MAX_DLC 8
typedef enum
{
	CAN_ID_STANDARD=0,
	CAN_ID_EXTENDED=1
}CAN_IdType;
typedef enum
{
	CAN_FRAME_DATA=0,
	CAN_FRAME_REMOTE=1

}CAN_FrameType;
typedef struct
{
	uint32_t id;
	CAN_IdType id_type;
	CAN_FrameType frame_type;
	uint8_t dlc;
	uint8_t data[CAN_MAX_DLC];

}CAN_Frame;
int CAN_FrameInit(CAN_Frame *f, uint32_t id, CAN_IdType type, const uint8_t *data, uint8_t dlc)
{
	if(f==NULL || dlc > CAN_MAX_DLC)
	{
		return -1;
	}
	if(type==CAN_ID_STANDARD && id > 0x7FF)
	{
		return -1;
	}
	if(type==CAN_ID_EXTENDED && id > 0x1FFFFFFF)
	{
		return -1;
	}
	memset(f,0,sizeof(*f));
	f->id=id;
	f->id_type=type;
	f->frame_type=CAN_FRAME_DATA;
	f->dlc=dlc;
	if(data!=NULL && dlc>0)
	{
		memcpy(f->data,data,dlc);
	}
}
int main()
{
	CAN_Frame tx;
	uint8_t payload[4]={0x11,0x22,0x33,0x44};
	if(CAN_FrameInit(&tx,0x123,CAN_ID_STANDARD, payload,4)==0)
	{
		printf("ID:0x%03x DLC:%u DATA:",(unsigned)tx.id,tx.dlc);

	}
	for(uint8_t i=0;i<tx.dlc;i++)
	{
		printf(" %02X",tx.data[i]);
		printf("\n");
	}
}
