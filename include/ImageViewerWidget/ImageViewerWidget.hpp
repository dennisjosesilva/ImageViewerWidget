#pragma once 

#include <QWidget>
#include <QPointF>
#include <QSize>

class QLabel;
class QScrollArea;
class QImage;
class QScrollBar;
class QMouseEvent;



namespace ImageViewerWidget
{
  class ImageViewerWidget : public QWidget
  {
    Q_OBJECT
  public:
    ImageViewerWidget(QWidget *parent=nullptr);

    inline QImage& image() { return image_; };
    inline const QImage& image() const { return image_; }

    bool saveImage(const QString &fileName);
    bool loadImage(const QString &fileName);

    void setImage(const QImage &newImage);

    inline QSize normalImageSize() const { return normalImageSize_; }
    inline int normalImageWidth() const { return normalImageSize_.width(); }
    inline int normalImageHeight() const { return normalImageSize_.height(); }
    inline QScrollArea *scrollAreaWidget() { return scrollArea_; }

    void fitToWidget(); 
    void unfitToWidget();    

    void normalSize();    
    void zoomIn();
    void zoomOut();   
    void scaleImage(double factor); 

    inline double scaleFactor() const { return scaleFactor_; }

  protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

  public:
  signals:
    void imageMousePress(const QPointF &p);
    void imageMouseRelease(const QPointF &p);
    void imageMouseDoubleClick(const QPointF &p);

  private:
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    
    QPointF scrollAreaPointMap(const QPointF &p) const;
    QPointF normalisePoint(const QPointF &p) const;
    QPointF mapScrollPointToImagePoint(const QPointF &p_normalised) const;


  private:
    QSize normalImageSize_;
    QImage image_;
    QLabel *imageLabel_;
    QScrollArea *scrollArea_;
    double scaleFactor_;
  };
}