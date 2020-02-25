#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    ui->toolBar->addWidget(ui->fontComboBox);
    ui->toolBar->addWidget(ui->buttonB);
    ui->toolBar->addWidget(ui->buttonI);
    ui->toolBar->addWidget(ui->buttonU);
    ui->toolBar->addWidget(ui->spinBoxFontSize);
    ui->toolBar->addWidget(ui->colorButton);
    bool isSaved = false;
    connect(ui->textEdit,SIGNAL(textChanged()), this, SLOT(updateLabels()));
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(ui->charCounter);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(ui->wordCounter);
    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(ui->labelIsSaved);
    QIcon unchecked(":/images/icons/icons8-delete-document-50.png");
    QPixmap pixmap = unchecked.pixmap(30, 30);
    ui->labelIsSaved->setPixmap(pixmap);
    }


MainWindow::~MainWindow()
{
    delete ui;
}

size_t word_count(std::string s)
{
    return s.empty() ? 0 : std::count_if(std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))), std::unique(s.begin(), s.end()), std::ptr_fun<int, int>(std::isspace)) + !std::isspace(*s.rbegin());
}

void MainWindow::updateLabels() {
    QString text = ui->textEdit->toPlainText();
    int charactersCount = text.length();
    QString charactersCounterText = QStringLiteral("Characters: %1").arg(charactersCount);
    ui->charCounter->setText(charactersCounterText);

    int wordsCount = word_count(text.toStdString());
      QString wordsCounterText = QStringLiteral("Words: %1").arg(wordsCount);
      ui->wordCounter->setText(wordsCounterText);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(isSaved) {
        event->accept();
    } else {
        on_actionSave_triggered();
        event->accept();
    }
}

void MainWindow::setSaved(bool saved) {
    if(!saved) {
        this->isSaved = false;
        QIcon unchecked(":/images/icons/icons8-delete-document-50.png");
        QPixmap pixmap = unchecked.pixmap(30, 30);
        ui->labelIsSaved->setPixmap(pixmap);
    } else {
        this->isSaved = true;
        QIcon checked(":/images/icons/icons8-edit-property-50.png");
        QPixmap pixmap = checked.pixmap(30, 30);
        ui->labelIsSaved->setPixmap(pixmap);
    }
}

void MainWindow::on_spinBoxFontSize_valueChanged(int arg1)
{
    ui->textEdit->setFontPointSize(qreal(arg1));
    ui->textEdit->setFocus();
}


void MainWindow::on_buttonB_clicked(bool checked)
{
    if(checked){
    ui->textEdit->setFontWeight(QFont::Bold);
     } else if (!checked) {
    ui->textEdit->setFontWeight(QFont::Normal);
   }
   ui->textEdit->setFocus();
}


void MainWindow::on_buttonU_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}


void MainWindow::on_buttonI_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}


void MainWindow::on_actionNew_document_triggered()
{
if(isSaved){
    ui->textEdit->setText(QString());
    } else {
    MainWindow::on_actionSave_triggered();
    }
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}



void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
    setSaved(true);
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();

}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_textEdit_textChanged()
{
    setSaved(false);
}

void MainWindow::on_actionExit_triggered()
{
       close();
}

void MainWindow::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    ui->textEdit->setTextColor(color);
}
