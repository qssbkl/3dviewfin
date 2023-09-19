#include "mainwindow.h"
#include "ui_mainwindow.h"

QString str;
int temp_counter_1 = 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    myPicture = new MyGraphicView();
    ui->graphicLayout->addWidget(myPicture);

    connect(this, &MainWindow::send_file_name, myPicture, &MyGraphicView::get_file_name);
    connect(this, &MainWindow::send_next_signal, myPicture, &MyGraphicView::next_drawing_signal);
    connect(this, &MainWindow::send_stop_signal, myPicture, &MyGraphicView::stop_drawing_signal);
    connect(this, &MainWindow::send_multip, myPicture, &MyGraphicView::get_multip);
    connect(this, &MainWindow::send_move_x, myPicture, &MyGraphicView::get_move_x);
    connect(this, &MainWindow::send_move_y, myPicture, &MyGraphicView::get_move_y);
    connect(this, &MainWindow::send_move_z, myPicture, &MyGraphicView::get_move_z);
    connect(this, &MainWindow::send_rotate_x, myPicture, &MyGraphicView::get_rotate_x);
    connect(this, &MainWindow::send_rotate_y, myPicture, &MyGraphicView::get_rotate_y);
    connect(this, &MainWindow::send_rotate_z, myPicture, &MyGraphicView::get_rotate_z);
    connect(this, &MainWindow::send_view_angle, myPicture, &MyGraphicView::get_view_angle);
    connect(this, &MainWindow::send_save_jpg_file, myPicture, &MyGraphicView::get_save_jpg_file);
    connect(this, &MainWindow::send_save_bmp_file, myPicture, &MyGraphicView::get_save_bmp_file);
    connect(this, &MainWindow::send_dash_line_signal, myPicture, &MyGraphicView::get_dash_line_signal);
    connect(this, &MainWindow::send_line_width, myPicture, &MyGraphicView::get_line_width);
    connect(this, &MainWindow::send_facet_type, myPicture, &MyGraphicView::get_facet_type);
    connect(this, &MainWindow::send_facet_size, myPicture, &MyGraphicView::get_facet_size);
    connect(this, &MainWindow::send_multip_speed, myPicture, &MyGraphicView::get_multip_speed);
    connect(this, &MainWindow::send_move_x_speed, myPicture, &MyGraphicView::get_move_x_speed);
    connect(this, &MainWindow::send_move_y_speed, myPicture, &MyGraphicView::get_move_y_speed);
    connect(this, &MainWindow::send_move_z_speed, myPicture, &MyGraphicView::get_move_z_speed);
    connect(this, &MainWindow::send_rotate_x_speed, myPicture, &MyGraphicView::get_rotate_x_speed);
    connect(this, &MainWindow::send_rotate_y_speed, myPicture, &MyGraphicView::get_rotate_y_speed);
    connect(this, &MainWindow::send_rotate_z_speed, myPicture, &MyGraphicView::get_rotate_z_speed);
    connect(this, &MainWindow::send_view_angle_speed, myPicture, &MyGraphicView::get_view_angle_speed);
    connect(this, &MainWindow::send_red_color, myPicture, &MyGraphicView::get_red_color);
    connect(this, &MainWindow::send_green_color, myPicture, &MyGraphicView::get_green_color);
    connect(this, &MainWindow::send_blue_color, myPicture, &MyGraphicView::get_blue_color);
    connect(this, &MainWindow::send_perspect_status, myPicture, &MyGraphicView::get_perspect_status);
    connect(this, &MainWindow::send_zero_signal, myPicture, &MyGraphicView::get_zero_signal);
    connect(this, &MainWindow::send_red_line_color, myPicture, &MyGraphicView::get_red_line_color);
    connect(this, &MainWindow::send_green_line_color, myPicture, &MyGraphicView::get_green_line_color);
    connect(this, &MainWindow::send_blue_line_color, myPicture, &MyGraphicView::get_blue_line_color);
    connect(this, &MainWindow::send_red_vertex_color, myPicture, &MyGraphicView::get_red_vertex_color);
    connect(this, &MainWindow::send_green_vertex_color, myPicture, &MyGraphicView::get_green_vertex_color);
    connect(this, &MainWindow::send_blue_vertex_color, myPicture, &MyGraphicView::get_blue_vertex_color);

    connect(myPicture, &MyGraphicView::send_vertexes_amount, this, &MainWindow::get_vertexes_amount);
    connect(myPicture, &MyGraphicView::send_facets_amount, this, &MainWindow::get_facets_amount);

    read_start_pos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_start_pos() {
    FILE *start_pos;
    double move_x_0 = 0, move_y_0 = 0, move_z_0 = 0, rotate_x_0 = 0, rotate_y_0 = 0, rotate_z_0 = 0, multip_0 = 1;
    int red_color_0 = 50, green_color_0 = 50, blue_color_0 = 50, perspective_0 = 1, facet_type_0 = 0, facet_size_0 = 0;
    int red_line_color_0 = 50, green_line_color_0 = 180,blue_line_color_0 = 160, line_type_0 = 0, line_width_0 = 1;
    int red_vertex_color_0 = 50, green_vertex_color_0 = 180,blue_vertex_color_0 = 160, error = 0;
    if ((start_pos = fopen("start_pos.pos", "r")) == NULL) {
        start_pos = fopen("start_pos.pos", "w");
        fprintf(start_pos, "%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
        fprintf(start_pos, "%d %d %d %d %d %d ", 50, 50, 50, 1, 0, 1);
        fprintf(start_pos, "%d %d %d %d %d", 50, 180, 160, 0, 1);
        fprintf(start_pos, "%d %d %d", 50, 180, 160);
    } else {
        char move_x_str[20] = {0}, move_y_str[20] = {0}, move_z_str[20] = {0};
        char rotate_x_str[20] = {0}, rotate_y_str[20] = {0}, rotate_z_str[20] = {0}, multip_str[20] = {0};
        error += fscanf(start_pos, "%s%s%s%s%s%s%s", move_x_str, move_y_str, move_z_str, rotate_x_str, rotate_y_str, rotate_z_str, multip_str);
        error += fscanf(start_pos, "%d%d%d%d%d%d", &red_color_0, &green_color_0, &blue_color_0, &perspective_0, &facet_type_0, &facet_size_0);
        error += fscanf(start_pos, "%d%d%d%d%d", &red_line_color_0, &green_line_color_0, &blue_line_color_0, &line_type_0, &line_width_0);
        error += fscanf(start_pos, "%d%d%d", &red_vertex_color_0, &green_vertex_color_0, &blue_vertex_color_0);
        move_x_0 = convert_str_to_double(move_x_str, strlen(move_x_str));
        move_y_0 = convert_str_to_double(move_y_str, strlen(move_y_str));
        move_z_0 = convert_str_to_double(move_z_str, strlen(move_z_str));
        rotate_x_0 = convert_str_to_double(rotate_x_str, strlen(rotate_x_str));
        rotate_y_0 = convert_str_to_double(rotate_y_str, strlen(rotate_y_str));
        rotate_z_0 = convert_str_to_double(rotate_z_str, strlen(rotate_z_str));
        multip_0 = convert_str_to_double(multip_str, strlen(multip_str));
        if (multip_0 < 0.01) multip_0 = 0.01;
    }
    fclose(start_pos);
    ui->VS_X_pos->setValue((int)move_x_0); ui->VS_X_pos->setSliderPosition((int)move_x_0); ui->VS_X_pos->repaint();
    ui->VS_Y_pos->setValue((int)move_y_0); ui->VS_Y_pos->setSliderPosition((int)move_y_0); ui->VS_Y_pos->repaint();
    ui->VS_Z_pos->setValue((int)move_z_0); ui->VS_Z_pos->setSliderPosition((int)move_z_0); ui->VS_Z_pos->repaint();
    ui->VS_X_rot->setValue((int)rotate_x_0); ui->VS_X_rot->setSliderPosition((int)rotate_x_0); ui->VS_X_rot->repaint();
    ui->VS_Y_rot->setValue((int)rotate_y_0); ui->VS_Y_rot->setSliderPosition((int)rotate_y_0); ui->VS_Y_rot->repaint();
    ui->VS_Z_rot->setValue((int)rotate_z_0); ui->VS_Z_rot->setSliderPosition((int)rotate_z_0); ui->VS_Z_rot->repaint();
    int multip_int = (int)(multip_0 * 1000);
    ui->VS_Multip->setValue(multip_int); ui->VS_Multip->setSliderPosition(multip_int); ui->VS_Multip->repaint();
    ui->SBRedColor->setValue(red_color_0); ui->SBRedColor->repaint();
    ui->SBGreenColor->setValue(green_color_0); ui->SBGreenColor->repaint();
    ui->SBGreenColor_2->setValue(blue_color_0); ui->SBGreenColor_2->repaint();
    if (perspective_0 == 1) {
        ui->CBPerspective->setChecked(true);
    } else {
        ui->CBPerspective->setChecked(false);
    }
    ui->CBPerspective->repaint();
    ui->CBFacetType->setCurrentIndex(facet_type_0);ui->CBFacetType->repaint();
    ui->SBFacetSize->setValue(facet_size_0);ui->SBFacetSize->repaint();
    ui->SBRedColor_line->setValue(red_line_color_0); ui->SBRedColor_line->repaint();
    ui->SBGreenColor_line->setValue(green_line_color_0); ui->SBGreenColor_line->repaint();
    ui->SBBlueColor_line->setValue(blue_line_color_0); ui->SBBlueColor_line->repaint();
    ui->SBRedColor_vertex->setValue(red_vertex_color_0); ui->SBRedColor_vertex->repaint();
    ui->SBGreenColor_vertex->setValue(green_vertex_color_0); ui->SBGreenColor_vertex->repaint();
    ui->SBBlueColor_vertex->setValue(blue_vertex_color_0); ui->SBBlueColor_vertex->repaint();
    if (line_type_0 == 1) {
        ui->RBDashLine->setChecked(true);
    } else {
        ui->RBDashLine->setChecked(false);
    }
    ui->RBDashLine->repaint();
    ui->SBLineWidth->setValue(line_width_0); ui->SBLineWidth->repaint();
    MainWindow::on_VS_Multip_sliderMoved(multip_int);
    MainWindow::on_VS_X_pos_sliderMoved((int)move_x_0);
    MainWindow::on_VS_Y_pos_sliderMoved((int)move_y_0);
    MainWindow::on_VS_Z_pos_sliderMoved((int)move_z_0);
    MainWindow::on_VS_X_rot_sliderMoved((int)rotate_x_0);
    MainWindow::on_VS_Y_rot_sliderMoved((int)rotate_y_0);
    MainWindow::on_VS_Z_rot_sliderMoved((int)rotate_z_0);
    MainWindow::on_SBRedColor_valueChanged(red_color_0);
    MainWindow::on_SBGreenColor_valueChanged(green_color_0);
    MainWindow::on_SBGreenColor_2_valueChanged(blue_color_0);
    if (perspective_0 == 1) {
        MainWindow::on_CBPerspective_toggled(true);
    } else {
        MainWindow::on_CBPerspective_toggled(false);
    }
    if (facet_type_0 == 0) {
        MainWindow::on_CBFacetType_currentTextChanged("none");
    } else if (facet_type_0 == 1) {
        MainWindow::on_CBFacetType_currentTextChanged("circle");
    } else if (facet_type_0 == 2) {
        MainWindow::on_CBFacetType_currentTextChanged("triangle");
    } else {
        MainWindow::on_CBFacetType_currentTextChanged("square");
    }
    MainWindow::on_SBRedColor_line_valueChanged(red_line_color_0);
    MainWindow::on_SBGreenColor_line_valueChanged(green_line_color_0);
    MainWindow::on_SBBlueColor_line_valueChanged(blue_line_color_0);
    MainWindow::on_SBRedColor_vertex_valueChanged(red_vertex_color_0);
    MainWindow::on_SBGreenColor_vertex_valueChanged(green_vertex_color_0);
    MainWindow::on_SBBlueColor_vertex_valueChanged(blue_vertex_color_0);
    if (line_type_0 == 1) {
        MainWindow::on_RBDashLine_toggled(true);
    } else {
        MainWindow::on_RBDashLine_toggled(false);
    }
    MainWindow::on_SBLineWidth_valueChanged(line_width_0);
    emit send_view_angle(0);
    if (error != 21) {
        error = 21;
    }
}

void MainWindow::get_vertexes_amount(int amount) {
    QString vertexes_amount_str = QString::number(amount, 'f', 0);
    ui->LBAmountOfVertexes->setText(vertexes_amount_str);
}

void MainWindow::get_facets_amount(int amount) {
    QString facets_amount_str = QString::number(amount, 'f', 0);
    ui->LBAmountOfFacets->setText(facets_amount_str);
}

void MainWindow::on_InputObject_clicked()
{
    QString str = QFileDialog::getOpenFileName(this, tr("Choose obj file"),
            QDir::currentPath(),tr("OBJ Image (*.obj);; All Files (*.*);; JPEG Image (*.jpg)"));
    QFileInfo fileinfo(str);
    QString str_1 = fileinfo.fileName();
    ui->ObjFileName->setText(str_1);
    QString str_2 = fileinfo.filePath();
    ui->ObjFilePath->setText(str_2);
}

void MainWindow::on_PBDraw_clicked()
{
    emit send_stop_signal(1);
    temp_counter_1 = 1;
    char path[255] = "";
    if (ui->ObjFilePath->text() != "home directory") {
         QByteArray bytes_2 = ui->ObjFilePath->text().toLocal8Bit();
         strcpy(path, bytes_2.data());
          emit send_file_name(path);
    }
}

void MainWindow::on_PBStop_clicked()
{
    emit send_stop_signal(1);

}

void MainWindow::on_PBNext_clicked()
{
        emit send_next_signal(temp_counter_1);
        temp_counter_1 += 1;
}

void MainWindow::on_VS_Multip_sliderMoved(int position)
{
    double multip_1 = ((double)position) / 1000;
    ui->DSB_Multip->setValue(multip_1);
    emit send_multip(multip_1);
}



void MainWindow::on_VS_Z_rot_sliderMoved(int position)
{
    double rotate_z_1 = (double)position;
    ui->SBZ_Rot->setValue(position);
    emit send_rotate_z(rotate_z_1);
}

void MainWindow::on_VS_Y_rot_sliderMoved(int position)
{
    double rotate_y_1 = (double)position;
    ui->SBY_Rot->setValue(position);
    emit send_rotate_y(rotate_y_1);
}

void MainWindow::on_VS_X_rot_sliderMoved(int position)
{
    double rotate_x_1 = (double)position;
    ui->SBX_Rot->setValue(position);
    emit send_rotate_x(rotate_x_1);
}

void MainWindow::on_VS_Z_pos_sliderMoved(int position)
{
    double move_z_1 = (double)position;
    ui->SBZ_Move->setValue(position);
    emit send_move_z(-move_z_1);
}


void MainWindow::on_VS_Y_pos_sliderMoved(int position)
{
    double move_y_1 = (double)position;
    ui->SBY_Move->setValue(position);
    emit send_move_y(move_y_1);
}

void MainWindow::on_VS_X_pos_sliderMoved(int position)
{
    double move_x_1 = (double)position;
    ui->SBX_Move->setValue(position);
    emit send_move_x(move_x_1);
}

void MainWindow::on_VS_view_angle_sliderMoved(int position)
{
    double view_angle_1 = (double)position;
    ui->SBView_Angle->setValue(position);
    emit send_view_angle(view_angle_1);
}

void MainWindow::on_PBJpgPhoto_clicked()
{
    emit send_stop_signal(1);
    temp_counter_1 = 1;
    char path[255] = "";
    if (ui->ObjFilePath->text() != "home directory") {
         QByteArray bytes_2 = ui->ObjFilePath->text().toLocal8Bit();
         strcpy(path, bytes_2.data());
    } else {
        QByteArray bytes = ui->ObjFileName->text().toLocal8Bit();
        strcpy(path, bytes.data());
    }
    emit send_save_jpg_file(path);
}

void MainWindow::on_PBBmpPhoto_clicked()
{
    emit send_stop_signal(1);
    temp_counter_1 = 1;
    char path[255] = "";
    if (ui->ObjFilePath->text() != "home directory") {
         QByteArray bytes_2 = ui->ObjFilePath->text().toLocal8Bit();
         strcpy(path, bytes_2.data());
    } else {
        QByteArray bytes = ui->ObjFileName->text().toLocal8Bit();
        strcpy(path, bytes.data());
    }
    emit send_save_bmp_file(path);
}

void MainWindow::on_PBToZero_clicked()
{
    FILE *start_pos;
    start_pos = fopen("start_pos.pos", "w");
    fprintf(start_pos, "%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    fclose(start_pos);
    MainWindow::read_start_pos();
    emit send_zero_signal(1);
}


void MainWindow::on_SBLineWidth_valueChanged(int arg1)
{
    emit send_line_width(arg1);
}

void MainWindow::on_RBDashLine_toggled(bool checked)
{
    if (checked) {
        emit send_dash_line_signal(1);
    } else {
        emit send_dash_line_signal(0);
    }
}

void MainWindow::on_SBFacetSize_valueChanged(int arg1)
{
    emit send_facet_size(arg1);
}

void MainWindow::on_CBFacetType_currentTextChanged(const QString &arg1)
{
    if (arg1 == "none") {
        emit send_facet_type(0);
    } else if (arg1 == "circle") {
        emit send_facet_type(1);
    } else if (arg1 == "triangle") {
        emit send_facet_type(2);
    } else {
        emit send_facet_type(3);
    }
}

void MainWindow::on_SBViewAngleSpeed_valueChanged(int arg1)
{
    emit send_view_angle_speed(arg1);
}

void MainWindow::on_SBMultipSpeed_valueChanged(int arg1)
{
    emit send_multip_speed(arg1);
}

void MainWindow::on_SBRotZSpeed_valueChanged(int arg1)
{
    emit send_rotate_z_speed(arg1);
}

void MainWindow::on_SBRotYSpeed_valueChanged(int arg1)
{
    emit send_rotate_y_speed(arg1);
}

void MainWindow::on_SBRotXSpeed_valueChanged(int arg1)
{
    emit send_rotate_x_speed(arg1);
}

void MainWindow::on_SBMoveZSpeed_valueChanged(int arg1)
{
    emit send_move_z_speed(-arg1);
}

void MainWindow::on_SBMoveYSpeed_valueChanged(int arg1)
{
    emit send_move_y_speed(arg1);
}

void MainWindow::on_SBMoveXSpeed_valueChanged(int arg1)
{
    emit send_move_x_speed(arg1);
}

void MainWindow::on_SBRedColor_valueChanged(int arg1)
{
    emit send_red_color(arg1);
}

void MainWindow::on_SBGreenColor_valueChanged(int arg1)
{
    emit send_green_color(arg1);
}

void MainWindow::on_SBGreenColor_2_valueChanged(int arg1)
{
    emit send_blue_color(arg1);
}

void MainWindow::on_CBPerspective_toggled(bool checked)
{
    if (checked) {
        emit send_perspect_status(1);
    } else {
        emit send_perspect_status(0);
    }
}

void MainWindow::on_SBRedColor_line_valueChanged(int arg1)
{
    emit send_red_line_color(arg1);
}

void MainWindow::on_SBGreenColor_line_valueChanged(int arg1)
{
    emit send_green_line_color(arg1);
}

void MainWindow::on_SBBlueColor_line_valueChanged(int arg1)
{
    emit send_blue_line_color(arg1);
}

void MainWindow::on_SBX_Move_valueChanged(int arg1)
{
    ui->VS_X_pos->setValue(arg1); ui->VS_X_pos->setSliderPosition(arg1); ui->VS_X_pos->repaint();
    MainWindow::on_VS_X_pos_sliderMoved(arg1);
}

void MainWindow::on_SBY_Move_valueChanged(int arg1)
{
    ui->VS_Y_pos->setValue(arg1); ui->VS_Y_pos->setSliderPosition(arg1); ui->VS_Y_pos->repaint();
    MainWindow::on_VS_Y_pos_sliderMoved(arg1);
}

void MainWindow::on_SBZ_Move_valueChanged(int arg1)
{
    ui->VS_Z_pos->setValue(arg1); ui->VS_Z_pos->setSliderPosition(arg1); ui->VS_Z_pos->repaint();
    MainWindow::on_VS_Z_pos_sliderMoved(arg1);
}

void MainWindow::on_SBX_Rot_valueChanged(int arg1)
{
    ui->VS_X_rot->setValue(arg1); ui->VS_X_rot->setSliderPosition(arg1); ui->VS_X_rot->repaint();
    MainWindow::on_VS_X_rot_sliderMoved(arg1);
}

void MainWindow::on_SBY_Rot_valueChanged(int arg1)
{
    ui->VS_Y_rot->setValue(arg1); ui->VS_Y_rot->setSliderPosition(arg1); ui->VS_Y_rot->repaint();
    MainWindow::on_VS_Y_rot_sliderMoved(arg1);
}

void MainWindow::on_SBZ_Rot_valueChanged(int arg1)
{
    ui->VS_Z_rot->setValue(arg1); ui->VS_Z_rot->setSliderPosition(arg1); ui->VS_Z_rot->repaint();
    MainWindow::on_VS_Z_rot_sliderMoved(arg1);
}

void MainWindow::on_DSB_Multip_valueChanged(double arg1)
{
    int multip_int = (int)(arg1 * 1000);
    ui->VS_Multip->setValue(multip_int); ui->VS_Multip->setSliderPosition(multip_int); ui->VS_Multip->repaint();
    MainWindow::on_VS_Multip_sliderMoved(multip_int);
}

void MainWindow::on_SBView_Angle_valueChanged(int arg1)
{
    ui->VS_view_angle->setValue(arg1); ui->VS_view_angle->setSliderPosition(arg1); ui->VS_view_angle->repaint();
    MainWindow::on_VS_view_angle_sliderMoved(arg1);
}

void MainWindow::on_SBRedColor_vertex_valueChanged(int arg1)
{
    emit send_red_vertex_color(arg1);
}

void MainWindow::on_SBGreenColor_vertex_valueChanged(int arg1)
{
    emit send_green_vertex_color(arg1);
}

void MainWindow::on_SBBlueColor_vertex_valueChanged(int arg1)
{
    emit send_blue_vertex_color(arg1);
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
        if (iconSize.width() > 100) emit send_main_window_size_changed(1);
}
