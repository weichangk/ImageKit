#include "stylemgr.h"
#include "qapplication.h"
#include "qwidget.h"
#include "QtCore"

void StyleMgr::setStyleToApp(const QString &qssFolder)
{
  QString allStyle;
  QDir dir(qssFolder);
  QFileInfoList fileList = dir.entryInfoList(QDir::Files);
  for (auto fileinfo : fileList)
  {
    if (fileinfo.suffix() != "qss")
      continue;
    QString path = QString("%1/%2").arg(qssFolder).arg(fileinfo.fileName());
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QString style = file.readAll();
    if (!style.isEmpty())
    {
      allStyle += style;
    }
    file.close();
  }
  qApp->setStyleSheet(allStyle);
}

void StyleMgr::setStyleToWidget(QWidget *widget, const QString &fileName)
{
  QFile fileQss(fileName);
  fileQss.open(QFile::ReadOnly);
  widget->setStyleSheet(fileQss.readAll());
  fileQss.close();
}
