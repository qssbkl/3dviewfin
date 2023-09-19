#include "mygraphicview.h"
#include <time.h>
#include <unistd.h>
#include "gif.h"

int temp_counter = 0, img_counter = 0, line_type = 0, line_width = 1, facet_type = 0, facet_size = 1, red_color = 50, green_color = 50, blue_color = 50;
int multip_flag = 1, temp_counter_2 = 0, perspect_flag = 1, red_line_color = 50, green_line_color = 180, blue_line_color = 160;
int red_vertex_color = 50, green_vertex_color = 180, blue_vertex_color = 160;
figure_t figure_1;
double x_max, x_min, y_max, y_min, z_max, z_min, size_coeff;
double move_x = 0.0, move_y = 0.0, move_z = 0.0, rotate_x = 0.0, rotate_y = 0.0, rotate_z = 0.0, multip = 1.0, view_angle = 0;
double move_x_speed = 0, move_y_speed = 0, move_z_speed = 0, rotate_x_speed = 0, rotate_y_speed = 0, rotate_z_speed = 1, multip_speed = 0, view_angle_speed = 1;
char str_file_name[255] = "cube-2.obj";
GifWriter gif_writer;

MyGraphicView::MyGraphicView(QWidget *parent)
    : QGraphicsView(parent)
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    scene = new QGraphicsScene();
    this->setScene(scene);
    group_1 = new QGraphicsItemGroup();
    group_2 = new QGraphicsItemGroup();
    group_3 = new QGraphicsItemGroup();

    scene->addItem(group_3);
    scene->addItem(group_2);
    scene->addItem(group_1);
    timer_2 = new QTimer(this);


    creat_cube(&figure_1);

    emit send_facets_amount(figure_1.triangles_number);
    emit send_vertexes_amount(figure_1.dots_number);
}

MyGraphicView::~MyGraphicView()
{
    save_start_pos();
    remove_figure(&figure_1);
    this->deleteItemsFromGroup(group_1);
    this->deleteItemsFromGroup(group_2);
    this->deleteItemsFromGroup(group_3);
}

void MyGraphicView::save_start_pos() {

    FILE *start_pos;
    start_pos = fopen("start_pos.pos", "w");
    fprintf(start_pos, "%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf ", move_x, move_y, move_z, rotate_x, rotate_y, rotate_z, multip);
    fprintf(start_pos, "%d %d %d %d %d %d ", red_color, green_color, blue_color, perspect_flag, facet_type, facet_size);
    fprintf(start_pos, "%d %d %d %d %d ", red_line_color, green_line_color, blue_line_color, line_type, line_width);
    fprintf(start_pos, "%d %d %d", red_vertex_color, green_vertex_color, blue_vertex_color);
    fclose(start_pos);
}


