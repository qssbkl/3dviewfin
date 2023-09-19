#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include "s21_3dviewer.h"
#include "s21_matrix.h"
#include "s21_parser.h"



// Расширяем класс QGraphicsView
class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = 0);
    ~MyGraphicView();

signals:

private slots:


private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_3;   // Объявляем группу элементов
    QGraphicsItemGroup  *group_2;
    QGraphicsItemGroup  *group_1;

    /* Таймер для задержки отрисовки.
     * Дело в том, что при создании окна и виджета
     * необходимо некоторое время, чтобы родительский слой
     * развернулся, чтобы принимать от него адекватные параметры
     * ширины и высоты
     * */
    QTimer              *timer;
    QTimer              *timer_2;

private:

    /* Метод для удаления всех элементов
     * из группы элементов
     * */
    void deleteItemsFromGroup(QGraphicsItemGroup *group);
    void draw_figure(void);
    void saveImgFile(char *str_file_name);
    void read_start_pos(void);
    void save_start_pos(void);

public slots:
    void get_file_name(char str[]);
    void stop_drawing_signal(int signal);
    void next_drawing_signal(int signal);
    void get_multip(double multip_in);
    void get_move_x(double move_x_in);
    void get_move_y(double move_y_in);
    void get_move_z(double move_z_in);
    void get_rotate_x(double rotate_x_in);
    void get_rotate_y(double rotate_y_in);
    void get_rotate_z(double rotate_z_in);
    void get_view_angle(double view_angle_in);
    void get_save_jpg_file(char str[]);
    void get_save_bmp_file(char str[]);
    void get_dash_line_signal(int signal);
    void get_line_width(int width);
    void get_facet_type(int type);
    void get_facet_size(int size);
    void get_multip_speed(int multip_speed_in);
    void get_move_x_speed(int move_x_speed_in);
    void get_move_y_speed(int move_y_speed_in);
    void get_move_z_speed(int move_z_speed_in);
    void get_rotate_x_speed(int rotate_x_speed_in);
    void get_rotate_y_speed(int rotate_y_speed_in);
    void get_rotate_z_speed(int rotate_z_speed_in);
    void get_view_angle_speed(int view_angle_speed_in);
    void get_red_color(int red_color_in);
    void get_green_color(int green_color_in);
    void get_blue_color(int blue_color_in);
    void get_perspect_status(int perspect_status_in);
    void get_zero_signal(int signal);
    void get_red_line_color(int red_color_in);
    void get_green_line_color(int green_color_in);
    void get_blue_line_color(int blue_color_in);
    void get_red_vertex_color(int red_color_in);
    void get_green_vertex_color(int green_color_in);
    void get_blue_vertex_color(int blue_color_in);
    void get_main_window_size_changed(int size_changed);

signals:
    void send_vertexes_amount(int);
    void send_facets_amount(int);
};



#endif // MYGRAPHICVIEW_H
