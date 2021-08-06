#include "ImageViewerWidget/ImageViewerWidget.hpp"

#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QImage>
#include <QMouseEvent>
#include <QLayout>
#include <QVBoxLayout>
#include <QImageWriter>
#include <QImageReader>

namespace ImageViewerWidget
{
  ImageViewerWidget::ImageViewerWidget(QWidget *parent)
    : QWidget{parent},
      imageLabel_{new QLabel},
      scrollArea_{new QScrollArea},
      scaleFactor_{1}      
  {
    QLayout *mainLayout = new QVBoxLayout;

    imageLabel_->setBackgroundRole(QPalette::Base);
    imageLabel_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel_->setScaledContents(true);

    scrollArea_->setBackgroundRole(QPalette::Dark);
    scrollArea_->setWidget(imageLabel_);
    scrollArea_->setVisible(false);
    
    mainLayout->addWidget(scrollArea_);
    setLayout(mainLayout);
  }

  bool ImageViewerWidget::saveImage(const QString &fileName)
  {
    QImageWriter writer{fileName};
    
    if (writer.write(image_))
      return true;
    
    return false;
  }

  bool ImageViewerWidget::loadImage(const QString &fileName)
  {
    QImageReader reader{fileName};
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    
    if (newImage.isNull()) 
      return false;

    setImage(newImage);

    return true;
  }

  void ImageViewerWidget::setImage(const QImage &newImage)
  {
    image_ = newImage;
    imageLabel_->setPixmap(QPixmap::fromImage(image_));
    scaleFactor_ = 1.0;

    normalSize();

    scrollArea_->setVisible(true);
    scrollArea_->setEnabled(true);
  }

  void ImageViewerWidget::fitToWidget()
  {
    scrollArea_->setWidgetResizable(true);
  }

  void ImageViewerWidget::unfitToWidget()
  {
    scrollArea_->setWidgetResizable(false);
  }

  void ImageViewerWidget::normalSize()
  {
    imageLabel_->adjustSize();
    scaleFactor_ = 1.0;
  }

  void ImageViewerWidget::zoomIn()
  {
    scaleImage(1.25);
  }

  void ImageViewerWidget::zoomOut()
  {
    scaleImage(0.8);
  }

  void ImageViewerWidget::scaleImage(double factor)
  {
    scaleFactor_ *= factor;
    imageLabel_->resize(scaleFactor_ * imageLabel_->pixmap()->size());

    adjustScrollBar(scrollArea_->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea_->verticalScrollBar(), factor);    
  } 

  void ImageViewerWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
  {
    scrollBar->setValue( static_cast<int>(factor * scrollBar->value()) +
      ((factor - 1) * scrollBar->pageStep() / 2));
  }

  void ImageViewerWidget::mousePressEvent(QMouseEvent *e)
  {
    update();
  }


  void ImageViewerWidget::mouseReleaseEvent(QMouseEvent *e)
  {
    update();
  }

  void ImageViewerWidget::mouseDoubleClickEvent(QMouseEvent *e)
  {
    update();
  }
}