void MyGraphicView::read_start_pos() {
    FILE *start_pos;
    if ((start_pos = fopen("start_pos.pos", "r")) == NULL) {
        start_pos = fopen("start_pos.pos", "w");
        fprintf(start_pos, "%.2lf %.2lf %.2lf %.2lf %.2lf %.2lf %.2lf", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    } else {
        char move_x_str[20], move_y_str[20], move_z_str[20], rotate_x_str[20], rotate_y_str[20], rotate_z_str[20], multip_str[20];
        int error = fscanf(start_pos, "%s%s%s%s%s%s%s", move_x_str, move_y_str, move_z_str, rotate_x_str, rotate_y_str, rotate_z_str, multip_str);
        move_x = convert_str_to_double(move_x_str, strlen(move_x_str));
        move_y = convert_str_to_double(move_y_str, strlen(move_y_str));
        move_z = convert_str_to_double(move_z_str, strlen(move_z_str));
        rotate_x = convert_str_to_double(rotate_x_str, strlen(rotate_x_str));
        rotate_y = convert_str_to_double(rotate_y_str, strlen(rotate_y_str));
        rotate_z = convert_str_to_double(rotate_z_str, strlen(rotate_z_str));
        multip = convert_str_to_double(multip_str, strlen(multip_str));
        if (multip < 0.001) multip = 0.001;
        if (error == 0) error = 1;
    }
}

void MyGraphicView::stop_drawing_signal(int signal) {
    if (signal) {
        if (timer_2 != NULL) {
            disconnect(timer_2, &QTimer::timeout, this, &MyGraphicView::draw_figure);
        }
        temp_counter_2 = 0;
        img_counter = 0;
    }
}

void MyGraphicView::get_file_name(char *str) {
    int lenth = strlen(str);
    for (int i = 0; i < 255; i++) str_file_name[i] = '\0';
    for (int i = 0; i < lenth; i++) {
        str_file_name[i] = str[i];
    }
    str_file_name[lenth] = '\0';
    temp_counter = -1;
    remove_figure(&figure_1);
    if (strlen(str) != 0) {
        read_data_from_file(str_file_name, &figure_1);
    } else {
        creat_cube(&figure_1);
    }
    x_max = figure_1.dots[0][0];
    x_min = figure_1.dots[0][0];
    y_max = figure_1.dots[0][1];
    y_min = figure_1.dots[0][1];
    z_max = figure_1.dots[0][2];
    z_min = figure_1.dots[0][2];
    for (int i = 1; i < figure_1.dots_number; i++) {
        if (figure_1.dots[i][0] > x_max) x_max = figure_1.dots[i][0];
        if (figure_1.dots[i][0] < x_min) x_min = figure_1.dots[i][0];
        if (figure_1.dots[i][1] > y_max) y_max = figure_1.dots[i][1];
        if (figure_1.dots[i][1] < y_min) y_min = figure_1.dots[i][1];
        if (figure_1.dots[i][2] > z_max) z_max = figure_1.dots[i][2];
        if (figure_1.dots[i][2] < z_min) z_min = figure_1.dots[i][2];
    }
    double max_size = x_max - x_min;
    double y_size = y_max - y_min;
    if (max_size < y_size) max_size = y_size;
    double z_size = z_max - z_min;
    if (max_size < z_size) max_size = z_size;
    size_coeff = 500/max_size;
    move_figure(&figure_1, -1 * (x_min + (x_max - x_min) / 2), -1 * (y_min + (y_max - y_min) / 2), -1 * (z_min + (z_max - z_min) / 2));
    resize_figure(&figure_1, size_coeff, size_coeff, size_coeff);
    emit send_facets_amount(figure_1.triangles_number);
    emit send_vertexes_amount(figure_1.dots_number);
      draw_figure();
}

void MyGraphicView::next_drawing_signal(int signal) {
    if (signal != 0) {
        timer_2->setInterval(40);
        temp_counter_2 = 0;
        connect(timer_2, &QTimer::timeout, this, &MyGraphicView::draw_figure);
        timer_2->start(40);
        img_counter = 50;
    }
}

void MyGraphicView::get_multip(double multip_in) {
    multip = multip_in;
    draw_figure();
}

void MyGraphicView::get_move_x(double move_x_in) {
    move_x = move_x_in;
    draw_figure();
}

void MyGraphicView::get_move_y(double move_y_in) {
    move_y = move_y_in;
    draw_figure();
}

void MyGraphicView::get_move_z(double move_z_in) {
    move_z = move_z_in;
    draw_figure();
}

void MyGraphicView::get_rotate_x(double rotate_x_in) {
    rotate_x = rotate_x_in;
    draw_figure();
}

void MyGraphicView::get_rotate_y(double rotate_y_in) {
    rotate_y = rotate_y_in;
    draw_figure();
}

void MyGraphicView::get_rotate_z(double rotate_z_in) {
    rotate_z = rotate_z_in;
    draw_figure();
}

void MyGraphicView::get_view_angle(double view_angle_in) {
    view_angle = view_angle_in;
    draw_figure();
}

void MyGraphicView::get_dash_line_signal(int signal) {
    if (signal == 1) {
        line_type = 1;
    } else {
        line_type = 0;
    }
    draw_figure();
}

void MyGraphicView::get_line_width(int width) {
    line_width = width;
    draw_figure();
}

void MyGraphicView::get_facet_type(int type) {
    facet_type = type;
    draw_figure();
}

void MyGraphicView::get_facet_size(int size) {
    facet_size = size;
    draw_figure();
}

void MyGraphicView::get_move_x_speed(int move_x_speed_in) {
    move_x_speed = (double)move_x_speed_in;
}

void MyGraphicView::get_move_y_speed(int move_y_speed_in) {
    move_y_speed = (double)move_y_speed_in;
}

void MyGraphicView::get_move_z_speed(int move_z_speed_in) {
    move_z_speed = (double)move_z_speed_in;
}

void MyGraphicView::get_rotate_x_speed(int rotate_x_speed_in) {
    rotate_x_speed = (double)rotate_x_speed_in;
}

void MyGraphicView::get_rotate_y_speed(int rotate_y_speed_in) {
    rotate_y_speed = (double)rotate_y_speed_in;
}

void MyGraphicView::get_rotate_z_speed(int rotate_z_speed_in) {
    rotate_z_speed = (double)rotate_z_speed_in;
}

void MyGraphicView::get_multip_speed(int multip_speed_in) {
    multip_speed = (double)multip_speed_in/200;
}

void MyGraphicView::get_view_angle_speed(int view_angle_speed_in) {
    view_angle_speed = (double)view_angle_speed_in;
}

void MyGraphicView::get_red_color(int red_color_in) {
    red_color = red_color_in;
    draw_figure();
}

void MyGraphicView::get_green_color(int green_color_in) {
    green_color = green_color_in;
    draw_figure();
}

void MyGraphicView::get_blue_color(int blue_color_in) {
    blue_color = blue_color_in;
    draw_figure();
}

void MyGraphicView::get_perspect_status(int perspect_status_in) {
    perspect_flag = perspect_status_in;
    draw_figure();
}

void MyGraphicView::get_zero_signal(int signal) {
    if (signal == 1) temp_counter = -1;
    draw_figure();
}

void MyGraphicView::get_red_line_color(int red_color_in) {
    red_line_color = red_color_in;
    draw_figure();
}

void MyGraphicView::get_green_line_color(int green_color_in) {
    green_line_color = green_color_in;
    draw_figure();
}

void MyGraphicView::get_blue_line_color(int blue_color_in) {
    blue_line_color = blue_color_in;
    draw_figure();
}

void MyGraphicView::get_red_vertex_color(int red_color_in) {
    red_vertex_color = red_color_in;
    draw_figure();
}

void MyGraphicView::get_green_vertex_color(int green_color_in) {
    green_vertex_color = green_color_in;
    draw_figure();
}

void MyGraphicView::get_blue_vertex_color(int blue_color_in) {
    blue_vertex_color = blue_color_in;
    draw_figure();
}

void MyGraphicView::get_main_window_size_changed(int size_changed) {
    if (size_changed == 1) draw_figure();
}

void MyGraphicView::saveImgFile(char *str_file_name) {
    int lenth = strlen(str_file_name);
    char temp_str[255], final_temp_str[275], gif_temp_str[299];
    if (lenth == 0) {
        strncpy(temp_str, "temp_number", 12);
        temp_str[12] = '\0';
    } else {
        for (int i = 0; i < lenth -4; i++) {
            temp_str[i] = str_file_name[i];
        }
        temp_str[lenth - 4] = '\0';
    }
    temp_str[lenth - 4] = '\0';
    sprintf(final_temp_str, "%s%s", temp_str, "-temp.png");
    const time_t current_time = time(NULL);
       struct tm *current_year = NULL;
       char s1[40] = { 0 };
       current_year = localtime(&current_time);
       strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", current_year);

    sprintf(gif_temp_str, "%s-%s%s", temp_str, s1, ".gif");
    QString fileName = final_temp_str;
    this->grab().save(fileName);
    QImage image_1;
    image_1.load(fileName);
    QImage image = image_1.scaled(640, 480);
    int frame_delay = 20;
    if (img_counter != 0 && temp_counter_2 == 1) {
        GifBegin(&gif_writer, gif_temp_str, image.width(), image.height(), 100);
        GifWriteFrame(&gif_writer, image.convertToFormat(QImage::Format_RGBA8888).
                      convertToFormat(QImage::Format_RGBA8888).constBits(),
                      static_cast<uint32_t>(image.width()),
                      static_cast<uint32_t>(image.height()),
                      static_cast<uint32_t>(frame_delay));
    }
    if (img_counter != 0 && temp_counter_2 < img_counter) {
        GifWriteFrame(&gif_writer, image.convertToFormat(QImage::Format_RGBA8888).
                      convertToFormat(QImage::Format_RGBA8888).constBits(),
                      static_cast<uint32_t>(image.width()),
                      static_cast<uint32_t>(image.height()),
                      static_cast<uint32_t>(frame_delay));
    } else if (img_counter != 0 && temp_counter_2 == img_counter) {
        GifWriteFrame(&gif_writer, image.convertToFormat(QImage::Format_RGBA8888).
                      convertToFormat(QImage::Format_RGBA8888).constBits(),
                      static_cast<uint32_t>(image.width()),
                      static_cast<uint32_t>(image.height()),
                      static_cast<uint32_t>(frame_delay));
        GifEnd(&gif_writer);
    }

}

void MyGraphicView::get_save_jpg_file(char *str_file_name) {
    const time_t current_time = time(NULL);
       struct tm *current_year = NULL;
       char s1[40] = { 0 };
       current_year = localtime(&current_time);
       strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", current_year);
    int lenth = strlen(str_file_name);
    char temp_str[255], final_temp_str[300];
    if (lenth == 0) {
        strncpy(temp_str, "temp_number", 12);
        temp_str[12] = '\0';
    } else {
        for (int i = 0; i < lenth -4; i++) {
            temp_str[i] = str_file_name[i];
        }
        temp_str[lenth - 4] = '\0';
    }
    sprintf(final_temp_str, "%s%c%s%s", temp_str, '-', s1, ".jpg");
    QString fileName = final_temp_str;
    this->grab().save(fileName);
}

void MyGraphicView::get_save_bmp_file(char *str_file_name) {
    const time_t current_time = time(NULL);
       struct tm *current_year = NULL;
       char s1[40] = { 0 };
       current_year = localtime(&current_time);
       strftime(s1, 80, "%d.%m.%Y %H:%M:%S ", current_year);
    int lenth = strlen(str_file_name);
    char temp_str[255], final_temp_str[300];
    if (lenth == 0) {
        strncpy(temp_str, "temp_number", 12);
        temp_str[12] = '\0';
    } else {
        for (int i = 0; i < lenth -4; i++) {
            temp_str[i] = str_file_name[i];
        }
        temp_str[lenth - 4] = '\0';
    }
    sprintf(final_temp_str, "%s%c%s%s", temp_str, '-', s1, ".bmp");
    QString fileName = final_temp_str;
    this->grab().save(fileName);
}

void MyGraphicView::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}

