#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>



int main(int argc, char *argv[]){

    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("ApexNotes");
    mainWindow.resize(800, 600);

    QTextEdit *textEditor = new QTextEdit();
    mainWindow.setCentralWidget(textEditor);

    QMenu *fileMenu = mainWindow.menuBar()->addMenu("File");
    QAction *openAction = fileMenu->addAction("Open");
    QAction *saveAction = fileMenu->addAction("Save");
    QAction *exitActin = fileMenu->addAction("Exit");


    QObject::connect(openAction, &QAction::triggered, [&](){
        // Placeholder for open file logic
         QString fileName = QFileDialog::getOpenFileName(&mainWindow);
         if(!fileName.isEmpty()){
             QFile file(fileName);
             if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                 QTextStream in(&file);
                 textEditor->setPlainText(in.readAll());
             }
         }

    });

    QObject::connect(saveAction, &QAction::triggered, [&](){
        // Placeholder for save file logic
        QString fileName = QFileDialog::getSaveFileName(&mainWindow);
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << textEditor->toPlainText();
            }
        }
    });

    QObject::connect(exitActin, &QAction::triggered, [&](){
        app.quit();
    });

    mainWindow.show();
    return app.exec();
}
