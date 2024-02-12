#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() {
  if (ObjDraw != nullptr) {
    free_object(ObjDraw);
  }
}

void GLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void GLWidget::resizeGL(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glTranslatef(0, 0, 2);
  // glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
  glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
  glClearColor(ViewerColor.redF(), ViewerColor.greenF(), ViewerColor.blueF(),
               ViewerColor.alphaF());
  glPointSize(VertexSize);
  double linewidth[2];
  glGetDoublev(GL_ALIASED_LINE_WIDTH_RANGE, linewidth);
  glLineWidth(linewidth[0] +
              (LineWidth / 100 *
               (linewidth[1] -
                linewidth[0])));  // adjust linewidth for different hardware
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (ObjDraw != nullptr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    projectionStyleHandler();

    glTranslatef(0, 0, -2);

    rotateX(yRot, ObjDraw);  // mouse rotation
    rotateY(xRot, ObjDraw);
    drawObj();
  }
}

void GLWidget::drawObj() {
  glEnableClientState(GL_VERTEX_ARRAY);
  lineStyleHandler();
  vertexStyleHandler();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::readObjFile(QString fileName) {
  QByteArray inputBytes = fileName.toUtf8();
  char *convertedFileName = strdup(inputBytes.constData());

  FILE *file_3d = NULL;
  if (!open_file(convertedFileName, &file_3d)) {
    if (ObjDraw != nullptr) {
      free_object(ObjDraw);
    }
    ObjDraw = (object *)calloc(1, sizeof(object));
    count_options(file_3d, ObjDraw);
    if (filling_object(file_3d, ObjDraw)) {
      QMessageBox::information(nullptr, "File .obj parsing error",
                               "Application failed to parse chosen file.");
      if (ObjDraw != nullptr) {
        free_object(ObjDraw);
        ObjDraw = nullptr;
      }
    } else {
      totalVertex = ObjDraw->vertex_count;
      totalEdges = ObjDraw->connections;
      initialRescaleObj(ObjDraw);
      update();
    }
  } else {
    QMessageBox::information(nullptr, "File open error",
                             "Application failed to open chosen file. Check if "
                             "file's path and extension are correct");
  }
  free(convertedFileName);
  if (file_3d) {
    fclose(file_3d);
  }
}
