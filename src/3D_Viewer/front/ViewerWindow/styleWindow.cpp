#include "./ui_mainwindow.h"
#include "mainwindow.h"

void MainWindow::on_pushButton_widgetColor_clicked() {
  QColor initialColor = QColor(58, 57, 57, 0);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");
  if (myColor.isValid()) {
    colorChanger(myColor, 0);
  }
}

void MainWindow::on_pushButton_lineColor_clicked() {
  QColor initialColor = QColor(242, 165, 60);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");
  if (myColor.isValid()) {
    colorChanger(myColor, 1);
  }
}

void MainWindow::on_pushButton_vertexColor_clicked() {
  QColor initialColor = QColor(242, 165, 60);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");
  if (myColor.isValid()) {
    colorChanger(myColor, 2);
  }
}

void MainWindow::on_radioButton_VertexNone_toggled(bool value) {
  if (value) {
    glWidget->vertexTypeChange(0);
  }
}

void MainWindow::on_radioButton_VertexCircle_toggled(bool value) {
  if (value) {
    glWidget->vertexTypeChange(1);
  }
}

void MainWindow::on_radioButton_VertexSquare_toggled(bool value) {
  if (value) {
    glWidget->vertexTypeChange(2);
  }
}

void MainWindow::on_radioButton_LineSolid_toggled(bool value) {
  if (value) {
    glWidget->lineTypeChange(true);
  }
}

void MainWindow::on_radioButton_LineDashed_toggled(bool value) {
  if (value) {
    glWidget->lineTypeChange(false);
  }
}

void MainWindow::on_radioButton_Central_toggled(bool value) {
  if (value) {
    glWidget->projectionChange(true);
  }
}

void MainWindow::on_radioButton_Parallel_toggled(bool value) {
  if (value) {
    glWidget->projectionChange(false);
  }
}

void MainWindow::on_horizontalSlider_LineSize_valueChanged(int value) {
  ui->doubleSpinBox_LineSize->setValue((double)value);
}

void MainWindow::on_doubleSpinBox_LineSize_valueChanged(double value) {
  glWidget->lineWidthChange(value);
  ui->horizontalSlider_LineSize->setValue((int)value);
}

void MainWindow::on_horizontalSlider_VertexSize_valueChanged(int value) {
  ui->doubleSpinBox_VertexSize->setValue((double)value);
}

void MainWindow::on_doubleSpinBox_VertexSize_valueChanged(double value) {
  glWidget->vertexSizeChange(value);
  ui->horizontalSlider_VertexSize->setValue((int)value);
}

void MainWindow::colorChanger(QColor color, int value) {
    QString txtcolor = "white";
    if (color.lightness() >= 130) txtcolor = "black";
  switch (value) {
    case 0:
      glWidget->widgetColorChange(color);
      ui->pushButton_widgetColor->setStyleSheet(
          QString("QPushButton {\n    	border: 1px solid rgb(242, 165, 60);\n    	background-color: %1;\n    	min-width: 70px;\n	color: %2;\n	border-radius: 7px;\n    margin-top: 3px\n}\nQPushButton:pressed {\n    background-color: %1;\n}\n\nQPushButton:flat {\n    border: none;\n}\n\nQPushButton:default {\n    border-color: navy;\n}")
                  .arg(color.name()) .arg(txtcolor));
      break;
    case 1:
      glWidget->lineColorChange(color);
      ui->pushButton_lineColor->setStyleSheet(
          QString("QPushButton {\n    	border: 1px solid rgb(242, 165, 60);\n    	background-color: %1;\n    	min-width: 70px;\n	color: %2;\n	border-radius: 7px;\n    margin-top: 3px\n}\nQPushButton:pressed {\n    background-color: %1;\n}\n\nQPushButton:flat {\n    border: none;\n}\n\nQPushButton:default {\n    border-color: navy;\n}")
                  .arg(color.name()) .arg(txtcolor));
      break;
    case 2:
      glWidget->vertexColorChange(color);
      ui->pushButton_vertexColor->setStyleSheet(
          QString("QPushButton {\n    	border: 1px solid rgb(242, 165, 60);\n    	background-color: %1;\n    	min-width: 70px;\n	color: %2;\n	border-radius: 7px;\n    margin-top: 3px\n}\nQPushButton:pressed {\n    background-color: %1;\n}\n\nQPushButton:flat {\n    border: none;\n}\n\nQPushButton:default {\n    border-color: navy;\n}")
              .arg(color.name()) .arg(txtcolor));
      break;
    default:
      break;
  }
}
