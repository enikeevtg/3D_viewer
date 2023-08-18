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

  connect(ui->checkBox_vertices_visibility, SIGNAL(stateChanged(int)), this,
          SLOT(visabilitySetting(int)));
  connect(ui->checkBox_edges_visibility, SIGNAL(stateChanged(int)), this,
          SLOT(visabilitySetting(int)));

  connect(ui->radioButton_solid_edges, SIGNAL(clicked()), this,
          SLOT(typeSelect()));
  connect(ui->radioButton_dashed_edges, SIGNAL(clicked()), this,
          SLOT(typeSelect()));
  connect(ui->radioButton_circle_vertices, SIGNAL(clicked()), this,
          SLOT(typeSelect()));
  connect(ui->radioButton_square_vertices, SIGNAL(clicked()), this,
          SLOT(typeSelect()));

  connect(ui->spinBox_vertices_size, SIGNAL(valueChanged(int)), this,
          SLOT(sizeSetting(int)));
  connect(ui->spinBox_edges_thickness, SIGNAL(valueChanged(int)), this,
          SLOT(sizeSetting(int)));

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
// VIEW SETTINGS TAB
void MainWindow::visabilitySetting(int check) {
  if (check) check = VISIBLE;
  QCheckBox* check_box = (QCheckBox*)sender();

  if (check_box->text() == "Vertices") {
    ui->openGLWidget->vertices_visibility = check;
  } else if (check_box->text() == "Edges") {
    ui->openGLWidget->edges_visibility = check;
  }

  ui->openGLWidget->update();
}

void MainWindow::typeSelect() {
  QRadioButton* radio_button = (QRadioButton*)sender();

  if (radio_button->text() == "circle vertices") {
    ui->openGLWidget->vertices_type = CIRCLE_VERTICES;
  } else if (radio_button->text() == "square vertices") {
    ui->openGLWidget->vertices_type = SQUARE_VERTICES;
  } else if (radio_button->text() == "solid edges") {
    ui->openGLWidget->edges_type = SOLID_EDGES;
  } else if (radio_button->text() == "dashed edges") {
    ui->openGLWidget->edges_type = DASHED_EDGES;
  }

  ui->openGLWidget->update();
}

void MainWindow::sizeSetting(int size) {
  QSpinBox* spin_box = (QSpinBox*)sender();

  if (spin_box->objectName() == "spinBox_vertices_size") {
    ui->openGLWidget->vertices_size = size;
  } else if (spin_box->objectName() == "spinBox_edges_thickness") {
    ui->openGLWidget->edges_thickness = size;
  }

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
// TRANSFORMATIONS TAB
void MainWindow::on_doubleSpinBox_Tx_valueChanged(double arg1) {
  for (int i = 0; i < object.vertices_count; i++) {
    ui->openGLWidget->object.vertices[i].x += arg1 - last_tx;
  }
  last_tx = arg1;
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_solid_edges_clicked() {
  ui->openGLWidget->edges_type = SOLID_EDGES;
  ui->openGLWidget->update();
}
