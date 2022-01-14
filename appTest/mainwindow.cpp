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
  addOverlayBtn_ = new QPushButton{"Add Overlay", this};
  removeOverlayBtn_ = new QPushButton{"Remove Overlay", this};

  fitToWindowBtn_ = new QCheckBox{"Fit to Window", this};
  fitToWindowBtn_->setChecked(false);

  buttonsLayout->addWidget(zoomInBtn_);
  buttonsLayout->addWidget(zoomOutBtn_);
  buttonsLayout->addWidget(normalSizeBtn_);
  buttonsLayout->addWidget(addOverlayBtn_);
  buttonsLayout->addWidget(removeOverlayBtn_);
  buttonsLayout->addWidget(fitToWindowBtn_);
  

  connect(zoomInBtn_, &QPushButton::clicked, this, &MainWidget::zoomInBtn_clicked);
  connect(zoomOutBtn_, &QPushButton::clicked, this, &MainWidget::zoomOutBtn_clicked);
  connect(addOverlayBtn_, &QPushButton::clicked, this, &MainWidget::addOverlayBtn_clicked);
  connect(removeOverlayBtn_, &QPushButton::clicked, this, &MainWidget::removeOverlayBtn_clicked);
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
  connect(imageViewer_, &iv::ImageViewerWidget::imageMouseRelease, this, &MainWidget::imageMouseRelease);
  connect(imageViewer_, &iv::ImageViewerWidget::imageMouseDoubleClick, this, &MainWidget::imageMouseDoubleClick);

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

void MainWidget::imageMousePress(const QPointF &p, QMouseEvent *e)
{
  QString message;
  if (e->modifiers() & Qt::ControlModifier)
    message = tr("mouse press at (%1, %2) with Ctrl").arg(p.x()).arg(p.y());
  else 
    message = tr("mouse press at (%1, %2)").arg(p.x()).arg(p.y());

  window_->statusBar()->showMessage(message);
}

void MainWidget::imageMouseRelease(const QPointF &p, QMouseEvent *e)
{
  QString message;
  if (e->modifiers() & Qt::ControlModifier)
    message = tr("mouse release at (%1, %2) with Ctrl").arg(p.x()).arg(p.y());
  else 
    message = tr("mouse release at (%1, %2)").arg(p.x()).arg(p.y());

  window_->statusBar()->showMessage(message);
}

void MainWidget::imageMouseDoubleClick(const QPointF &p, QMouseEvent *e)
{
  QString message;
  
  if (e->modifiers() & Qt::ControlModifier)
    message = tr("mouse double click at (%1, %2) with Ctrl").arg(p.x()).arg(p.y());
  else 
    message = tr("mouse double click at *(%1, %2)").arg(p.x()).arg(p.y());

  message = tr("mouse double click at (%1, %2)").arg(p.x()).arg(p.y());
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

void MainWidget::addOverlayBtn_clicked()
{
  const QImage &f = imageViewer_->image();
  QImage f100{f.size(), QImage::Format_ARGB32};

  for (int l=0; l < f.height(); ++l) {
    const uchar *fline = f.constScanLine(l);
    QRgb *f100line = reinterpret_cast<QRgb*>(f100.scanLine(l));
    
    for (int c=0; c < f.width(); ++c) {
      if (fline[c] > 100) {
        f100line[c] = qRgba(255, 0, 0, 128);
      }
      else {
        f100line[c] = qRgba(255, 255, 255, 0);
      }
    }
  }

  imageViewer_->setOverlayImage(f100);
}

void MainWidget::removeOverlayBtn_clicked()
{
  imageViewer_->removeOverlay();
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