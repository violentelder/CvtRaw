#include "cvtraw.h"
#pragma once
#pragma execution_character_set("utf-8") 

int nRet;
BayerToRGB *pB2R = NULL;
CvtCalss *pCvt = NULL;
QString oFile, oFilePath;



typedef enum _MVB3D_RANGE_CHUNK_ID
{
	MVB3D_RANGE_CHUNK_ID_IMAGE = 0x617d18db,			// 图像
	MVB3D_RANGE_CHUNK_ID_WIDTH = 0xa5a53d01,			// 宽
	MVB3D_RANGE_CHUNK_ID_HEIGHT = 0xa5a53d02,			// 长
	MVB3D_RANGE_CHUNK_ID_INTENSITY = 0xa5a53d03,		// 亮度图
	MVB3D_RANGE_CHUNK_ID_WIDTH_IMG = 0xa5a53d04,		// 宽度图
	MVB3D_RANGE_CHUNK_ID_DIRECTION = 0xa5a53d05,		// 扫描方向
	MVB3D_RANGE_CHUNK_ID_START_FRAME = 0xa5a53d06,		// 首帧帧号
	MVB3D_RANGE_CHUNK_ID_SAMPLE_SCALE = 0xa5a53d07,		// 采样间隔
	MVB3D_RANGE_CHUNK_ID_SAMPLE_OFFSET = 0xa5a53d08,	// 采样偏移

	MVB3D_RANGE_CHUNK_ID_TIMESTAMP = 0xa5a50001,		// 时间戳
	MVB3D_RANGE_CHUNK_ID_GAIN = 0xa5a50002,				// 增益
	MVB3D_RANGE_CHUNK_ID_EXPOSURE = 0xa5a50003,			// 曝光
	MVB3D_RANGE_CHUNK_ID_BRIGHTNESS = 0xa5a50004,		// 亮度
	MVB3D_RANGE_CHUNK_ID_FRAME_COUNT = 0xa5a50005,		// 帧数
	MVB3D_RANGE_CHUNK_ID_EXTCOUNT = 0xa5a50006,			// 触发计数
	MVB3D_RANGE_CHUNK_ID_LINEIO = 0xa5a50007,			// 触发输入输出数
	MVB3D_RANGE_CHUNK_ID_WHITEBALANCE = 0xa5a50008,		// 白平衡
	MVB3D_RANGE_CHUNK_ID_ROIPOSITION = 0xa5a50009,		// ROI包括宽、高、水平、垂直偏移各两个字节

}MVB3D_RANGE_CHUNK_ID;



CvtRaw::CvtRaw(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->image = new QImage();


	//建立事件过滤功能
	ui.graphicsView->installEventFilter(this);
	ui.graphicsView->verticalScrollBar()->setDisabled(1);
	ui.graphicsView->horizontalScrollBar()->setDisabled(1);
	ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	

	HideC32Setting();
	ui.pushButton_change->setVisible(false);
	ui.radioButton_ply->setVisible(false);

	btn[0] = ui.radioButton_Mono8;
	btn[1] = ui.radioButton_bayer8;
	btn[2] = ui.radioButton_RGB8;
	btn[3] = ui.radioButton_ABC32;
	btn[4] = ui.radioButton_ABC32F;
	btn[5] = ui.radioButton_ABC32FP;
	for (int i = 0; i < 6; i++)
	{
		connect(btn[i], SIGNAL(toggled(bool)), this, SLOT(HideC32Setting()));
	}

	connect(ui.pushButton_openfile, SIGNAL(clicked()), this, SLOT(OpenImg()));
	connect(ui.pushButton_convert, SIGNAL(clicked()), this, SLOT(ConvertRaw()));
	connect(ui.radioButton_C32, SIGNAL(toggled(bool)), this, SLOT(ShowC32Setting()));
	connect(ui.checkBox_chunkdata, SIGNAL(toggled(bool)), this, SLOT(GetChunkData()));
	connect(ui.pushButton_change, SIGNAL(clicked()), this, SLOT(ChangeImage()));


}

CvtRaw::~CvtRaw()
{
	
}


