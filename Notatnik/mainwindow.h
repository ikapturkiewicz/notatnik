#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QColorDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isSaved;
    void setSaved(bool saved);

private slots:
    void on_actionNew_document_triggered();

    void on_buttonB_clicked(bool checked);

    void on_buttonU_clicked(bool checked);

    void on_buttonI_clicked(bool checked);

    void on_actionOpen_triggered();

    void on_spinBoxFontSize_valueChanged(int arg1);

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_textEdit_textChanged();

    void on_actionExit_triggered();

    void closeEvent(QCloseEvent *event);

    void updateLabels();

    void on_colorButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
