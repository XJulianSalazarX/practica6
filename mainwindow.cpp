#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //escena
    this->setGeometry(400,50,1200,1030);
    this->setMinimumSize(width(),height());
    this->setMaximumSize(width(),height());
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(QPixmap(":/imagenes/cartesiano.png").scaled(1000,1000));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1000,1000);
    ui->graphicsView->setSceneRect(0,0,1000,1000);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVisible(false);
    //escena entrada de datos
    scene2 = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene2);
    ui->graphicsView_2->setFixedSize(900,300);
    ui->graphicsView_2->setSceneRect(0,0,800,300);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVisible(true);
    Invisible();
    ui->splitter->setVisible(true);
    ui->splitter->setGeometry(300,50,ui->splitter->width(),ui->splitter->height());
    ui->next->setVisible(false);
    ui->back->setVisible(false);
    ui->delete_->setVisible(false);
    //Sol
    Sun();
    //timer
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreatePlanet()
{
    if(!planetName(":/imagenes/planet2.png")){
        planets.push_back(new Planet(":/imagenes/planet2.png"));
    }
    else if(!planetName(":/imagenes/planet3.png")){
        planets.push_back(new Planet(":/imagenes/planet3.png"));
    }
    else if(!planetName(":/imagenes/planet4.png")){
        planets.push_back(new Planet(":/imagenes/planet4.png"));
    }
    else if(!planetName(":/imagenes/planet5.png")){
        planets.push_back(new Planet(":/imagenes/planet5.png"));
    }
    else if(!planetName(":/imagenes/planet6.png")){
        planets.push_back(new Planet(":/imagenes/planet6.png"));
    }
}

bool MainWindow::planetName(QString name)
{
    for(Planet *i: planets){
        if(i->getName() == name) return true;
    }
    return false;
}

void MainWindow::Sun()
{
    planets.push_back(new Planet(":/imagenes/sun2.png"));
    planets[0]->setMasa(70000/16);
    planets[0]->setRadio(18.75);
    planets[0]->setVelx(0);
    planets[0]->setVely(0);
    planets[0]->Tamanio();
    planets[0]->setX_inicial(500-planets[0]->getRadio());
    planets[0]->setY_inicial(500-planets[0]->getRadio());
    planets[0]->setPosx(planets[0]->getX_inicial());
    planets[0]->setPosy(planets[0]->getY_inicial());
    scene->addItem(planets[0]);
    planets[0]->setPos(planets[0]->getPosx(),planets[0]->getPosy());
}

void MainWindow::mover()
{
    Aceleracion();
    for(short pos=1;pos<planets.size();pos++){

        planets[pos]->setVelx(planets[pos]->getVelx()+(planets[pos]->getAc_x()*time));
        planets[pos]->setVely(planets[pos]->getVely()+(planets[pos]->getAc_y()*time));
        planets[pos]->setPosx(planets[pos]->getPosx()+(planets[pos]->getVelx()*time));
        planets[pos]->setPosy(planets[pos]->getPosy()+(planets[pos]->getVely()*time));

        qDebug() << "velx: " << planets[pos]->getVelx();
        qDebug() << "vely: " << planets[pos]->getVely();
        qDebug() << "Posx: " << planets[pos]->getPosx();
        qDebug() << "Posy: " << planets[pos]->getPosy();

        planets[pos]->setPos(planets[pos]->getPosx(),planets[pos]->getPosy());
    }
}

void MainWindow::Aceleracion()
{
    double acx=0,acy=0,dist=0;
//    for(short pos=1;pos<planets.size();pos++){
//        for(short pos2=0;pos2<planets.size();pos2++){
//            if(pos!=pos2){
//                dist = pow(planets[pos2]->getPosx()-planets[pos]->getPosx(),2);
//                dist += pow(planets[pos2]->getPosy()-planets[pos]->getPosy(),2);
//                dist = sqrt(dist);
//                acx+=(planets[pos2]->getMasa()/pow(dist,3))*(planets[pos2]->getPosx()-planets[pos]->getPosx());
//                acy+=(planets[pos2]->getMasa()/pow(dist,3))*(planets[pos2]->getPosy()-planets[pos]->getPosy());
//            }
//            qDebug() << "Distancia " << dist;
//            dist = 0;
//        }
//        planets[pos]->setAc_x(acx);
//        planets[pos]->setAc_y(acy);
//        qDebug() << "ac x " << acx;
//        qDebug() << "ac y " << acy;
//        acx=0,acy=0;
//    }

    for(short pos=1;pos<planets.size();pos++){
        dist = pow(planets[0]->getPosx()-planets[pos]->getPosx(),2);
        dist += pow(planets[0]->getPosy()-planets[pos]->getPosy(),2);
        dist = sqrt(dist);
        acx+=(planets[0]->getMasa()/pow(dist,3))*(planets[0]->getPosx()-planets[pos]->getPosx());
        acy+=(planets[0]->getMasa()/pow(dist,3))*(planets[0]->getPosy()-planets[pos]->getPosy());
        qDebug() << "Distancia " << dist;
        dist = 0;
        planets[pos]->setAc_x(acx);
        planets[pos]->setAc_y(acy);
        qDebug() << "ac x " << acx;
        qDebug() << "ac y " << acy;
        acx=0,acy=0;
    }
}

