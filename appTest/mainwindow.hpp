#pragma once

#include <QMainWindow>
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
  void fitToWindowBtn_toggled(bool checked);
  void imageCombo_currentIndexChanged(int index);

protected:
  void loadImage(const QString &filename);

private:
  QMainWindow *window_;

  iv::ImageViewerWidget *imageViewer_;

  QPushButton *zoomInBtn_;
  QPushButton *zoomOutBtn_;
  QPushButton *normalSizeBtn_;
  QCheckBox *fitToWindowBtn_;
  QComboBox *imageCombo_;

};

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();
};