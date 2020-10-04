#ifndef CVTRAW_H
#define CVTRAW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include "ui_cvtraw.h"
#include "BayerToRGB.h"
#include "Convert.h"
#include "ImageWidget.h"


class CvtRaw : public QMainWindow
{
	Q_OBJECT

public:
	CvtRaw(QWidget *parent = 0);
	~CvtRaw();
	
	
	/*bool eventFilter(QObject *target, QEvent *event);*/
	//接收并显示图片的函数
	void recvShowPicSignal(QImage *image);
	
	
private:
	Ui::CvtRawClass ui;
	QImage			*image;
	QPixmap			*Pixmap;
	QRadioButton	*btn[6];
	ImageWidget		*m_Image;

	//Chunk Data
	int len_tmp = 0;
	int id_tmp = 0;
	int locus;
	bool IntFlag = 0;
	int Int_len = 0;

	int width = 0;
	int height = 0;
	float Xscale;
	float Yscale;
	float Zscale;


	

	void OutputErrorInfo(QString sErrorInfo);
	void OutputInfo(QString sErrorInfo);

	public slots:     //槽函数声明标志

	void ShowC32Setting();
	void HideC32Setting();
	void OpenImg();
	void ConvertRaw();
	void GetChunkData();
	void ChangeImage();
};

#endif // CVTRAW_H
