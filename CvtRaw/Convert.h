#pragma once

#include <Windows.h>
#include <conio.h>
#include <stdio.h>


//C32��Ч�����ϵͳ����
#define HKA_MIN_S32     (-2147483647 - 1 )              // ��С32λ�з�������ֵ
#define SCALE          (0.0000152587890625f)			// (1/65536)

//ABC32F_Planerת������
#define BIG2SMALL(val) ( ((val & 0xff)<<24) + (((val>>8) & 0xff)<<16) + (((val>>16) & 0xff)<<8) + (val>>24) )
#define RAW2REAL(val)  ( ((short *)(&val))[1] + ((unsigned short *)(&val))[0] * SCALE )

typedef enum MvGvspPixelType
{
	PixelType_Gvsp_Coord3D_ABC32f = 0x026000C0,
	PixelType_Gvsp_Coord3D_ABC32f_Planar = 0x026000C1,

	PixelType_Gvsp_Coord3D_ABC32 = 0x82603001,
	PixelType_Gvsp_Coord3D_AB32f = 0x82403002,
	PixelType_Gvsp_Coord3D_AB32 = 0x82403003,
	PixelType_Gvsp_Coord3D_AC32f_64 = 0x024000C2,
	PixelType_Gvsp_Coord3D_AC32f_Planar = 0x024000C3,
	PixelType_Gvsp_Coord3D_AC32 = 0x82403004,
	PixelType_Gvsp_Coord3D_A32f = 0x012000BD,
	PixelType_Gvsp_Coord3D_A32 = 0x81203005,
	PixelType_Gvsp_Coord3D_C32f = 0x012000BF,
	PixelType_Gvsp_Coord3D_C32 = 0x81203006,
	PixelType_Gvsp_Coord3D_ABC16 = 0x023000B9,

}MvGvspPixelType;


typedef struct _MV_POINT_CLOUD_DATA_
{
	unsigned int        nLinePntNum;        // [IN]     ÿһ�е������
	unsigned int        nLineNum;           // [IN]     ����

	MvGvspPixelType     enSrcPixelType;     // [IN]     �������ݵ����ظ�ʽ
	unsigned char*      pSrcData;           // [IN]     �������ݻ���
	unsigned int        nSrcDataLen;        // [IN]     �������ݴ�С


	//����C32������
	float				x_scale;			// [IN]     ����X����������
	float				y_scale;			// [IN]     ����Y����������
	float               z_scale;			// [IN]     ����z����������


	FILE*               pFileOut;

	unsigned int        nReserved[8];       //          �����ֶ�

}MV_POINT_CLOUD_DATA;

typedef struct _BMP_DATA_
{
	unsigned int        nWidth;				// [IN]     ͼ����
	unsigned int        nHeight;			// [IN]     ͼ��߶�

	unsigned char*      pSrcData;           // [IN]     �������ݻ���
	unsigned int		nBitCount;			// [IN]     ��������λ��
	unsigned int        nSrcDataLen;        // [IN]     �������ݴ�С

	FILE*               pFileOut;

}BMP_DATA;


class CvtCalss
{
public:
	CvtCalss();
	~CvtCalss();


public:
	unsigned int		Height;
	unsigned int		Width;

	unsigned int			m_nC32BMPDataBufferSize;
	unsigned char*			m_pC32BMPDataBuffer;

	int		ChangeC32ToMono8(unsigned char* pData, unsigned int nWidth, unsigned int nHeight, unsigned int nDataSize);
	int		SavePointCloudData(MV_POINT_CLOUD_DATA* pstParam);
	int		SaveBmp(BMP_DATA* pstParam);

};