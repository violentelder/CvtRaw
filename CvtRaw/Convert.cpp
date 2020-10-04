#include "Convert.h"

CvtCalss::CvtCalss()
	: Height(0)
	, Width(0)
	, m_nC32BMPDataBufferSize(0)
	, m_pC32BMPDataBuffer(NULL)

{

}

int CvtCalss::ChangeC32ToMono8(unsigned char* pData, unsigned int nWidth, unsigned int nHeight, unsigned int nDataSize)
{
	if (NULL == pData || 0 == nWidth || 0 == nHeight || nDataSize < nWidth * nHeight * 4)
	{
		return -1;
	}
	int nDepth = 0;
	int nMax = INT_MIN;
	int nMin = INT_MAX;
	int* pValue = (int*)pData;
	for (int i = 0; i < nHeight * nWidth; i++)
	{
		nDepth = pValue[i];
		if (HKA_MIN_S32 == nDepth)
		{
			nDepth = 0;
		}
		if (nDepth > nMax)
		{
			nMax = nDepth;
		}
		if (nDepth < nMin)
		{
			nMin = nDepth;
		}
	}

	int nCurRange = nMax - nMin;
	unsigned char nTmpValue = 0;
	for (int i = 0; i < nHeight * nWidth; i++)
	{
		nDepth = pValue[i];
		if (HKA_MIN_S32 == nDepth)
		{
			nDepth = 0;
		}
		if (nCurRange != 0)
		{
			nTmpValue = (nDepth - nMin) / (nCurRange * 1.0) * 255;
		}
		pData[i] = nTmpValue;
	}
}



//int CvtCalss::SaveC32To16BMP(char *bmpName, unsigned char* pData, unsigned int nWidth, unsigned int nHeight)
//{
//	if (NULL == pData || 0 == nWidth || 0 == nHeight)
//	{
//		return MV_E_PARAMETER;
//	}
//
//	BITMAPFILEHEADER stFileHeader = { 0 };
//	BITMAPINFOHEADER stInfoHeader = { 0 };
//	stFileHeader.bfType = 19778;
//	stFileHeader.bfOffBits = (sizeof(stFileHeader) + sizeof(stInfoHeader));
//	stFileHeader.bfSize = (stFileHeader.bfOffBits + nWidth * nHeight * sizeof(short));
//	stInfoHeader.biSize = sizeof(stInfoHeader);
//	stInfoHeader.biWidth = nWidth;
//	stInfoHeader.biHeight = nHeight;
//	stInfoHeader.biPlanes = 1;
//	stInfoHeader.biBitCount = 8 * sizeof(short);
//	stInfoHeader.biSizeImage = nWidth * nHeight * sizeof(short);
//
//	bool bShouldAppend = (nWidth % 2 != 0);// 是否需要补齐四字节
//	if (bShouldAppend)
//	{
//		stInfoHeader.biSizeImage += (nHeight * sizeof(short));
//	}
//
//	if (m_nC32BMPDataBufferSize < stInfoHeader.biSizeImage)
//	{
//		if (m_pC32BMPDataBuffer)
//		{
//			free(m_pC32BMPDataBuffer);
//			m_pC32BMPDataBuffer = NULL;
//			m_nC32BMPDataBufferSize = 0;
//		}
//		m_pC32BMPDataBuffer = (unsigned char*)malloc(stInfoHeader.biSizeImage + 1024);
//		if (NULL == m_pC32BMPDataBuffer)
//		{
//			return MV_E_RESOURCE;
//		}
//		m_nC32BMPDataBufferSize = stInfoHeader.biSizeImage + 1024;
//	}
//	memset(m_pC32BMPDataBuffer, 0, m_nC32BMPDataBufferSize);
//
//	// 转换数据
//	int*   pInt = (int*)pData;
//	short* pShort = (short*)pData;
//	int nAppendSize = (bShouldAppend ? 1 : 0);
//	for (int i = 0; i < nWidth * nHeight; ++i)
//	{
//		pShort[i + (i / nWidth * nAppendSize)] = pInt[i];
//	}
//
//	// 倒转数据
//	unsigned int nCurrentDataWidth = (nWidth + nAppendSize);
//	for (int i = 0; i < nHeight; ++i)
//	{
//		memcpy(m_pC32BMPDataBuffer + (nHeight - 1 - i) * nCurrentDataWidth * sizeof(short), pData + i * nCurrentDataWidth * sizeof(short), nCurrentDataWidth * sizeof(short));
//	}
//
//	//保存转换后的图片
//
//
//	FILE* pFileOut = fopen(bmpName, "wb");;
//	fwrite(&stFileHeader, 1, sizeof(stFileHeader), pFileOut);
//	fwrite(&stInfoHeader, 1, sizeof(stInfoHeader), pFileOut);
//	fwrite(m_pC32BMPDataBuffer, 1, stInfoHeader.biSizeImage, pFileOut);
//	fflush(pFileOut);
//	fclose(pFileOut);
//	pFileOut = NULL;
//
//
//
//	return MV_OK;
//}