void CvtRaw::OutputErrorInfo(QString sErrorInfo)
{
	QMessageBox::warning(NULL, "警告", QString(sErrorInfo));
	return;
}

void CvtRaw::OutputInfo(QString sErrorInfo)
{
	QMessageBox::information(NULL, "提示", QString(sErrorInfo));
	return;
}

void CvtRaw::recvShowPicSignal(QImage *image)
{
	QPixmap ConvertPixmap = QPixmap::fromImage(*image);		//The QPixmap class is an off-screen image representation that can be used as a paint device
	QGraphicsScene  *qgraphicsScene = new QGraphicsScene;	//要用QGraphicsView就必须要有QGraphicsScene搭配着用
	m_Image = new ImageWidget(&ConvertPixmap);				//实例化类ImageWidget的对象m_Image，该类继承自QGraphicsItem
	int nwith = ui.graphicsView->width();					//获取界面控件Graphics View的宽度
	int nheight = ui.graphicsView->height();				//获取界面控件Graphics View的高度
	m_Image->setQGraphicsViewWH(nwith, nheight);			//将界面控件Graphics View的width和height传进类m_Image中
	qgraphicsScene->addItem(m_Image);						//将QGraphicsItem类对象放进QGraphicsScene中

	
	ui.graphicsView->setScene(qgraphicsScene);				//Sets the current scene to scene. If scene is already being viewed, this function does nothing.
	//使视窗的大小固定在原始大小，不会随图片的放大而放大（默认状态下图片放大的时候视窗两边会自动出现滚动条，并且视窗内的视野会变大），防止图片放大后重新缩小的时候视窗太大而不方便观察图片
	ui.graphicsView->setSceneRect(QRectF(-(nwith / 2), -(nheight / 2), nwith, nheight));
	ui.graphicsView->setFocus();							//将界面的焦点设置到当前Graphics View控件
	
}


//bool CvtRaw::eventFilter(QObject *target, QEvent *event)
//{
//	if (QApplication::keyboardModifiers() == Qt::ShiftModifier)
//	{
//		ui.graphicsView->verticalScrollBar()->setDisabled(1);
//		ui.graphicsView->horizontalScrollBar()->setDisabled(1);
//		
//		if (event->type() == QEvent::Wheel)
//		{
//			QWheelEvent *wEvent = (QWheelEvent *)event;
//			ui.graphicsView->scale(1 / m_scale, 1 / m_scale);
//			qDebug() << m_scale;
//			if (wEvent->delta() > 0)
//			{
//				if (m_scale < 10)
//				{
//					m_scale += 0.2;
//				}
//				else{
//					m_scale = 10;
//				}
//			}
//			else
//			{
//				if (m_scale > 0.2)
//				{
//					m_scale -= 0.2;
//				}
//				else{
//					m_scale = 0.2;
//				}
//			}
//			ui.graphicsView->scale(m_scale, m_scale);
//			return QMainWindow::eventFilter(target, event);
//		}
//	}
//	else
//	{
//		ui.graphicsView->verticalScrollBar()->setEnabled(1);
//		ui.graphicsView->horizontalScrollBar()->setEnabled(1);
//		return QMainWindow::eventFilter(target, event);
//	}
//
//	
//		
//}


void CvtRaw::ShowC32Setting()
{
	ui.groupBox->setVisible(true);
}

void CvtRaw::HideC32Setting()
{
	ui.groupBox->setVisible(false);
}


void CvtRaw::OpenImg()
{
	//重置子widget
	ui.checkBox_chunkdata->setChecked(false);
	ui.lineEdit_width->setText(NULL);
	ui.lineEdit_height->setText(NULL);
	ui.pushButton_change->setVisible(false);
	ui.radioButton_ply->setVisible(false);
	width = 0;
	height = 0;

	//打开文件夹中的裸数据
	oFile = QFileDialog::getOpenFileName(this,
		"打开文件",
		"",
		"Raw Files(*.raw);;All(*.*)");
	
	//显示所示图片的路径
	QFileInfo OpenFileInfo;
	OpenFileInfo = QFileInfo(oFile);
	oFilePath = OpenFileInfo.filePath();
	ui.lineEdit->setText(oFilePath);

	
}

