/* 
 * File:   main.cpp
 * Author: LUPO Kévin - LAMOUROUX Vincent - KEMPF Anthony 
 */

#include <QtGui>
#include <string.h>
#include "MainWindow.h"
#include <QTableWidgetItem>
#include <QString>
#include<fstream>
#include <exception>
#include "MainWindow.h" 

using namespace std;

 MainWindow::MainWindow()
 {
     QWidget *widget = new QWidget;
     setCentralWidget(widget);
     
     //Création des boutons de l'interface
     add = new QPushButton("Ajouter",this);
     remove = new QPushButton("Retirer",this);
     start = new QPushButton("Lancer le proxy", this);
     restart = new QPushButton("Redemarrer le proxy", this);
     
     //Affichage
     add->show();
     remove->show();
     start->show();
     restart->show();
     
     //On ouvre le fichier de service
     QFile file("services");
     file.open(QIODevice::ReadOnly|QIODevice::Text);
     QTextStream in(&file);
     int count=0;
     QString s;
     
     //On compte le nombre de ligne du fichier afin de créer le tableau de service
     while(!in.atEnd()){
         s = file.readLine();
         count++;
     }
     file.close();

     //On lit le fichier et on remplit les différents éléments de la structure
     int i =0;
     file.open(QIODevice::ReadOnly);
     while(!in.atEnd()){
         in >> _servicesArray[i]._service >> _servicesArray[i]._port >> _servicesArray[i]._protocol >> _servicesArray[i]._receiver;
         _servicesArray[i]._activated = false;
         i++;
     }
     file.close();
     
     QWidget *topFiller = new QWidget;
     topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     
     //Création de la table de widget
     table = new QTableWidget(count,5,this);
     table->setFixedSize(550,350);
     
     //Label des colonnes
     table->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Protocole"),1));   
     table->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Service"),1));
     table->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Port"),1));
     table->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Destinataire"),1));
     table->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Etat"),1));
     
     for (int i = 0;i <count;i++){
        //On range les différents éléments du tableau dans la table
        table->setItem(i,0,new QTableWidgetItem(_servicesArray[i]._protocol,1));
        table->setItem(i,1,new QTableWidgetItem(_servicesArray[i]._service,1));
        table->setItem(i,2,new QTableWidgetItem(_servicesArray[i]._port,1));
        table->setItem(i,3,new QTableWidgetItem(_servicesArray[i]._receiver,1));
        //Desactivation des saisies dans les cellules
        table->item(i,0)->setFlags(Qt::ItemIsEnabled);
        table->item(i,1)->setFlags(Qt::ItemIsEnabled);
        table->item(i,2)->setFlags(Qt::ItemIsEnabled);
        table->item(i,3)->setFlags(Qt::ItemIsEnabled);
        //Creation de la checkbox de la ligne
        checkBox[i] = new QCheckBox(table);
        table->setCellWidget(i,4,checkBox[i]);        
        checkBox[i]->setChecked(_servicesArray[i]._activated);
     }

     QWidget *bottomFiller = new QWidget;
     bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     
     
     QVBoxLayout *layout = new QVBoxLayout;
     layout->setMargin(5);
     layout->addWidget(topFiller);
     layout->addWidget(bottomFiller);
     layout->addWidget(add);
     layout->addWidget(remove);
     layout ->addWidget(start);
     layout->addWidget(restart);
     
     widget->setLayout(layout);

     createActions();
     createMenus();

     setWindowTitle(tr("Editeur de services"));
     //La taille de la fenêtre est fixe
     setMinimumSize(550, 500);
     setMaximumSize(550,500);
     resize(550, 500);
 }

 //Nettoyage du fichier
 void MainWindow::newFile()
 {
     table->clear();
     for (int i = table->rowCount()-1; i>=1 ; i--) 
         table->removeRow(i);
     for (int i = 0; i <4; i++){
        table->setItem(0,i, new QTableWidgetItem(1));
        table->item(0,i)->setFlags(Qt::ItemIsEnabled);
     }
     table->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Protocole"),1));   
     table->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Service"),1));
     table->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Port"),1));
     table->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Destinataire"),1));
     table->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Etat"),1));
     checkBox[0] = new QCheckBox(table);
     table->setCellWidget(0,4,checkBox[0]);        
     checkBox[0]->setChecked(false);
     connect (checkBox[0], SIGNAL(stateChanged(int)), this,SLOT(check()));
 }

 //On sauve le fichier
 void MainWindow::save()
 {   
     QFile file("services");
     QTextStream stream(&file);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
     stream.setCodec("UTF-8");
     
     for (int i = 0; i <table->rowCount(); i++){
         for(int j = 0; j <4; j++){
             stream << table->item(i,j)->text() << " ";
         }
         stream <<endl;
     }
     file.close();
 }

 void MainWindow::about()
 {
     QMessageBox::about(this, tr("Projet M1 Reseau"),
             tr("LUPO Kevin - KEMPF Anthony - LAMOUROUX Vincent"));
 }

 //Liage des actions aux boutons/menus
 void MainWindow::createActions()
 {   
     newAct = new QAction(tr("&Nouveau"), this);
     newAct->setShortcut(tr("Ctrl+N"));
     newAct->setStatusTip(tr("&Réinitialise le fichier"));
     connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     saveAct = new QAction(tr("&Sauvegarder"), this);
     saveAct->setShortcut(tr("Ctrl+S"));
     saveAct->setStatusTip(tr("Sauve le fichier de services"));
     connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

     exitAct = new QAction(tr("&Quitter"), this);
     exitAct->setShortcut(tr("Ctrl+Q"));
     exitAct->setStatusTip(tr("Quitte l'application"));
     connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
     
     aboutAct = new QAction(tr("&Projet"), this);
     aboutAct->setStatusTip(tr("Noms des etudiants"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
     
     for(int i = 0; i <table->rowCount(); i++)
        connect (checkBox[i], SIGNAL(stateChanged(int)), this,SLOT(check()));
     connect(add, SIGNAL(clicked()), this, SLOT(addLine()));
     connect(remove, SIGNAL(clicked()), this, SLOT(removeLine()));
     connect(start, SIGNAL(clicked()), this, SLOT(startProxy()));
     connect(restart, SIGNAL(clicked()), this, SLOT(restartProxy()));
 }

 //Ajout d'une ligne 
 void MainWindow::addLine(){
     if (table->rowCount()<100 ){
        int row = table->rowCount();
        table->insertRow(row);
        for (int i =0; i < 4;i++){
                table->setItem(row,i, new QTableWidgetItem(1));
                table->item(row,i)->setFlags(Qt::ItemIsEnabled);
        }
        checkBox[row] = new QCheckBox(table);
        table->setCellWidget(row,4,checkBox[row]);
        connect(checkBox[row], SIGNAL(stateChanged(int)), this,SLOT(check()));
     }else{
         QMessageBox::about(this, tr("Erreur"),
             tr("Le nombres de services est maximal"));
     }
 }
 
 //Retire une ligne du fichier
 void MainWindow::removeLine(){
     int row = table->rowCount();
     table->removeRow(row-1);
 }
 
 //Entrée dans le mode édition
 void MainWindow::check(){
     for(int i = 0; i <table->rowCount(); i++){
         if (checkBox[i]->isChecked()){
                for (int j = 0; j < 4; j++){
                        table->item(i,j)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable);
                }
         }else{
             for(int j = 0; j < 4; j++){
                 table->item(i,j)->setFlags(Qt::ItemIsEnabled);
             }
         }
     }
 }
 
 //Lancement du  proxy
 void MainWindow::startProxy(){
     //exec du projet reseau
     system("exec ~/NetBeansProjects/Projet_Reseau_M1/projet_reseau_m1");
 }
 
 //Redémarrage du proxy
 void MainWindow::restartProxy(){
     //exec pkill 15 projet reseau
     system("exec pkill -15 ~/NetBeansProjects/Projet_Reseau_M1/projet_reseau_m1");
     //exec projet reseau
     system("exec ~/NetBeansProjects/Projet_Reseau_M1/projet_reseau_m1");
 }
 
 //Creations des menus
 void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&Fichier"));
     fileMenu->addAction(newAct);
     fileMenu->addAction(saveAct);
     fileMenu->addSeparator();
     fileMenu->addAction(exitAct);

     helpMenu = menuBar()->addMenu(tr("&A propos"));
     helpMenu->addAction(aboutAct);
 }