int CvtCalss::SavePointCloudData(MV_POINT_CLOUD_DATA* pstParam)
{
	if (NULL == pstParam || NULL == pstParam->pSrcData)
	{
		return -1;
	}
	unsigned int nPntNum = pstParam->nLinePntNum * pstParam->nLineNum;//所有点的数量
	char DstBuf[1024] = { 0 };

	sprintf_s(DstBuf, 1024, "ply\n");
	sprintf_s(DstBuf + strlen(DstBuf), 64, "format ascii 1.0\n");
	sprintf_s(DstBuf + strlen(DstBuf), 64, "comment author:hik-robot\n");
	sprintf_s(DstBuf + strlen(DstBuf), 64, "element vertex %d\n", nPntNum);
	sprintf_s(DstBuf + strlen(DstBuf), 64, "property float x\n");
	sprintf_s(DstBuf + strlen(DstBuf), 64, "property float y\n");
	sprintf_s(DstBuf + strlen(DstBuf), 64, "property float z\n");
	sprintf_s(DstBuf + strlen(DstBuf), 64, "end_header\n");

	unsigned int nDstBufLen = strlen(DstBuf);//初始化为PLY头长度
	fwrite(DstBuf, nDstBufLen, 1, pstParam->pFileOut);

	switch (pstParam->enSrcPixelType)
	{
	case PixelType_Gvsp_Coord3D_ABC32:                              // 3D激光轮廓传感器数据格式
	{
		int * pSrcData = (int *)pstParam->pSrcData;
		unsigned int m = 0;
		for (int i = 0; i < nPntNum; i++)
		{
			if (i >= m * (pstParam->nLinePntNum) && i < (m + 1) * (pstParam->nLinePntNum))                                            //每nLinePntNum 改一次Y OffsetY 值
			{
				sprintf(DstBuf, "%d %d %d\n\0", *pSrcData, *(pSrcData + 1), *(pSrcData + 2));            // OffsetY = m * STEP_DISTANCE， y = y + offset
				nDstBufLen = strlen(DstBuf);
				fwrite(DstBuf, nDstBufLen, 1, pstParam->pFileOut);
				pSrcData = pSrcData + 3;
				if (i == (pstParam->nLinePntNum) * (m + 1) - 1)
				{
					m = m + 1;
				}
			}
		}
	}
	break;

	case PixelType_Gvsp_Coord3D_ABC32f:                              // 3D激光轮廓传感器数据格式
	{
		float * pSrcData = (float *)pstParam->pSrcData;
		unsigned int m = 0;
		for (int i = 0; i < nPntNum; i++)
		{
			if (i >= m * (pstParam->nLinePntNum) && i < (m + 1) * (pstParam->nLinePntNum))                                            //每nLinePntNum 改一次Y OffsetY 值
			{
				sprintf(DstBuf, "%f %f %f\n\0", *pSrcData, *(pSrcData + 1), *(pSrcData + 2));            // OffsetY = m * STEP_DISTANCE， y = y + offset
				nDstBufLen = strlen(DstBuf);
				fwrite(DstBuf, nDstBufLen, 1, pstParam->pFileOut);
				pSrcData = pSrcData + 3;
				if (i == (pstParam->nLinePntNum) * (m + 1) - 1)
				{
					m = m + 1;
				}
			}
		}
	}
	break;

	case PixelType_Gvsp_Coord3D_C32:                              // 3D激光轮廓传感器深度图数据格式
	{
		int * pSrcData = (int *)pstParam->pSrcData;
		unsigned int x = 0;
		unsigned int y = 0;
		for (int j = 0; j < pstParam->nLineNum; j++)
		{
			for (int i = 0; i < pstParam->nLinePntNum; i++)
			{

				if ((*pSrcData) == 0x80000000)					//去除无效点
				{
					x = y = 0;
					*pSrcData = 0;
				}
				else
				{
					x = (i *(pstParam->x_scale));
					y = (j *(pstParam->y_scale));

				}

				sprintf(DstBuf, "%d %d %d\n\0", x, y, (*pSrcData));
				nDstBufLen = strlen(DstBuf);
				fwrite(DstBuf, nDstBufLen, 1, pstParam->pFileOut);
				pSrcData = pSrcData + 1;

			}
		}
	}



	case PixelType_Gvsp_Coord3D_ABC32f_Planar:                          // 线激光立体相机数据格式
	{
		int * pSrcData = (int *)pstParam->pSrcData;
		unsigned int m = 0;
		for (unsigned int i = 0; i < nPntNum; i++)
		{
			if (i >= m * (pstParam->nLinePntNum) && i < (m + 1) * (pstParam->nLinePntNum))                                            //每nLinePntNum 改一次Y OffsetY 值
			{
				if (((*pSrcData) == 0xffffffff) || ((*(pSrcData + 2)) == 0xffffffff))
				{
					*pSrcData = 0;
					*(pSrcData + 1) = 0;
					*(pSrcData + 2) = 0;
				}
				unsigned int x_u32 = *pSrcData;
				unsigned int y_u32 = *(pSrcData + 1);
				unsigned int z_u32 = *(pSrcData + 2);
				x_u32 = BIG2SMALL(x_u32);
				y_u32 = BIG2SMALL(y_u32);
				z_u32 = BIG2SMALL(z_u32);
				sprintf(DstBuf, "%f %f %f\n\0", RAW2REAL(x_u32), RAW2REAL(y_u32), RAW2REAL(z_u32));            // OffsetY = m * 100
				nDstBufLen = strlen(DstBuf);
				fwrite(DstBuf, nDstBufLen, 1, pstParam->pFileOut);
				pSrcData = pSrcData + 3;
				if (i == (pstParam->nLinePntNum) * (m + 1) - 1)
				{
					m = m + 1;
				}
			}

		}
	}
	break;

	default:
		return -1;
	}

	return 0;
}
int CvtCalss::SaveBmp(BMP_DATA* pstParam/*char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount*/)
{
	//如果位图数据指针为 0，则没有数据传入，函数返回
	if (!pstParam->pSrcData)
	{
		return 0;
	}

	//颜色表大小，以字节为单位，灰度图像颜色表为 1024 字节，彩色图像颜色表大小为 0
	int colorTablesize = 0;


	BITMAPFILEHEADER stFileHeader = { 0 };											//申请位图文件头结构变量，填写文件头信息
	BITMAPINFOHEADER stInfoHeader = { 0 };											//申请位图信息头结构变量，填写信息头信息
	stFileHeader.bfType = 0x4D42;													//bmp 类型
	stFileHeader.bfOffBits = (sizeof(stFileHeader) + sizeof(stInfoHeader));			//bmp 加头后位置偏移:是图像文件前 3 个部分所需空间之和
	stFileHeader.bfReserved1 = 0;													//保留字段
	stFileHeader.bfReserved2 = 0;

	stInfoHeader.biWidth = pstParam->nWidth;
	stInfoHeader.biHeight = pstParam->nHeight;
	stInfoHeader.biPlanes = 1;
	stInfoHeader.biSize = sizeof(stInfoHeader);
	stInfoHeader.biBitCount = pstParam->nBitCount;
	stInfoHeader.biClrImportant = 0;
	stInfoHeader.biClrUsed = 0;
	stInfoHeader.biCompression = 0;


	switch (pstParam->nBitCount)
	{
	case 8:
	{
		colorTablesize = 1024;
		//待存储图像数据每行字节数为 4 的倍数
		int lineByte = (pstParam->nWidth * pstParam->nBitCount / 8 + 3) / 4 * 4;

		//bfSize 是图像文件 4 个组成部分之和
		stFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
			+ colorTablesize + lineByte * pstParam->nHeight;
		fwrite(&stFileHeader, sizeof(BITMAPFILEHEADER), 1, pstParam->pFileOut);

		//写位图信息头进内存
		stInfoHeader.biSizeImage = lineByte*pstParam->nHeight;
		stInfoHeader.biXPelsPerMeter = 0;
		stInfoHeader.biYPelsPerMeter = 0;
		fwrite(&stInfoHeader, sizeof(BITMAPINFOHEADER), 1, pstParam->pFileOut);


		//灰度图像，有颜色表，写入文件
		RGBQUAD rgbquad[256];
		int i;
		for (i = 0; i < 256; i++)
		{
			rgbquad[i].rgbBlue = i;
			rgbquad[i].rgbGreen = i;
			rgbquad[i].rgbRed = i;
			rgbquad[i].rgbReserved = 0;
		}
		fwrite(&rgbquad, sizeof(RGBQUAD), 256, pstParam->pFileOut);


		//写位图数据进文件,倒转数据
		int j;
		for (j = 0; j < pstParam->nHeight; j++)
		{
			fwrite(pstParam->pSrcData + (pstParam->nHeight - 1 - j) * pstParam->nWidth, lineByte, 1, pstParam->pFileOut);
		}

		//关闭文件
		fclose(pstParam->pFileOut);
		return 1;
	}

	case 16:
	{
		stFileHeader.bfSize = (stFileHeader.bfOffBits + pstParam->nSrcDataLen * sizeof(short));
		stInfoHeader.biXPelsPerMeter = 0;
		stInfoHeader.biYPelsPerMeter = 0;
		stInfoHeader.biSizeImage = pstParam->nSrcDataLen * sizeof(short);

		bool bShouldAppend = (pstParam->nWidth % 2 != 0);// 是否需要补齐四字节
		if (bShouldAppend)
		{
			stInfoHeader.biSizeImage += (pstParam->nHeight * sizeof(short));
		}

		if (m_nC32BMPDataBufferSize < stInfoHeader.biSizeImage)
		{
			if (m_pC32BMPDataBuffer)
			{
				free(m_pC32BMPDataBuffer);
				m_pC32BMPDataBuffer = NULL;
				m_nC32BMPDataBufferSize = 0;
			}
			m_pC32BMPDataBuffer = (unsigned char*)malloc(stInfoHeader.biSizeImage + 1024);
			if (NULL == m_pC32BMPDataBuffer)
			{
				return 0;
			}
			m_nC32BMPDataBufferSize = stInfoHeader.biSizeImage + 1024;
		}
		memset(m_pC32BMPDataBuffer, 0, m_nC32BMPDataBufferSize);

		// 转换数据
		int*   pInt = (int*)pstParam->pSrcData;
		short* pShort = (short*)pstParam->pSrcData;
		int nAppendSize = (bShouldAppend ? 1 : 0);
		for (int i = 0; i < pstParam->nSrcDataLen; ++i)
		{
			pShort[i + (i / pstParam->nWidth * nAppendSize)] = pInt[i];
		}

		// 倒转数据
		unsigned int nCurrentDataWidth = (pstParam->nWidth + nAppendSize);
		for (int i = 0; i < pstParam->nHeight; ++i)
		{
			memcpy(m_pC32BMPDataBuffer + (pstParam->nHeight - 1 - i) * nCurrentDataWidth * sizeof(short), pstParam->pSrcData + i * nCurrentDataWidth * sizeof(short), nCurrentDataWidth * sizeof(short));
		}

		//保存转换后的图片
		fwrite(&stFileHeader, 1, sizeof(stFileHeader), pstParam->pFileOut);
		fwrite(&stInfoHeader, 1, sizeof(stInfoHeader), pstParam->pFileOut);
		fwrite(m_pC32BMPDataBuffer, 1, stInfoHeader.biSizeImage, pstParam->pFileOut);
		fflush(pstParam->pFileOut);
		fclose(pstParam->pFileOut);
		pstParam->pFileOut = NULL;

		return 1;
	}
	break;

	case 24:
	{
		int size = pstParam->nWidth* pstParam->nHeight * 3 * sizeof(char);	//每个像素点3个字节
		stFileHeader.bfSize = stFileHeader.bfOffBits + size;
		stInfoHeader.biSizeImage = size;
		stInfoHeader.biXPelsPerMeter = 2835;								//像素每米
		stInfoHeader.biYPelsPerMeter = 2835;
		stInfoHeader.biHeight = -pstParam->nHeight;							//用高度的负值，实现数据的倒转
		fwrite(&stFileHeader, 1, sizeof(stFileHeader), pstParam->pFileOut);
		fwrite(&stInfoHeader, 1, sizeof(stInfoHeader), pstParam->pFileOut);

		fwrite(pstParam->pSrcData, size, 1, pstParam->pFileOut);

		//关闭文件
		fclose(pstParam->pFileOut);
		return 1;
	}
	break;

	}

}

CvtCalss::~CvtCalss()
{

}