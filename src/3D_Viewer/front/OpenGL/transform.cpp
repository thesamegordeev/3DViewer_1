#include "glwidget.h"

/*---------------------Mouse manipulation---------------------*/
void GLWidget::mousePressEvent(QMouseEvent *event) {
  mPos = event->position();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  xRot = event->position().x() - mPos.x();
  yRot = event->position().y() - mPos.y();
  mPos = event->position();
  update();
}
void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  xRot = 0;
  yRot = 0;
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;
  int numSteps = 0;
  if (!numPixels.isNull()) {
    numSteps = numPixels.y();
  } else if (!numDegrees.isNull()) {
    numSteps = numDegrees.y() / 15;
  }
  double zoomFactor = 1.0 + numSteps * 0.001f;
  rescaleObj(zoomFactor, ObjDraw);
  update();
}

/*---------------------Rotation via buttons---------------------*/

void GLWidget::rotateObjX(double angle) {
  if (ObjDraw != nullptr) {

    rotateX(angle, ObjDraw);
    update();
  }
}

void GLWidget::rotateObjY(double angle) {
  if (ObjDraw != nullptr) {
    if (!LineSolid) angle *= -1;
    rotateY(angle, ObjDraw);
    update();
  }
}

void GLWidget::rotateObjZ(double angle) {
  if (ObjDraw != nullptr) {
    if (!LineSolid) angle *= -1;
    rotateZ(angle, ObjDraw);
    update();
  }
}

/*---------------------Zoom via buttons---------------------*/
void GLWidget::zoomObj(double scale) {
  if (ObjDraw != nullptr) {
    double zoomFactor = 1.0 + scale * 0.01f;
    if (zoomFactor < 0.1f) {
      zoomFactor = 0.1f;
    }
    rescaleObj(zoomFactor, ObjDraw);
    update();
  }
}

/*---------------------Move via buttons---------------------*/
void GLWidget::moveObjX(double val) {
  if (ObjDraw != nullptr) {
    moveX(val, ObjDraw);
    update();
  }
}
void GLWidget::moveObjY(double val) {
  if (ObjDraw != nullptr) {
    moveY(val, ObjDraw);
    update();
  }
}
void GLWidget::moveObjZ(double val) {
  if (ObjDraw != nullptr) {
    moveZ(val, ObjDraw);
    update();
  }
}
