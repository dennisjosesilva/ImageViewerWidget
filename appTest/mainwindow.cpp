#include "ImageViewerWidget/ImageViewerWidget.hpp"
#include "mainwindow.hpp"

#include <QPushButton>
#include <QCheckBox>
#include <QImage>
#include <QStatusBar>
#include <QComboBox>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QMainWindow *window)
  :window_{window}
{
  setWindowTitle("Image Viewer Test App");
  resize(400, 700);

  imageViewer_ = new iv::ImageViewerWidget(this);
  
  QLayout *mainLayout = new QVBoxLayout;
  QHBoxLayout *buttonsLayout = new QHBoxLayout;
  QHBoxLayout *imageViewerLayout = new QHBoxLayout;

  zoomInBtn_ = new QPushButton{"Zoom In", this};
  zoomOutBtn_ = new QPushButton{"Zoom Out", this};
  normalSizeBtn_ = new QPushButton{"Normal Size", this};
  
  fitToWindowBtn_ = new QCheckBox{"Fit to Window", this};
  fitToWindowBtn_->setChecked(false);

  buttonsLayout->addWidget(zoomInBtn_);
  buttonsLayout->addWidget(zoomOutBtn_);
  buttonsLayout->addWidget(normalSizeBtn_);
  buttonsLayout->addWidget(fitToWindowBtn_);

  connect(zoomInBtn_, &QPushButton::clicked, this, &MainWidget::zoomInBtn_clicked);
  connect(zoomOutBtn_, &QPushButton::clicked, this, &MainWidget::zoomOutBtn_clicked);
  connect(normalSizeBtn_, &QPushButton::clicked, this, &MainWidget::normalSizeBtn_clicked);
  connect(fitToWindowBtn_, &QCheckBox::toggled, this, &MainWidget::fitToWindowBtn_toggled);

  buttonsLayout->addStretch();
  buttonsLayout->setSpacing(10);

  mainLayout->addItem(buttonsLayout);

  imageViewerLayout->addWidget(imageViewer_);
  mainLayout->addItem(imageViewerLayout);

  imageCombo_ = new QComboBox(this);
  imageCombo_->addItem("Zuckerberg", "../../images/Zuckerberg.pgm");
  imageCombo_->addItem("oilpainting", "../../images/oilpainting.pgm");
  imageCombo_->addItem("donald", "../../images/donald.pgm");
  imageCombo_->addItem("texting", "../../images/texting.pgm");
  imageCombo_->addItem("baboon", "../../images/baboon.pgm");

  connect(imageCombo_, QOverload<int>::of(&QComboBox::currentIndexChanged), 
    this, &MainWidget::imageCombo_currentIndexChanged);

  buttonsLayout->addWidget(new QLabel("Image:"));
  buttonsLayout->addWidget(imageCombo_);

  loadImage("../../images/Zuckerberg.pgm");

  connect(imageViewer_, &iv::ImageViewerWidget::imageMousePress, this, &MainWidget::imageMousePress);

  setLayout(mainLayout);
}

void MainWidget::loadImage(const QString &fileName)
{
  const QImage &image = imageViewer_->image();
  imageViewer_->loadImage(fileName);  

  QString message = 
    tr("load: %4, dim: %1 x %2, depth: %3").arg(image.width())
      .arg(image.height()).arg(image.depth()).arg(fileName);
  window_->statusBar()->showMessage(message);
}

void MainWidget::imageMousePress(const QPointF &p)
{
  QString message = tr("mouse press at (%1, %2)").arg(p.x()).arg(p.y());
  window_->statusBar()->showMessage(message);
}

void MainWidget::zoomInBtn_clicked()
{
  imageViewer_->zoomIn();
}

void MainWidget::zoomOutBtn_clicked()
{
  imageViewer_->zoomOut();
}

void MainWidget::normalSizeBtn_clicked()
{
  imageViewer_->normalSize();
}

void MainWidget::imageCombo_currentIndexChanged(int index)
{
  QString filePath = qvariant_cast<QString>(imageCombo_->currentData());
  loadImage(filePath);
}

void MainWidget::fitToWindowBtn_toggled(bool checked)
{
  if (checked) {
    imageViewer_->fitToWidget();
    zoomInBtn_->setEnabled(false);
    zoomOutBtn_->setEnabled(false);
    normalSizeBtn_->setEnabled(false);
  }
  else {
    imageViewer_->unfitToWidget();
    imageViewer_->normalSize();

    zoomInBtn_->setEnabled(true);
    zoomOutBtn_->setEnabled(true);
    normalSizeBtn_->setEnabled(true);
  }
}

MainWindow::MainWindow()
{
  MainWidget *widget = new MainWidget(this);
  setCentralWidget(widget);
}