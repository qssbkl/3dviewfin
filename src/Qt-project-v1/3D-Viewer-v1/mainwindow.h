#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mygraphicview.h>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_InputObject_clicked();

    void on_PBDraw_clicked();

    void on_PBStop_clicked();

    void on_PBNext_clicked();

    void on_VS_Multip_sliderMoved(int position);

    void on_VS_Z_rot_sliderMoved(int position);

    void on_VS_Y_rot_sliderMoved(int position);

    void on_VS_X_rot_sliderMoved(int position);

    void on_VS_Z_pos_sliderMoved(int position);

    void on_VS_Y_pos_sliderMoved(int position);

    void on_VS_X_pos_sliderMoved(int position);

    void on_VS_view_angle_sliderMoved(int position);

    void on_PBJpgPhoto_clicked();

    void on_PBBmpPhoto_clicked();

    void on_PBToZero_clicked();

    void on_SBLineWidth_valueChanged(int arg1);

    void on_RBDashLine_toggled(bool checked);

    void on_SBFacetSize_valueChanged(int arg1);

    void on_CBFacetType_currentTextChanged(const QString &arg1);

    void on_SBViewAngleSpeed_valueChanged(int arg1);

    void on_SBMultipSpeed_valueChanged(int arg1);

    void on_SBRotZSpeed_valueChanged(int arg1);

    void on_SBRotYSpeed_valueChanged(int arg1);

    void on_SBRotXSpeed_valueChanged(int arg1);

    void on_SBMoveZSpeed_valueChanged(int arg1);

    void on_SBMoveYSpeed_valueChanged(int arg1);

    void on_SBMoveXSpeed_valueChanged(int arg1);

    void on_SBRedColor_valueChanged(int arg1);

    void on_SBGreenColor_valueChanged(int arg1);

    void on_SBGreenColor_2_valueChanged(int arg1);

    void on_CBPerspective_toggled(bool checked);

    void on_SBRedColor_line_valueChanged(int arg1);

    void on_SBGreenColor_line_valueChanged(int arg1);

    void on_SBBlueColor_line_valueChanged(int arg1);

    void on_SBX_Move_valueChanged(int arg1);

    void on_SBY_Move_valueChanged(int arg1);

    void on_SBZ_Move_valueChanged(int arg1);

    void on_SBX_Rot_valueChanged(int arg1);

    void on_SBY_Rot_valueChanged(int arg1);

    void on_SBZ_Rot_valueChanged(int arg1);

    void on_DSB_Multip_valueChanged(double arg1);

    void on_SBView_Angle_valueChanged(int arg1);

    void on_SBRedColor_vertex_valueChanged(int arg1);

    void on_SBGreenColor_vertex_valueChanged(int arg1);

    void on_SBBlueColor_vertex_valueChanged(int arg1);

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    Ui::MainWindow  *ui;
    MyGraphicView   *myPicture;     // Наш кастомный виджет
    void read_start_pos();

public slots:
    void get_vertexes_amount(int amount);
    void get_facets_amount(int amount);

signals:
    void send_file_name(char*);
    void send_stop_signal(int);
    void send_next_signal(int);
    void send_multip(double);
    void send_move_x(double);
    void send_move_y(double);
    void send_move_z(double);
    void send_rotate_x(double);
    void send_rotate_y(double);
    void send_rotate_z(double);
    void send_view_angle(double);
    void send_save_jpg_file(char*);
    void send_save_bmp_file(char*);
    void send_dash_line_signal(int);
    void send_line_width(int);
    void send_facet_type(int);
    void send_facet_size(int);
    void send_multip_speed(int);
    void send_move_x_speed(int);
    void send_move_y_speed(int);
    void send_move_z_speed(int);
    void send_rotate_x_speed(int);
    void send_rotate_y_speed(int);
    void send_rotate_z_speed(int);
    void send_view_angle_speed(int);
    void send_red_color(int);
    void send_green_color(int);
    void send_blue_color(int);
    void send_perspect_status(int);
    void send_zero_signal(int);
    void send_red_line_color(int);
    void send_green_line_color(int);
    void send_blue_line_color(int);
    void send_red_vertex_color(int);
    void send_green_vertex_color(int);
    void send_blue_vertex_color(int);
    void send_main_window_size_changed(int);
};

#endif // MAINWINDOW_H
