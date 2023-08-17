#include "mainwindow.h"

#include "eopenglwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->toolBar->setMovable(false);
  ui->tabsWidget->setHidden(true);

  //  for (auto button : ui->buttonGroup_tabs_buttons->buttons()) {
  //      connect(button, SIGNAL(clicked()), this, SLOT(showTab()));
  //  }
  connect(ui->pushButton_transformations, SIGNAL(clicked()), this,
          SLOT(showTab()));
  connect(ui->pushButton_capture, SIGNAL(clicked()), this, SLOT(showTab()));
  connect(ui->pushButton_view_settings, SIGNAL(clicked()), this,
          SLOT(showTab()));
  connect(ui->pushButton_info, SIGNAL(clicked()), this, SLOT(showTab()));

  connect(ui->pushButton_vertices_color, SIGNAL(clicked()), this,
          SLOT(getColor()));
  connect(ui->pushButton_edges_color, SIGNAL(clicked()), this,
          SLOT(getColor()));
  connect(ui->pushButton_background_color, SIGNAL(clicked()), this,
          SLOT(getColor()));
}

MainWindow::~MainWindow() { delete ui; }

////////////////////////////////////////////////////////////////////////////
// FILE OPENING
void MainWindow::on_actionOpenModel_triggered() {
  file = QFileDialog::getOpenFileName(this, "Open File", file, "*.obj");
  QFileInfo file_info(file);
  if (file_info.isFile() == true) {
    structClean(&object);
    int error =
        getGeometryInfo(file_info.filePath().toLatin1().data(), &object);
    if (!error) {
      ui->file_info->setText("");
      fileInfoFilling(&object, file_info);
      ui->openGLWidget->object = object;
    }
  }
}

void MainWindow::fileInfoFilling(geometry_info* pobject, QFileInfo file_info) {
  QString filename = file_info.fileName();
  QString filepath = file_info.absolutePath();
  QString filesize = QString::number(file_info.size() / 1000.0);
  QString v_count = QString::number(pobject->vertices_count);
  QString f_count = QString::number(pobject->facets_count);
  QString e_count = QString::number(edgesCounting(pobject));

  ui->file_info->setText(
      "filename: " + filename + "\nfilepath: " + filepath +
      "/\n\nfilesize: " + filesize + " kb\n\nvertices count: " + v_count +
      "\nedges count: " + e_count + "\nfacets count: " + f_count);
}

int MainWindow::edgesCounting(geometry_info* pobject) {
  int edges_count = 0;
  for (int i = 0; i < pobject->facets_count; i++) {
    edges_count += pobject->facets->facet_vertices_count;
  }
  return edges_count;
}

////////////////////////////////////////////////////////////////////////////
// TABS SHOWING PUSHBUTTONS
void MainWindow::showTab() {
  QPushButton* button = (QPushButton*)sender();

  bool checked = button->isChecked();
  ui->pushButton_transformations->setChecked(false);
  ui->pushButton_capture->setChecked(false);
  ui->pushButton_view_settings->setChecked(false);
  ui->pushButton_info->setChecked(false);
  button->setChecked(checked);

  QString current_tab_msg = "";
  if (checked == true) {
    int tab_id = 0;
    current_tab_msg = "Model transformations";
    if (button->objectName() == "pushButton_capture") {
      tab_id = 1;
      current_tab_msg = "Model capture";
    } else if (button->objectName() == "pushButton_view_settings") {
      tab_id = 2;
      current_tab_msg = "Viewport settings";
    } else if (button->objectName() == "pushButton_info") {
      tab_id = 3;
      current_tab_msg = "Model info";
    }
    ui->tabsWidget->setHidden(false);
    ui->tabsWidget->setCurrentIndex(tab_id);
  } else {
    ui->tabsWidget->setHidden(true);
  }
  ui->statusbar->showMessage(current_tab_msg);
}

////////////////////////////////////////////////////////////////////////////
// VIEW SETTINGS
void MainWindow::on_checkBox_vertices_visibility_stateChanged(int arg1) {
  ui->radioButton_square_vertices->setEnabled(arg1);
  ui->radioButton_circle_vertices->setEnabled(arg1);
  ui->spinBox_vertex_size->setEnabled(arg1);
  ui->pushButton_vertices_color->setEnabled(arg1);

  ui->openGLWidget->vertices_visibility = arg1;  // 0 or 2
  ui->openGLWidget->update();
}

void MainWindow::on_checkBox_edges_visibility_stateChanged(int arg1) {
  ui->radioButton_dashed_edges->setEnabled(arg1);
  ui->radioButton_solid_edges->setEnabled(arg1);
  ui->spinBox_edges_thickness->setEnabled(arg1);
  ui->pushButton_edges_color->setEnabled(arg1);

  ui->openGLWidget->edges_visibility = arg1;  // 0 or 2
  ui->openGLWidget->update();
}

void MainWindow::getColor() {
  QPushButton* button = (QPushButton*)sender();

  QColor* color = nullptr;

  if (button->objectName() == "pushButton_vertices_color") {
    color = &ui->openGLWidget->vertices_color;
  } else if (button->objectName() == "pushButton_edges_color") {
    color = &ui->openGLWidget->edges_color;
  } else {
    color = &ui->openGLWidget->background_color;
  }

  *color = QColorDialog::getColor(*color, this, "Choose Color");
  QString color_name = color->name(QColor::HexArgb);
  button->setStyleSheet("background-color: " + color_name +
                        "; border: 2px solid white;");

  ui->openGLWidget->update();
}

////////////////////////////////////////////////////////////////////////////
// AFFINE TRANSFORMATIONS
void MainWindow::on_doubleSpinBox_Tx_valueChanged(double arg1) {
  for (int i = 0; i < object.vertices_count; i++) {
    ui->openGLWidget->object.vertices[i].x += arg1 - last_tx;
  }
  last_tx = arg1;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_solid_edges_clicked() {
  ui->openGLWidget->edges_type = 1;
  //  ui->openGLWidget->update();
}