void MainWindow::on_add_clicked()
{
    if(ui->ok->isVisible()){
        QMessageBox::critical(this,"Error","Ingrese nombre del archivo para continuar");
        return;
    }

    saveButton=true;

    ui->posx->setReadOnly(false);
    ui->posy->setReadOnly(false);
    ui->velx->setReadOnly(false);
    ui->vely->setReadOnly(false);

    ui->masa->setValue(0);
    ui->radio->setValue(0);
    ui->velx->setValue(0);
    ui->vely->setValue(0);
    ui->posx->setValue(0);
    ui->posy->setValue(0);

    timer->stop();
    ui->graphicsView_2->setVisible(true);
    Visible();

    ui->next->setVisible(false);
    ui->back->setVisible(false);
    ui->delete_->setVisible(false);

}
void MainWindow::on_save_clicked()
{
    if(ui->ok->isVisible()){
        QMessageBox::critical(this,"Error","Ingrese nombre del archivo para continuar");
        return;
    }
    if(saveButton){
        //entro en donde no debia
        if(planets.size()==6){
            QMessageBox::critical(this,"Error","No se pueden agregar más de 6 planetas.");
            ui->graphicsView_2->setVisible(false);
            Invisible();
            return;
        }
        //agregar planeta
        short pos;
        CreatePlanet();
        pos = planets.size()-1;
        planets[pos]->setMasa(ui->masa->value()/16);
        planets[pos]->setRadio(ui->radio->value()/16);
        planets[pos]->setVelx(ui->velx->value());
        planets[pos]->setVely(ui->vely->value());
        planets[pos]->Tamanio();
        planets[pos]->setX_inicial(500+(ui->posx->value()/16)-planets[pos]->getRadio());
        planets[pos]->setY_inicial(500-(ui->posy->value()/16)-planets[pos]->getRadio());
        planets[pos]->setPosx(planets[pos]->getX_inicial());
        planets[pos]->setPosy(planets[pos]->getY_inicial());
        scene->addItem(planets[pos]);
        planets[pos]->setPos(planets[pos]->getPosx(),planets[pos]->getPosy());
        //cerrar scena
        ui->graphicsView_2->setVisible(false);
        Invisible();
    }

    else{
        //donde debia
        planets[number]->setMasa(ui->masa->value()/16);
        planets[number]->setRadio(ui->radio->value()/16);
        planets[number]->setVelx(ui->velx->value());
        planets[number]->setVely(ui->vely->value());
        planets[number]->Tamanio();
        planets[number]->setX_inicial(500+(ui->posx->value()/16)-planets[number]->getRadio());
        planets[number]->setY_inicial(500-(ui->posy->value()/16)-planets[number]->getRadio());
        planets[number]->setPosx(planets[number]->getX_inicial());
        planets[number]->setPosy(planets[number]->getY_inicial());
        planets[number]->setPos(planets[number]->getPosx(),planets[number]->getPosy());
        //cerrar scena
        on_pushButton_3_clicked();

    }
    Aceleracion();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->ok->isVisible()){
        QMessageBox::critical(this,"Error","Ingrese nombre del archivo para continuar");
        return;
    }
    ui->graphicsView_2->setVisible(false);
    Invisible();
    ui->next->setVisible(false);
    ui->back->setVisible(false);
    ui->delete_->setVisible(false);
}

void MainWindow::Visible()
{
    //label
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    //spin box
    ui->posx->setVisible(true);
    ui->posy->setVisible(true);
    ui->masa->setVisible(true);
    ui->radio->setVisible(true);
    ui->velx->setVisible(true);
    ui->vely->setVisible(true);
    //button
    ui->splitter_2->setVisible(true);
}