void CvtRaw::ChangeImage()
{
	switch (IntFlag)
	{
	case 0:
	{
		image = new QImage("C32.bmp");
		recvShowPicSignal(image);
		ui.pushButton_change->setText("亮度图");
		IntFlag = 1;
		break;
	}
	case 1:
	{
		image = new QImage("INTENSITY.bmp");
		recvShowPicSignal(image);
		ui.pushButton_change->setText("深度图");
		IntFlag = 0;
		break;
	}
	}
}

void CvtRaw::GetChunkData()
{
	if (ui.checkBox_chunkdata->isChecked() == 1)
	{
		if (oFile != NULL)
		{
			FILE *fp1 = NULL;
			char*  ch;

			//toLocal8Bit 支持中文
			QByteArray ba = oFilePath.toLocal8Bit();									
			ch = ba.data();
			fp1 = fopen(ch, "r");

			int i = 0;
			while (1)
			{
				i += len_tmp / 4;
				fseek(fp1, -i * 4L, SEEK_END);
				fread(&id_tmp, 4, 1, fp1);
				switch (id_tmp)
				{
				case MVB3D_RANGE_CHUNK_ID_WIDTH:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					fseek(fp1, -i * 4L - len_tmp * 1L, SEEK_END);
					fread(&width, sizeof(len_tmp), 1, fp1);
					ui.lineEdit_width->setText(QString::number(width));				
					break;
				}

				case MVB3D_RANGE_CHUNK_ID_HEIGHT:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					fseek(fp1, -i * 4L - len_tmp * 1L, SEEK_END);
					fread(&height, sizeof(len_tmp), 1, fp1);
					ui.lineEdit_height->setText(QString::number(height));
					break;
				}

				case MVB3D_RANGE_CHUNK_ID_INTENSITY:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					Int_len = len_tmp;
					IntFlag = 1;
					locus = i;
					break;
				}
				case MVB3D_RANGE_CHUNK_ID_WIDTH_IMG:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					break;
				}
				case MVB3D_RANGE_CHUNK_ID_START_FRAME:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					break;
				}
				case MVB3D_RANGE_CHUNK_ID_SAMPLE_SCALE:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);

					fseek(fp1, -i * 4L - len_tmp * 1L, SEEK_END);
					fread(&Xscale, 4, 1, fp1);

					fseek(fp1, -(i - 1) * 4L - len_tmp * 1L, SEEK_END);
					fread(&Yscale, 4, 1, fp1);

					fseek(fp1, -(i - 2) * 4L - len_tmp * 1L, SEEK_END);
					fread(&Zscale, 4, 1, fp1);
					ui.radioButton_ply->setVisible(true);
					break;
				}

				case MVB3D_RANGE_CHUNK_ID_SAMPLE_OFFSET:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					break;
				}

				case MVB3D_RANGE_CHUNK_ID_DIRECTION:
				{
					fseek(fp1, -(i - 1) * 4L, SEEK_END);
					fread(&len_tmp, 4, 1, fp1);
					break;
				}

				default:
					i++;
					len_tmp = 0;
					break;

				}

				if (id_tmp == MVB3D_RANGE_CHUNK_ID_IMAGE)
				{
					id_tmp = 0;
					break;
				}

				if ((width == 0) && (i > 20))
				{
					OutputErrorInfo("该数据不包含Chunk！");
					ui.checkBox_chunkdata->setChecked(false);
					break;

				}

			}

			fclose(fp1);
			return;
		}
		else
		{
			ui.checkBox_chunkdata->setChecked(false);
			OutputErrorInfo("请输入图像！");
			return;
		}
	}
	return;

}

