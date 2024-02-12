#include "./ui_mainwindow.h"
#include "mainwindow.h"

/*---------------------Rotate via buttons---------------------*/
void MainWindow::on_horizontalSlider_rotX_valueChanged(int value) {
  glWidget->rotateObjX(value - currentRotateX);
  currentRotateX = value;
  ui->spinBox_rotX->setValue(value);
}

void MainWindow::on_spinBox_rotX_valueChanged(int value) {
  ui->horizontalSlider_rotX->setValue(value);
}

void MainWindow::on_horizontalSlider_rotY_valueChanged(int value) {
  glWidget->rotateObjY(value - currentRotateY);
  currentRotateY = value;
  ui->spinBox_rotY->setValue(value);
}

void MainWindow::on_spinBox_rotY_valueChanged(int value) {
  ui->horizontalSlider_rotY->setValue(value);
}

void MainWindow::on_horizontalSlider_rotZ_valueChanged(int value) {
  glWidget->rotateObjZ(value - currentRotateZ);
  currentRotateZ = value;
  ui->spinBox_rotZ->setValue(value);
}

void MainWindow::on_spinBox_rotZ_valueChanged(int value) {
  ui->horizontalSlider_rotZ->setValue(value);
}

/*---------------------Scale via buttons---------------------*/
void MainWindow::on_horizontalSlider_Scale_valueChanged(int value) {
  if (currentScale > value) {
    glWidget->zoomObj(-2);
  } else {
    glWidget->zoomObj(2);
  }
  currentScale = value;
}

/*---------------------Move via buttons---------------------*/
void MainWindow::on_horizontalSlider_moveX_valueChanged(int value) {
  double moveVal = (value - currentMoveX) / 100.0;
  glWidget->moveObjX(moveVal);
  currentMoveX = value;
  ui->spinBox_MoveX->setValue(value);
}

void MainWindow::on_horizontalSlider_moveY_valueChanged(int value) {
  double moveVal = (value - currentMoveY) / 100.0;
  glWidget->moveObjY(moveVal);
  currentMoveY = value;
  ui->spinBox_MoveY->setValue(value);
}

void MainWindow::on_horizontalSlider_moveZ_valueChanged(int value) {
  double moveVal = (value - currentMoveZ) / 100.0;
  glWidget->moveObjZ(moveVal);
  currentMoveZ = value;
  ui->spinBox_MoveZ->setValue(value);
}

void MainWindow::on_spinBox_MoveX_valueChanged(int value) {
  ui->horizontalSlider_moveX->setValue(value);
}

void MainWindow::on_spinBox_MoveY_valueChanged(int value) {
  ui->horizontalSlider_moveY->setValue(value);
}

void MainWindow::on_spinBox_MoveZ_valueChanged(int value) {
  ui->horizontalSlider_moveZ->setValue(value);
}
