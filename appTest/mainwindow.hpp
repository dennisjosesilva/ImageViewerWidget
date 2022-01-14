#pragma once

#include <QMainWindow>
#include <QPointF>
#include "ImageViewerWidget/ImageViewerWidget.hpp"

namespace iv = ImageViewerWidget;

class QPushButton;
class QCheckBox;
class QComboBox;


class MainWidget : public QWidget
{
  Q_OBJECT

public:
  MainWidget(QMainWindow *window);

protected slots:
  void zoomInBtn_clicked();
  void zoomOutBtn_clicked();
  void normalSizeBtn_clicked();
  void addOverlayBtn_clicked();
  void removeOverlayBtn_clicked();
  void fitToWindowBtn_toggled(bool checked);
  void imageCombo_currentIndexChanged(int index);

  

protected:
  void loadImage(const QString &filename);
  void imageMousePress(const QPointF &p, QMouseEvent *e);
  void imageMouseRelease(const QPointF &p, QMouseEvent *e);
  void imageMouseDoubleClick(const QPointF &p, QMouseEvent *e);

private:
  QMainWindow *window_;

  iv::ImageViewerWidget *imageViewer_;

  QPushButton *zoomInBtn_;
  QPushButton *zoomOutBtn_;
  QPushButton *normalSizeBtn_;
  QPushButton *addOverlayBtn_;
  QPushButton *removeOverlayBtn_;
  QCheckBox *fitToWindowBtn_;
  QComboBox *imageCombo_;

};

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
};