void CvtRaw::ConvertRaw()
{
	pCvt = new CvtCalss();
	if (NULL == pCvt)
	{
		return;
	}
	pB2R = new BayerToRGB();
	if (NULL == pB2R)
	{
		return;
	}

	pCvt->Width = ui.lineEdit_width->text().toUInt();
	if (pCvt->Width <= 0)
	{
		OutputErrorInfo("图像宽度不能为空！");
		return;
	}

	pCvt->Height = ui.lineEdit_height->text().toUInt();
	if (pCvt->Height <= 0)
	{
		OutputErrorInfo("图像高度不能为空！");
		return;
	}

	FILE *fp = NULL;
	char*  ch;
	QByteArray ba = oFilePath.toLocal8Bit();									//toLocal8Bit 支持中文
	ch = ba.data();
	fp = fopen(ch, "r");   														//打开raw图像文件	

	unsigned int		nDataLen;
	fseek(fp, 0L, SEEK_END);													//将文件指针移动文件结尾
	nDataLen = ftell(fp);														//计算文件大小
	fseek(fp, 0L, SEEK_SET);


	if (ui.radioButton_Mono8->isChecked())										
	{
		unsigned char* pReadImage = (unsigned char*)malloc(nDataLen * sizeof(unsigned char));
		memset(pReadImage, 0, nDataLen * sizeof(unsigned char));
		fread(pReadImage, 1, nDataLen, fp);										//读取raw数据
		fclose(fp);

		char writePath[] = "Mono 8.bmp";
		BMP_DATA strBMPData = { 0 };
		strBMPData.nWidth = pCvt->Width;
		strBMPData.nHeight = pCvt->Height;
		strBMPData.nBitCount = 8;
		strBMPData.pSrcData = (unsigned char*)pReadImage;

		strBMPData.pFileOut = fopen(writePath, "wb");
		if (NULL == strBMPData.pFileOut)
		{
			return;
		}
		nRet = pCvt->SaveBmp(&strBMPData);
		image = new QImage(writePath);
		recvShowPicSignal(image);

	}

	else if (ui.radioButton_bayer8->isChecked())
	{
		unsigned char* pReadImage = (unsigned char*)malloc(nDataLen * sizeof(unsigned char));
		memset(pReadImage, 0, nDataLen * sizeof(unsigned char));
		fread(pReadImage, 1, nDataLen, fp);                                //读取raw数据
		fclose(fp);

		unsigned char* pRGB = (unsigned char*)malloc(3 * nDataLen * sizeof(unsigned char));
		memset(pRGB, 0, 3 * nDataLen * sizeof(unsigned char));

		nRet = pB2R->Bayer8ToRgb24(pReadImage, pCvt->Width, pCvt->Height, pRGB, 3 * nDataLen * sizeof(unsigned char));

		char writePath[] = "Bayer 8.bmp";
		BMP_DATA strBMPData = { 0 };
		strBMPData.nWidth = pCvt->Width;
		strBMPData.nHeight = pCvt->Height;
		strBMPData.nBitCount = 24;
		strBMPData.pSrcData = (unsigned char*)pRGB;
		strBMPData.pFileOut = fopen(writePath, "wb");
		if (NULL == strBMPData.pFileOut)
		{
			return;
		}
		nRet = pCvt->SaveBmp(&strBMPData);
		image = new QImage(writePath);
		recvShowPicSignal(image);

	}

	else if (ui.radioButton_RGB8->isChecked())
	{
		unsigned char* pReadImage = (unsigned char*)malloc(3 * nDataLen * sizeof(unsigned char));
		memset(pReadImage, 0, 3 * nDataLen * sizeof(unsigned char));
		fread(pReadImage, 3, nDataLen, fp);                                //读取raw数据
		fclose(fp);

		char writePath[] = "RGB8.bmp";
		BMP_DATA strBMPData = { 0 };
		strBMPData.nWidth = pCvt->Width;
		strBMPData.nHeight = pCvt->Height;
		strBMPData.nBitCount = 24;
		strBMPData.pSrcData = (unsigned char*)pReadImage;

		strBMPData.pFileOut = fopen(writePath, "wb");
		if (NULL == strBMPData.pFileOut)
		{
			return;
		}
		nRet = pCvt->SaveBmp(&strBMPData);
		image = new QImage(writePath);
		recvShowPicSignal(image);
	}
	else if (ui.radioButton_ABC32->isChecked())
	{
		int* pReadImage = (int*)malloc(4 * nDataLen * sizeof(int));
		memset(pReadImage, 0, 4 * nDataLen * sizeof(int));
		int* pGet = pReadImage;
		fread(pGet, 16, nDataLen, fp);										//读取raw数据
		fclose(fp);

		char writePath[] = "ABC32.ply";

		MV_POINT_CLOUD_DATA strPointData = { 0 };
		strPointData.nLinePntNum = pCvt->Width;
		strPointData.nLineNum = pCvt->Height;
		strPointData.enSrcPixelType = PixelType_Gvsp_Coord3D_ABC32;
		strPointData.nSrcDataLen = 30 * nDataLen * sizeof(int);
		strPointData.pSrcData = (unsigned char*)pReadImage;

		strPointData.pFileOut = fopen(writePath, "wb+");
		if (NULL == strPointData.pFileOut)
		{
			return;
		}
		int nRet = pCvt->SavePointCloudData(&strPointData);                           //PLY点云格式转换
		fclose(strPointData.pFileOut);

	}

	else if (ui.radioButton_ABC32F->isChecked())
	{
		float* pReadImage = (float*)malloc(4 * nDataLen * sizeof(float));
		memset(pReadImage, 0, 4 * nDataLen * sizeof(float));
		float* pGet = pReadImage;
		fread(pGet, 16, nDataLen, fp);
		fclose(fp);

		char writePath[] = "ABC32f.ply";
		MV_POINT_CLOUD_DATA strPointData = { 0 };
		strPointData.nLinePntNum = pCvt->Width;
		strPointData.nLineNum = pCvt->Height;
		strPointData.enSrcPixelType = PixelType_Gvsp_Coord3D_ABC32f;
		strPointData.nSrcDataLen = 4 * nDataLen * sizeof(float);
		strPointData.pSrcData = (unsigned char*)pReadImage;

		strPointData.pFileOut = fopen(writePath, "wb+");
		if (NULL == strPointData.pFileOut)
		{
			return;
		}
		int nRet = pCvt->SavePointCloudData(&strPointData);                           //PLY点云格式转换
		fclose(strPointData.pFileOut);

	}
	else if (ui.radioButton_ABC32FP->isChecked())
	{
		float* pReadImage = (float*)malloc(4 * nDataLen * sizeof(float));
		memset(pReadImage, 0, 4 * nDataLen * sizeof(float));
		float* pGet = pReadImage;
		fread(pGet, 16, nDataLen, fp);
		fclose(fp);

		char writePath[] = "ABC32f_planer.ply";
		MV_POINT_CLOUD_DATA strPointData = { 0 };
		strPointData.nLinePntNum = pCvt->Width;
		strPointData.nLineNum = pCvt->Height;
		strPointData.enSrcPixelType = PixelType_Gvsp_Coord3D_ABC32f_Planar;
		strPointData.nSrcDataLen = 30 * nDataLen * sizeof(float);
		strPointData.pSrcData = (unsigned char*)pReadImage;

		strPointData.pFileOut = fopen(writePath, "wb+");
		if (NULL == strPointData.pFileOut)
		{
			return;
		}
		int nRet = pCvt->SavePointCloudData(&strPointData);                           //PLY点云格式转换
		fclose(strPointData.pFileOut);

	}
	else if (ui.radioButton_C32->isChecked())
	{
		int* pReadImage = (int*)malloc(nDataLen * sizeof(int));
		memset(pReadImage, 0, nDataLen * sizeof(int));
		int* pGet = pReadImage;
		fread(pGet, 4, nDataLen, fp);										//读取raw数据

		if (ui.radioButton_8bit->isChecked() == 1)
		{
			if (IntFlag)
			{
				ui.pushButton_change->setVisible(true);
				ui.pushButton_change->setText("亮度图");
				int* pIntImage = (int*)malloc(Int_len * sizeof(char));
				memset(pIntImage, 0, Int_len * sizeof(char));
				pGet = pIntImage;
				fseek(fp, -locus * 4L - Int_len * 1L, SEEK_END);
				fread(pGet, 1, Int_len, fp);

				char writePath[] = "INTENSITY.bmp";
				BMP_DATA strBMPData = { 0 };
				strBMPData.nWidth = pCvt->Width;
				strBMPData.nHeight = pCvt->Height;
				strBMPData.nBitCount = 8;
				strBMPData.pSrcData = (unsigned char*)pIntImage;

				strBMPData.pFileOut = fopen(writePath, "wb");
				if (NULL == strBMPData.pFileOut)
				{
					return;
				}
				nRet = pCvt->SaveBmp(&strBMPData);
				fclose(fp);
			}

			nRet = pCvt->ChangeC32ToMono8((unsigned char*)pReadImage, pCvt->Width, pCvt->Height, nDataLen * sizeof(int));
			char writePath[] = "C32.bmp";
			BMP_DATA strBMPData = { 0 };
			strBMPData.nWidth = pCvt->Width;
			strBMPData.nHeight = pCvt->Height;
			strBMPData.nBitCount = 8;
			strBMPData.pSrcData = (unsigned char*)pReadImage;

			strBMPData.pFileOut = fopen(writePath, "wb");
			if (NULL == strBMPData.pFileOut)
			{
				return;
			}
			nRet = pCvt->SaveBmp(&strBMPData);
			image = new QImage(writePath);
			recvShowPicSignal(image);
		}
		else if (ui.radioButton_16bit->isChecked() == 1)
		{
			if (IntFlag)
			{
				ui.pushButton_change->setVisible(true);
				ui.pushButton_change->setText("亮度图");
				int* pIntImage = (int*)malloc(Int_len * sizeof(char));
				memset(pIntImage, 0, Int_len * sizeof(char));
				pGet = pIntImage;
				fseek(fp, -locus * 4L - Int_len * 1L, SEEK_END);
				fread(pGet, 1, Int_len, fp);

				char writePath[] = "INTENSITY.bmp";
				BMP_DATA strBMPData = { 0 };
				strBMPData.nWidth = pCvt->Width;
				strBMPData.nHeight = pCvt->Height;
				strBMPData.nBitCount = 8;
				strBMPData.pSrcData = (unsigned char*)pIntImage;

				strBMPData.pFileOut = fopen(writePath, "wb");
				if (NULL == strBMPData.pFileOut)
				{
					return;
				}
				nRet = pCvt->SaveBmp(&strBMPData);
				fclose(fp);
			}

			char writePath[] = "C32.bmp";
			BMP_DATA strBMPData = { 0 };
			strBMPData.nWidth = pCvt->Width;
			strBMPData.nHeight = pCvt->Height;
			strBMPData.nBitCount = 16;
			strBMPData.pSrcData = (unsigned char*)pReadImage;
			strBMPData.nSrcDataLen = nDataLen;
			

			strBMPData.pFileOut = fopen(writePath, "wb");
			if (NULL == strBMPData.pFileOut)
			{
				return;
			}
			nRet = pCvt->SaveBmp(&strBMPData);
			image = new QImage(writePath);
			recvShowPicSignal(image);
		}
		else if (ui.radioButton_ply->isChecked() == 1)
		{
			char writePath[] = "C32.ply";

			MV_POINT_CLOUD_DATA strPointData = { 0 };
			strPointData.nLinePntNum = pCvt->Width;
			strPointData.nLineNum = pCvt->Height;
			strPointData.x_scale = Xscale;
			strPointData.y_scale = Yscale;
			strPointData.z_scale = Zscale;
			strPointData.enSrcPixelType = PixelType_Gvsp_Coord3D_C32;
			strPointData.nSrcDataLen = 30 * nDataLen * sizeof(int);
			strPointData.pSrcData = (unsigned char*)pReadImage;

			strPointData.pFileOut = fopen(writePath, "wb+");
			if (NULL == strPointData.pFileOut)
			{
				return;
			}
			int nRet = pCvt->SavePointCloudData(&strPointData);                           //PLY点云格式转换
			fclose(strPointData.pFileOut);
		}
		
	}
	else
	{
		OutputErrorInfo("解析模式不能为空！");
		return;

	}
	if (pB2R)
	{
		delete pB2R;
		pB2R = NULL;
	}

	if (pCvt)
	{
		delete pCvt;
		pCvt = NULL;
	}

	OutputInfo("转换成功！");


}