void MyGraphicView::draw_figure()
{
    this->deleteItemsFromGroup(group_1);
    this->deleteItemsFromGroup(group_2);
    this->deleteItemsFromGroup(group_3);

    int width = this->width();
    int height = this->height();
    scene->setSceneRect(0,0,width,height);
    scene->setBackgroundBrush(QColor(red_color, green_color, blue_color, 255));

    QPen penBlack(Qt::black);
    QPen penRed(Qt::red);
    QPen penGreen(Qt::green);
    QPen penBlue(Qt::blue);
    penGreen.setWidth(3);
    penBlue.setWidth(3);

    int centerOfWidget_X = width/2;
    int centerOfWidget_Y = height/2;
    temp_counter += 1;
    temp_counter_2 += 1;

    figure_t figure;

    copy_figure(&figure, &figure_1);
    if (img_counter != 0) {
        int counter_3 = temp_counter % 200;
        if (counter_3 >= 100) {
            counter_3 = 200 - counter_3;
        }
        double temp_multip;
        temp_multip = multip + multip_speed * (double)(counter_3);
        multi_move(&figure, move_x + move_x_speed * (double)temp_counter/10,
                    move_y + move_y_speed * (double)temp_counter/10,
                    move_z + move_z_speed * (double)temp_counter/10,
                    temp_multip, temp_multip, temp_multip,
                    rotate_x + rotate_x_speed * (double)temp_counter,
                    rotate_y + rotate_y_speed * (double)temp_counter,
                    rotate_z + rotate_z_speed * (double)temp_counter,
                    0, 0, 0);
    } else {
        multi_move(&figure, move_x, move_y, move_z, multip, multip, multip, rotate_x, rotate_y, rotate_z, 0, 0, 0);
    }
    double view_vert_angle, temp_view_angle = view_angle;
    if (img_counter != 0) {
        double temp_angle = temp_view_angle + (double)(view_angle_speed * temp_counter*50)/720;
        while (temp_angle > 360) temp_angle -= 360;
        while (temp_angle < - 360) temp_angle += 360;
        if (temp_angle > 180) temp_angle = temp_angle - 360;
        if (temp_angle < - 180) temp_angle = 360 + temp_angle;
        temp_view_angle = temp_angle;
        view_vert_angle = temp_view_angle * 4;
    } else {
        view_vert_angle = temp_view_angle * 4;
    }

    if (perspect_flag == 1) {
        if (temp_view_angle >= 0 && temp_view_angle <= 90) {
            transform_figure(&figure, 0, - 1 + view_vert_angle / 360, - view_vert_angle / 360);
        } else if (temp_view_angle > 90 && temp_view_angle <= 180){
            transform_figure(&figure, 0, - 1 + view_vert_angle / 360, -2 + view_vert_angle / 360);
        } else if(temp_view_angle < 0 && temp_view_angle >= -90) {
            transform_figure(&figure, 0, - 1 - view_vert_angle / 360, - view_vert_angle / 360);
        } else if(temp_view_angle < -90 && temp_view_angle >= -180){
            transform_figure(&figure, 0, - 1 - view_vert_angle / 360, 2 + view_vert_angle / 360);
        }
    }

    rotate_figure(&figure, view_vert_angle / 4, 0, 0);
    for (int i = 0; i < figure.lines_number; i++) {
        int first = (int)figure.dots[figure.lines[i][0]][1];
        int second = (int)figure.dots[figure.lines[i][1]][1];
        int max = (first > second ? first: second);
        int min = (first <= second ? first: second);
        int middle = (max - min) / 2 + min;
        int colour = (middle + 255) / 3;
        if (colour > 255) {
            colour = 255;
        } else if (colour < 0) {
            colour = 0;
        }
        QPen penCurrent(QColor(red_line_color, green_line_color, blue_line_color, 255 - colour));
        const int scale = 5;
        if (line_type == 1) {
            penCurrent.setDashPattern({ 1.0 * scale, 1.0 * scale, 1.0 * scale, 1.0 * scale });
        }
        penCurrent.setWidth(line_width);
        if (i <= 1000000) {
        group_2->addToGroup(scene->addLine(centerOfWidget_X + (int)figure.dots[figure.lines[i][0]][0],
                            centerOfWidget_Y + (int)figure.dots[figure.lines[i][0]][2],
                            centerOfWidget_X + (int)figure.dots[figure.lines[i][1]][0],
                            centerOfWidget_Y + (int)figure.dots[figure.lines[i][1]][2],
                            penCurrent));
        } else {
        group_3->addToGroup(scene->addLine(centerOfWidget_X + (int)figure.dots[figure.lines[i][0]][0],
                            centerOfWidget_Y + (int)figure.dots[figure.lines[i][0]][2],
                            centerOfWidget_X + (int)figure.dots[figure.lines[i][1]][0],
                            centerOfWidget_Y + (int)figure.dots[figure.lines[i][1]][2],
                            penCurrent));
        }
    }
    if (facet_type != 0) {
        for (int i = 0; i < figure.dots_number; i++) {
            int colour = (255 + (int)figure.dots[i][1]) / 3;
            if (colour > 255) {
                colour = 255;
            } else if (colour < 0) {
                colour = 0;
            }
            QPen penCurrent_1(QColor(red_vertex_color, green_vertex_color, blue_vertex_color, 255 - colour));
            QBrush brush_1(QColor(red_vertex_color, green_vertex_color, blue_vertex_color, 255 - colour));

            int dot_width = 2 * facet_size, dot_hight = 2 * facet_size;
            if (facet_type == 1) {
                group_1->addToGroup(scene->addEllipse(centerOfWidget_X + (int)figure.dots[i][0] - dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] - dot_width / 2,
                        dot_width, dot_hight, penCurrent_1, brush_1));
            } else if (facet_type == 2) {
                QPolygonF polly;
                polly << QPointF(centerOfWidget_X + (int)figure.dots[i][0],
                        centerOfWidget_Y + (int)figure.dots[i][2] - dot_width / 2) <<
                        QPointF(centerOfWidget_X + (int)figure.dots[i][0] - dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] + dot_width / 2) <<
                        QPointF(centerOfWidget_X + (int)figure.dots[i][0] + dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] + dot_width / 2);
                group_1->addToGroup(scene->addPolygon(polly ,
                        penCurrent_1, brush_1));
            } else {
                QPolygonF polly;
                polly << QPointF(centerOfWidget_X + (int)figure.dots[i][0] - dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] - dot_width / 2) <<
                        QPointF(centerOfWidget_X + (int)figure.dots[i][0] - dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] + dot_width / 2) <<
                        QPointF(centerOfWidget_X + (int)figure.dots[i][0] + dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] + dot_width / 2) <<
                        QPointF(centerOfWidget_X + (int)figure.dots[i][0] + dot_width / 2,
                        centerOfWidget_Y + (int)figure.dots[i][2] - dot_width / 2);
                group_1->addToGroup(scene->addPolygon(polly ,
                        penCurrent_1, brush_1));
            }

        }
    }
    if (img_counter != 0) {
        if (temp_counter_2 <= img_counter) {
            saveImgFile(str_file_name);
        }
    }
    remove_figure(&figure);
}
