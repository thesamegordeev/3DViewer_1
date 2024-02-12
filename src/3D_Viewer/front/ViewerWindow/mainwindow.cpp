#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D Viewer");
  glWidget = new GLWidget(this);
  ui->horizontalLayout->insertWidget(0, glWidget);
#ifdef Q_OS_MAC
  settings = new QSettings("teamLoraleec.ru", "3DViewer", this);
#else
  settings = new QSettings("Team Loraleec", "3DViewer", this);
#endif
  downloadSettings();
  update();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
  delete glWidget;
}

void MainWindow::on_pushButton_openFile_clicked() {
  QDir::setCurrent(QCoreApplication::applicationDirPath());
  QDir dir(QDir::currentPath());
  dir.cdUp();
  dir.cd("obj_files");
  QString dataSamplesDir = dir.absolutePath();
  QString filePath = QFileDialog::getOpenFileName(
      this, "Choose file", dataSamplesDir, ".obj (*.obj)");
  if (filePath.isEmpty()) {
    QMessageBox::information(
        nullptr, "File error",
        "The file has not been selected or the file is not an .obj");
  } else {
    initTransformSettings();
    glWidget->readObjFile(filePath);

    displayObjInfo(filePath);
  }
}

void MainWindow::displayObjInfo(QString filePath) {
  QFileInfo fi(filePath);
  QString name = fi.fileName();
  ui->label_name->setText(name);
  ui->label_vertex->setText(QString::number(glWidget->totalVertex, 10));
  ui->label_polygons->setText(QString::number(glWidget->totalEdges, 10));
}

void MainWindow::on_pushButton_screenshot_clicked() {
  if (timer == nullptr || !(timer->isActive())) {
    QImage img = glWidget->grabFramebuffer();
    QString screenshot = QFileDialog::getSaveFileName(
        this, tr("Save File"), QDir::homePath(), tr("Images (*.jpeg *.bmp)"));
    if (!screenshot.isNull()) {
      img.save(screenshot);
    }
  }
}

void MainWindow::on_pushButton_GIF_clicked() {
  if (timer == nullptr || !(timer->isActive())) {
    timer = new QTimer(this);
    gif = new QGifImage(QSize(640, 480));
    QVector<QRgb> ctable;
    ctable << qRgb(255, 255, 255) << qRgb(0, 0, 0) << qRgb(255, 0, 0)
           << qRgb(0, 255, 0) << qRgb(0, 0, 255) << qRgb(255, 255, 0)
           << qRgb(0, 255, 255) << qRgb(255, 0, 255);
    gif->setGlobalColorTable(ctable, QColor("white"));
    //        gif->setDefaultTransparentColor(QColor("black"));
    gif->setDefaultDelay(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(gifAddFrame()));
    timer->start(100);
  }
}

void MainWindow::gifAddFrame() {
  if (counter < 50) {
    gif->addFrame(glWidget->grabFramebuffer().scaled(640, 480));
    counter++;
  } else {
    timer->stop();
    timer->disconnect();
    timer = nullptr;
    delete timer;
    gif->save("../screencap.gif");
    delete gif;
    gif = nullptr;
    counter = 0;
  }
}

