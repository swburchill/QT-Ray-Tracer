#include "mainwindow.h"
#include "light.h"
#include "intersection.h"
#include "material.h"
#include "plane.h"
#include "shape.h"
#include "sphere.h"
#include "triangle.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QVector4D>
#include <QVector>

#include <math.h>
#include <iostream>

using namespace std;

int imagePlaneW = 200; //from -100 to 100
int imagePlaneH = 200; //from -100 to 100
int imagePlaneZ = 200; //distance of camera to imagePlane

int imageResolutionW = 256;
int imageResolutionH = 256;

int maxDepth = 5;
int startDepth = 1;

QVector3D backgroundColour = QVector3D(0,0,0);
QVector3D cameraPosition = QVector3D(0,0,200);
QVector3D cameraDirection = QVector3D(0,0,-1);
QVector3D cameraUp = QVector3D(0,1,0);

QVector<Shape*> shapeList = QVector<Shape*>();
QVector<Material*> materialList = QVector<Material*>();
QVector<Light*> lightList = QVector<Light*>();
QVector3D intensityAmbient = QVector3D(0.15f, 0.15f, 0.15f);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectAllSlots();
    createShapes();
    createLights();
    renderScene();
}

MainWindow::~MainWindow()
{
    delete ui;
    //commented out because not sure if works on linux as I had issues with deleting pointers
    //causing a crash last time I check using the school machines. For some reason windows
    //is smarter than linux when it comes to pointers
    //qDeleteAll(shapeList);
    //qDeleteAll(materialList);
    //qDeleteAll(lightList);
}

void MainWindow::createLights()
{
    Light* l1 = new Light(QVector3D(0, 200, 0), QVector3D(.25f, .25f, .25f));
    Light* l2 = new Light(QVector3D(-400, 400, 200), QVector3D(.15f, .15f, .15f));
    Light* l3 = new Light(QVector3D(600, 600, 300), QVector3D(.15f, .15f, .15f));

    lightList.append(l1);
    lightList.append(l2);
    lightList.append(l3);
}

void MainWindow::createShapes()
{
    //create materials - in same function as shapes will need the properties
    Material* bluePlastic = new Material(QVector3D(0.0f,0.0f,255.0f), QVector3D(2.55f,2.55f,2.55f), QVector3D(127.5f,127.5f,127.5f), (float)0); //specular overidden to be opaque for assignment
    Material* greenPlastic = new Material(QVector3D(0.0f,255.0f,0.0f), QVector3D(2.55f,2.55f,2.55f), QVector3D(127.5f,127.5f,127.5f), (float)0); //specular overidden to be opaque for assignment
    Material* brass = new Material(QVector3D(84.00006f,56.999895f,7.000005f), QVector3D(198.99996f,144.999885f,28.999875f), QVector3D(253.000035f,239.99988f,205.999965f), (float)27.8974);
    Material* bronze = new Material(QVector3D(54.1875f,32.5125f,0.054f), QVector3D(182.07f,109.242f,46.2672f), QVector3D(100.35474f,69.33603f,42.513855f), (float)25.6);
    Material* chrome = new Material(QVector3D(63.75f,63.75f,63.75f), QVector3D(102.0f,102.0f,102.0f), QVector3D(197.522235f,197.522235f,197.522235f), (float)76.8);
    Material* copper = new Material(QVector3D(48.76875f,18.7425f,5.7375f), QVector3D(179.469f,68.9724f,21.114f), QVector3D(65.478135f,35.09361f,21.93357f), (float)12.8);
    Material* gold = new Material(QVector3D(63.04875f,50.8725f,18.9975f), QVector3D(191.6682f,154.6524f,57.7524f), QVector3D(160.211655f,141.72951f,93.346575f), (float)51.2);
    Material* pewter = new Material(QVector3D(26.9994f,15.00012f,28.999875f), QVector3D(109.000005f,119.99994f,137.99988f), QVector3D(84.9915f,84.9915f,133.000095f), (float)0); //specular overidden to be opaque for assignment
    Material* silver = new Material(QVector3D(49.02375f,49.02375f,49.02375f), QVector3D(129.4227f,129.4227f,129.4227f), QVector3D(129.609615f,129.609615f,129.609615f), (float)51.2);
    Material* polishedSilver = new Material(QVector3D(58.96875f,58.96875f,58.96875f), QVector3D(70.7625f,70.7625f,70.7625f), QVector3D(197.347305f,197.347305f,197.347305f), (float)89.6);
    //store materials
    materialList.append(bluePlastic);
    materialList.append(brass);
    materialList.append(bronze);
    materialList.append(chrome);
    materialList.append(copper);
    materialList.append(gold);
    materialList.append(pewter);
    materialList.append(silver);
    materialList.append(polishedSilver);
    materialList.append(greenPlastic);
    //create spheres
    Sphere* s1 = new Sphere(QVector3D(0,0,0), (float)40, pewter); //opaque
    Sphere* s2 = new Sphere(QVector3D(0,0,90), (float)20, copper); //10% reflective
    Sphere* s3 = new Sphere(QVector3D(50,50,50), (float)20, gold); //40% reflective
    Sphere* s4 = new Sphere(QVector3D(-50,-50,-50), (float)20, chrome); //80% reflective
    //create planes
    Plane* p1 = new Plane(QVector3D(-100,-100,100), QVector3D(100,-100,-100), QVector3D(0,1,0), QVector3D(0,-100,0), bluePlastic); //opaque
    Plane* p2 = new Plane(QVector3D(-100,-100,-100), QVector3D(100,100,-100), QVector3D(0,0,1), QVector3D(0,0,-100), silver);  //50% reflective
    //create triangles
    Triangle* t1 = new Triangle(QVector3D(50,-100,50), QVector3D(25,-100,0), QVector3D(50,-75,25), chrome); //70% reflective
    Triangle* t2 = new Triangle(QVector3D(50,-100,50), QVector3D(75,-100,25), QVector3D(50,-75,25), brass); //30% reflective
    Triangle* t3 = new Triangle(QVector3D(25,-100,0), QVector3D(75,-100,25), QVector3D(50,-75,25), greenPlastic); //opaque
    //add shapes to object list
    shapeList.append(s1);
    shapeList.append(s2);
    shapeList.append(s3);
    shapeList.append(s4);
    shapeList.append(p1);
    shapeList.append(p2);
    shapeList.append(t1);
    shapeList.append(t2);
    shapeList.append(t3);
}