void MainWindow::Invisible()
{
    //label
    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    //spin box
    ui->posx->setVisible(false);
    ui->posy->setVisible(false);
    ui->masa->setVisible(false);
    ui->radio->setVisible(false);
    ui->velx->setVisible(false);
    ui->vely->setVisible(false);
    //button
    ui->splitter_2->setVisible(false);
}
void MainWindow::on_play_clicked()
{
    if(ui->ok->isVisible()){
        QMessageBox::critical(this,"Error","Ingrese nombre del archivo para continuar");
        return;
    }

    if(planets.size()==1){
        QMessageBox::critical(this,"Error","Debe haber por lo menos un planeta diferente al sol para iniciar la simulacion.");
        return;
    }
    else if(ui->graphicsView_2->isVisible()){
        QMessageBox::critical(this,"Error","Cierre la ventana abierta.");
        return;
    }
    timer->start(500);
}

void MainWindow::on_stop_clicked()
{
    timer->stop();
}

void MainWindow::on_view_clicked()
{
    if(ui->ok->isVisible()){
        QMessageBox::critical(this,"Error","Ingrese nombre del archivo para continuar");
        return;
    }
    saveButton = false;

    number = 0;
    timer->stop();
    ui->graphicsView_2->setVisible(true);
    Visible();
    ui->next->setVisible(true);
    ui->back->setVisible(true);
    ui->delete_->setVisible(true);

    if(number ==0){
        ui->posx->setReadOnly(true);
        ui->posy->setReadOnly(true);
        ui->velx->setReadOnly(true);
        ui->vely->setReadOnly(true);
    }
    else{
        ui->posx->setReadOnly(false);
        ui->posy->setReadOnly(false);
        ui->velx->setReadOnly(false);
        ui->vely->setReadOnly(false);
    }

    ui->posx->setValue((planets[number]->getX_inicial()+planets[number]->getRadio()-500)*16);
    ui->posy->setValue((500-(planets[number]->getY_inicial()+planets[number]->getRadio()))*16);
    ui->masa->setValue(planets[number]->getMasa()*16);
    ui->radio->setValue(planets[number]->getRadio()*16);
    ui->velx->setValue(planets[number]->getVelx());
    ui->vely->setValue(planets[number]->getVely());

}

void MainWindow::on_next_clicked()
{
    number ++;
    if(number == planets.size()) number = 0;

    if(number ==0){
        ui->posx->setReadOnly(true);
        ui->posy->setReadOnly(true);
        ui->velx->setReadOnly(true);
        ui->vely->setReadOnly(true);
    }
    else{
        ui->posx->setReadOnly(false);
        ui->posy->setReadOnly(false);
        ui->velx->setReadOnly(false);
        ui->vely->setReadOnly(false);
    }

    ui->posx->setValue((planets[number]->getX_inicial()+planets[number]->getRadio()-500)*16);
    ui->posy->setValue((500-(planets[number]->getY_inicial()+planets[number]->getRadio()))*16);
    ui->masa->setValue(planets[number]->getMasa()*16);
    ui->radio->setValue(planets[number]->getRadio()*16);
    ui->velx->setValue(planets[number]->getVelx());
    ui->vely->setValue(planets[number]->getVely());
}

void MainWindow::on_back_clicked()
{
    number --;
    if(number == -1) number = planets.size()-1;

    if(number ==0){
        ui->posx->setReadOnly(true);
        ui->posy->setReadOnly(true);
        ui->velx->setReadOnly(true);
        ui->vely->setReadOnly(true);
    }
    else{
        ui->posx->setReadOnly(false);
        ui->posy->setReadOnly(false);
        ui->velx->setReadOnly(false);
        ui->vely->setReadOnly(false);
    }

    ui->posx->setValue((planets[number]->getX_inicial()+planets[number]->getRadio()-500)*16);
    ui->posy->setValue((500-(planets[number]->getY_inicial()+planets[number]->getRadio()))*16);
    ui->masa->setValue(planets[number]->getMasa()*16);
    ui->radio->setValue(planets[number]->getRadio()*16);
    ui->velx->setValue(planets[number]->getVelx());
    ui->vely->setValue(planets[number]->getVely());
}

void MainWindow::on_delete__clicked()
{
    if(number==0){
        QMessageBox::critical(this,"Error","No se puede eliminar el sol.");
        return;
    }
    scene->removeItem(planets[number]);
    delete planets[number];
    planets.removeAt(number);
    QMessageBox::warning(this,"Advertencia","Has eliminado un planeta.");

    on_pushButton_3_clicked();

}

void MainWindow::on_ok_clicked()
{
    file_name = ui->lineEdit->text();


    if(file_name.isEmpty() or file_name.mid(file_name.size()-4)!=".txt"){
        QMessageBox::critical(this,"Error","Ingrese nombre del archivo, debe terminar en .txt.");
        return;
    }

    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this,"Error","Ingrese un nombre valido.");
        return;
    }
    file.flush();
    file.close();

    ui->ok->setVisible(false);
    ui->splitter->setVisible(false);

    ui->graphicsView->setVisible(true);
    ui->graphicsView_2->setVisible(false);

}
