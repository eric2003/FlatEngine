#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <random>
#include <iostream>

void Initialize();

enum class ShapeType
{
    Circle = 0,
    Box = 1
};

class RandomHelper
{
public:
    static std::default_random_engine gen;
    static int RandomInteger( int min, int max )
    {
        std::uniform_int_distribution<> distribution(min, max);
        int result = distribution(gen);
        return result;
    }
    static float RandomSingle(float min, float max)
    {
        std::uniform_real_distribution<float> distribution(min, max);
        float result = distribution(gen);
        return result;
    }
};


std::default_random_engine RandomHelper::gen;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //create a scene
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsRectItem *rect = new QGraphicsRectItem();
    rect->setRect(0,0,100,100);
    //add the item to the scene
    scene->addItem(rect);
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();
    Initialize();
    return a.exec();
}

void Initialize()
{
    int width = 1280;
    int height = 768;

    int bodyCount = 10;

    for ( int i = 0; i < bodyCount; ++ i )
    {
        int type = RandomHelper::RandomInteger(0,1);
        std::cout << " type = " << type << "\n";
    }

    for ( int i = 0; i < bodyCount; ++ i )
    {
        float ff = RandomHelper::RandomSingle(0,1);
        std::cout << " ff = " << ff << "\n";
    }

    const float padding = 20.0f;


}
