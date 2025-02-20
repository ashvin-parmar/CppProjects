#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<drawingmanager.h>
#include<QPushButton>
#include<QMouseEvent>
#include<QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeAllFrame();
    void brushStyleInitialization();
    void frameSetTabOrderInitialization();
    void PhaseII();
    void PhaseIII();

private slots:
    void on_drawLine_clicked();

    void on_lineMenu_clicked();

    void on_cancelLine_clicked();

    void on_drawText_clicked();

    void on_cancelText_clicked();

    void on_textMenu_clicked();

    void on_cancelPoint_clicked();

    void on_drawPoint_clicked();

    void on_pointMenu_clicked();

    void on_polylineMenu_clicked();

    void on_addPointPolyline_clicked();

    void on_drawPolyline_clicked();

    void on_cancelPolyline_clicked();

    void on_addPointPolygon_clicked();

    void on_cancelPolygon_clicked();

    void on_drawPolygon_clicked();

    void on_polygonMenu_clicked();

    void on_arcMenu_clicked();

    void on_cancelArc_clicked();

    void on_drawArc_clicked();

    void on_ellipseIsCenter_stateChanged(int arg1);

    void on_ellipseMenu_clicked();

    void on_drawEllipse_clicked();

    void on_cancelEllipse_clicked();

    void on_cancelRectangle_clicked();

    void on_drawRectangle_clicked();

    void on_rectangleMenu_clicked();

    void on_drawRoundedRectangle_clicked();

    void on_cancelRoundedRectangle_clicked();

    void on_roundedRectangleMenu_clicked();

    void on_pixmapFilePathButton_clicked();

    void on_drawPixmap_clicked();

    void on_cancelPixmap_clicked();

    void on_pixmapMenu_clicked();

    void on_pixmapFilePath_textChanged(const QString &arg1);

    void on_loginButton_clicked();

    void on_homeMenu_clicked();

    void on_username_textChanged(const QString &arg1);

    void on_exit_triggered();

    void on_actionList_View_triggered();

    void on_listWidgetClose_clicked();

    void on_actionList_View_changed();

    void on_actionTree_View_triggered();

    void on_actionTree_View_changed();

    void on_treeWidgetClose_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DrawingManager *drawingManager;
    bool frameOpened;
    QPushButton *exitFullScreenButton;
};
#endif // MAINWINDOW_H
