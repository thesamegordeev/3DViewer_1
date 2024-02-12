#include "glwidget.h"

void GLWidget::widgetColorChange(QColor value) {
  ViewerColor = value;
  update();
}

void GLWidget::lineColorChange(QColor value) {
  LineColor = value;
  update();
}

void GLWidget::vertexColorChange(QColor value) {
  VertexColor = value;
  update();
}

void GLWidget::vertexTypeChange(int value) {
  VertexType = value;
  update();
}

void GLWidget::lineTypeChange(bool value) {
  LineSolid = value;
  update();
}

void GLWidget::projectionChange(bool value) {
  CentralProjection = value;
  update();
}

void GLWidget::lineWidthChange(double value) {
  LineWidth = value;
  update();
}

void GLWidget::vertexSizeChange(double value) {
  VertexSize = value;
  update();
}

void GLWidget::vertexStyleHandler() {
    if (!LineSolid) {
      glLineStipple(1, 0x00ff);
      glEnable(GL_LINE_STIPPLE);
    }
  glVertexPointer(3, GL_DOUBLE, 0, ObjDraw->vertex_arr);
  switch (VertexType) {
    case 1:
      glColor3f(VertexColor.redF(), VertexColor.greenF(), VertexColor.blueF());
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, ObjDraw->vertex_count);
      break;
    case 2:
      glColor3f(VertexColor.redF(), VertexColor.greenF(), VertexColor.blueF());
      glDisable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, ObjDraw->vertex_count);
      break;
    default:
      break;
  }
}

void GLWidget::projectionStyleHandler() {
  //glMatrixMode(GL_PROJECTION);
  //glLoadIdentity();
  if (CentralProjection == true) {
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5000.0);
  } else {
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 5000.0);
  }
  //glMatrixMode(GL_MODELVIEW);
}

void GLWidget::lineStyleHandler() {

//  glEnable(GL_LINE_SMOOTH);
  if (!LineSolid) {
    glLineStipple(1, 0x00ff);
    glEnable(GL_LINE_STIPPLE);
#ifndef DASHED_RENDERS
    double* negativeVertexes = (double *)calloc(ObjDraw->vertex_count * 3, sizeof(double));
    for (int i = 0; i < ObjDraw->vertex_count * 3; i += 3) {
        negativeVertexes[i] =  ObjDraw->vertex_arr[i];
        negativeVertexes[i + 1] = -1 * ObjDraw->vertex_arr[i + 1];
        negativeVertexes[i + 2] = ObjDraw->vertex_arr[i + 2];
    }
    glVertexPointer(3, GL_DOUBLE, 0, negativeVertexes);
    glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
    glDrawElements(GL_LINES, ObjDraw->connections * 2, GL_UNSIGNED_INT, ObjDraw->facets_arr);
    free(negativeVertexes);
#else
    glVertexPointer(3, GL_DOUBLE, 0, ObjDraw->vertex_arr);
    glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
    glDrawElements(GL_LINES, ObjDraw->connections * 2, GL_UNSIGNED_INT, ObjDraw->facets_arr);
#endif
  } else {
      glDisable(GL_LINE_STIPPLE);
      glVertexPointer(3, GL_DOUBLE, 0, ObjDraw->vertex_arr);
      glColor3f(LineColor.redF(), LineColor.greenF(), LineColor.blueF());
      glDrawElements(GL_LINES, ObjDraw->connections * 2, GL_UNSIGNED_INT, ObjDraw->facets_arr);
  }

}