void MainWindow::autoRender()
{
    if(ui->autoRenderCheckBox->isChecked())
    {
        renderScene();
    }
}

void MainWindow::connectAllSlots()
{
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetValues()));
    connect(ui->renderButton, SIGNAL(clicked()), this, SLOT(renderScene()));

    connect(ui->cameraPositionX, SIGNAL(valueChanged(double)), this, SLOT(autoRender()));
    connect(ui->cameraPositionY, SIGNAL(valueChanged(double)), this, SLOT(autoRender()));
    connect(ui->cameraPositionZ, SIGNAL(valueChanged(double)), this, SLOT(autoRender()));

    connect(ui->viewingDiriectionX, SIGNAL(valueChanged(double)), this, SLOT(autoRender()));
    connect(ui->viewingDiriectionY, SIGNAL(valueChanged(double)), this, SLOT(autoRender()));
    connect(ui->viewingDiriectionZ, SIGNAL(valueChanged(double)), this, SLOT(autoRender()));

    connect(ui->backgroundColourX, SIGNAL(valueChanged(int)), this, SLOT(autoRender()));
    connect(ui->backgroundColourY, SIGNAL(valueChanged(int)), this, SLOT(autoRender()));
    connect(ui->backgroundColourZ, SIGNAL(valueChanged(int)), this, SLOT(autoRender()));

    connect(ui->resolutionX, SIGNAL(valueChanged(int)), this, SLOT(autoRender()));
    connect(ui->resolutionY, SIGNAL(valueChanged(int)), this, SLOT(autoRender()));
}

void MainWindow::getGuiValues()
{
    cameraPosition.setX(ui->cameraPositionX->value());
    cameraPosition.setY(ui->cameraPositionY->value());
    cameraPosition.setZ(ui->cameraPositionZ->value());

    cameraDirection.setX(ui->viewingDiriectionX->value());
    cameraDirection.setY(ui->viewingDiriectionY->value());
    cameraDirection.setZ(ui->viewingDiriectionZ->value());
    cameraDirection.normalize();

    backgroundColour.setX(ui->backgroundColourX->value());
    backgroundColour.setY(ui->backgroundColourY->value());
    backgroundColour.setZ(ui->backgroundColourZ->value());

    imageResolutionW = ui->resolutionX->value();
    imageResolutionH = ui->resolutionY->value();
}

void MainWindow::resetValues()
{
    ui->labelStatus->setText("Resetting");
    imageResolutionW = 256;
    imageResolutionH = 256;

    backgroundColour = QVector3D(0,0,0);
    cameraPosition = QVector3D(0,0,200);
    cameraDirection = QVector3D(0,0,-1);

    ui->cameraPositionX->setValue(0);
    ui->cameraPositionY->setValue(0);
    ui->cameraPositionZ->setValue(200);

    ui->viewingDiriectionX->setValue(0);
    ui->viewingDiriectionY->setValue(0);
    ui->viewingDiriectionZ->setValue(-1);

    ui->backgroundColourX->setValue(0);
    ui->backgroundColourY->setValue(0);
    ui->backgroundColourZ->setValue(0);

    ui->resolutionX->setValue(256);
    ui->resolutionY->setValue(256);
    autoRender();
}

