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
    imageLabel_->setMargin(0);
    
    imageLabel_->setFrameStyle(QFrame::NoFrame);        
    imageLabel_->setScaledContents(true);

    scrollArea_->setBackgroundRole(QPalette::Dark);
    scrollArea_->setFrameStyle(QFrame::NoFrame);
    scrollArea_->setWidget(imageLabel_);    
    scrollArea_->setVisible(false);
    
    mainLayout->setContentsMargins(0, 0, 0, 0);    
    mainLayout->setSpacing(0);    

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
    normalImageSize_ = QSize{newImage.size()};

    normalSize();

    scrollArea_->setVisible(true);
    scrollArea_->setEnabled(true);

    imageLabel_->update();
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

  QPointF ImageViewerWidget::scrollAreaPointMap(const QPointF &p) const
  {
    QPointF scrollOffset = QPointF(scrollArea_->horizontalScrollBar()->value(), 
       scrollArea_->verticalScrollBar()->value());

    return p + scrollOffset;
  }

  QPointF ImageViewerWidget::normalisePoint(const QPointF &p) const
  {
    return QPointF{ p.x() / imageLabel_->size().width(), 
      p.y() / imageLabel_->size().height() };
  }

  QPointF ImageViewerWidget::mapScrollPointToImagePoint(
    const QPointF &p_normalised) const
  {
    return QPointF{ p_normalised.x() * normalImageWidth(), 
      p_normalised.y() * normalImageHeight() };
  }


  void ImageViewerWidget::mousePressEvent(QMouseEvent *e)
  {
    QPointF p = scrollAreaPointMap(e->localPos()) - QPointF{ 2, 4 };
    QPointF p_normalised = normalisePoint(p);

    if ( 0 <= p_normalised.x() && p_normalised.x() < 1.0 && 
         0 <= p_normalised.y() && p_normalised.y() < 1.0) {      

      QPointF p_transformed = mapScrollPointToImagePoint(p_normalised);
      emit imageMousePress(p_transformed);
    }

    update();
  }

  void ImageViewerWidget::mouseReleaseEvent(QMouseEvent *e)
  {
    QPointF p = scrollAreaPointMap(e->localPos()) - QPointF{ 2, 4 };
    QPointF p_normalised = normalisePoint(p);

    if ( 0 <= p_normalised.x() && p_normalised.x() < 1.0 && 
         0 <= p_normalised.y() && p_normalised.y() < 1.0) {      

      QPointF p_transformed = mapScrollPointToImagePoint(p_normalised);
      emit imageMouseRelease(p_transformed);
    }

    update();   
  }

  void ImageViewerWidget::mouseDoubleClickEvent(QMouseEvent *e)
  {
    QPointF p = scrollAreaPointMap(e->localPos()) - QPointF{ 2, 4 };
    QPointF p_normalised = normalisePoint(p);

    if ( 0 <= p_normalised.x() && p_normalised.x() < 1.0 && 
         0 <= p_normalised.y() && p_normalised.y() < 1.0) {      

      QPointF p_transformed = mapScrollPointToImagePoint(p_normalised);
      emit imageMouseDoubleClick(p_transformed);
    }

    update();
  }
}