void MainWindow::renderScene()
{
    getGuiValues();

    QVector3D ex = QVector3D::normal(cameraDirection, cameraUp);
    QVector3D up = QVector3D::normal(ex, cameraDirection);
    QVector3D topLeftPixel = cameraPosition + imagePlaneZ*cameraDirection - (imagePlaneW/2)*ex - (imagePlaneH/2)*(-up);
    QVector3D dx = ((float)imagePlaneW / (float)imageResolutionW)*ex;
    QVector3D dy = ((float)imagePlaneH / (float)imageResolutionH)*(-up);

    QVector3D rayDirection;
    QVector3D pixelLocation;
    QVector3D colour;

    ui->labelStatus->setText("Rendering");
    rayTracerImage = new QImage(imageResolutionW, imageResolutionH, QImage::Format_RGB888);
    for(int i = 0; i < imageResolutionW; i++)
    {
        for(int j = 0; j < imageResolutionH; j++)
        {
            pixelLocation = topLeftPixel + i*dx + j*dy;
            rayDirection = pixelLocation - cameraPosition;
            rayDirection.normalize();
            colour = traceRay(cameraPosition, rayDirection, startDepth);
            rayTracerImage->setPixel(i, j, qRgb(clamp(colour.x()), clamp(colour.y()), clamp(colour.z())));
        }
    }
    ui->labelStatus->setText("Render Complete");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*rayTracerImage));
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}

void MainWindow::saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Files (*.bmp)"));
    if(fileName!=NULL)
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        rayTracerImage->save(&file, "BMP");
    }
}

int MainWindow::clamp(int value)
{
    int clamped = value;
    if(value < 0)
    {
        clamped = 0;
    }
    if(value > 255)
    {
        clamped = 255;
    }
    return clamped;
}

QVector3D MainWindow::traceRay(QVector3D rayOrigin, QVector3D rayDirection, int depth)
{
    if(depth > maxDepth)
    {
        return backgroundColour;
    }
    Intersection* rayResult = new Intersection();
    foreach (Shape* shape, shapeList)
    {
        shape->intersect(rayOrigin, rayDirection, rayResult);
    }
    if(rayResult->hit_ == false)
    {
        return backgroundColour;
    }
    else
    {
        QVector3D intensity = QVector3D(0,0,0);
        QVector3D reflectRay = QVector3D(0,0,0);
        foreach (Light* light, lightList)
        {
            QVector3D shadowRay = light->position_ - rayResult->intersectPoint_;
            float lightDistance = shadowRay.length();
            shadowRay.normalize();
            Intersection* shadowResult = new Intersection();
            foreach (Shape* shape, shapeList)
            {
                shape->intersect(rayResult->intersectPoint_, shadowRay, shadowResult);
            }
            if(shadowResult->hit_ == true && (shadowResult->Object_ != rayResult->Object_))
            {
                intensity += rayResult->material_->ambient_ * intensityAmbient;
            }
            else
            {
                // Ambient
                QVector3D ambient = rayResult->material_->ambient_ * intensityAmbient;
                // Diffuse
                QVector3D diffuse = rayResult->material_->diffuse_ * light->intensity_ * qMax(QVector3D::dotProduct(rayResult->normalAtIntersect_,shadowRay), 0.0f);
                // Specular
                QVector3D R = ((2*(QVector3D::dotProduct(rayResult->normalAtIntersect_,shadowRay))* rayResult->normalAtIntersect_) - shadowRay);
                //R.normalize();
                QVector3D V = rayOrigin - rayResult->intersectPoint_;
                V.normalize();
                QVector3D specular = rayResult->material_->specular_ * light->intensity_ * pow(qMax(QVector3D::dotProduct(R,V), 0.0f), rayResult->material_->specularExponent_);
                //find attenuation
                float attenuation = (lightDistance / (0.002*pow(lightDistance,2) + 1*lightDistance + 1));
                //calculate intensity
                intensity += ambient + attenuation*(diffuse + specular);
            }
            //get reflect component
            reflectRay = rayDirection - (2*(QVector3D::dotProduct(rayDirection, rayResult->normalAtIntersect_))* rayResult->normalAtIntersect_);
            reflectRay.normalize();
            intensity += (rayResult->material_->specularExponent_/100) * traceRay(rayResult->intersectPoint_, reflectRay, depth + 1);
        }
        return intensity;
    }
}
