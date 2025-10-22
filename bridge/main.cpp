#include <iostream>
class Shape;
class Circle;
class Rectangle;

class Renderer
{

public:
    virtual void render(const Shape* shape) =0;
};

// Just declare the classes, don't implement render() yet
class OpenGLRenderer:public Renderer
{
public:
    void render(const Shape* shape) override;  // Declaration only
};

class DirectXRenderer:public Renderer
{
public:
    void render(const Shape* shape) override;  // Declaration only
};


class Shape
{
protected:
    Renderer* renderer;

public:
    Shape(Renderer* ren): renderer(ren)
    {

    }
    
    virtual ~Shape()
    {
        
    }

    virtual void draw()=0;
    virtual void renderShape(Renderer* renderer)=0;
};

class Circle:public Shape
{
    int radius;
    int x,y;
public:
    Circle(Renderer* ren, int r, int posX, int posY):Shape(ren), radius(r), x(posX), y(posY)
    {}
    void draw() override
    {
        std::cout<<"This is Circle Draw " << std::endl;
        renderer->render(this);
        renderShape(renderer);
    }
    int getRadius() const {return radius;};
    int getX() const {return x;}
    int getY() const {return y;}

    void renderShape(Renderer* ren) override
    {
        std::cout << "Render the circle of radius= " << radius
                  << ", position= ( " << x << "," << y << ")" << std::endl;
    }
};

class Rectangle:public Shape
{
    int length;
    int width;
public:
    Rectangle(Renderer* ren,int len, int width):Shape(ren), length(len), width(width){}
    void draw() override
    {
         std::cout<<"This is Rectangle Draw" << std::endl;
         renderer->render(this);
         renderShape(renderer);
    }

    void renderShape(Renderer* ren) override
    {
        std::cout << "Render rectangle with length : " << length
                  << "and width : " << width << std::endl;
    }
    int getLength() const{return length;}
    int getWidth() const{return width;}
};

// NOW implement the render methods after all classes are defined
void OpenGLRenderer::render(const Shape* shape) 
{
    std::cout << "OpenGL renderer is rendering the shape " << std::endl; 

    if(const Circle* circle = dynamic_cast<const Circle*>(shape))
    {
        std::cout << "Circle with radius=" << circle->getRadius() 
                  << " at position(" << circle->getX() << "," << circle->getY() << ")" << std::endl;
    }
    else if(const Rectangle* rect = dynamic_cast<const Rectangle*>(shape))
    {
        std::cout << "Rectangle with dimensions=" << rect->getLength() 
                  << "x" << rect->getWidth() << std::endl;
    }
    else
    {
        std::cout << "Unknown Shape" << std::endl;
    }
}

void DirectXRenderer::render(const Shape* shape) 
{
    std::cout << "DirectX is rendering the shape" << std::endl;
    // Add your DirectX dynamic_cast implementation here!
}

int main() {
    // Step 1: Create renderers
    OpenGLRenderer openglRenderer;
    DirectXRenderer directxRenderer;
    
    // Step 2: Create shapes with different renderers
    Circle circle1(&openglRenderer, 10, 50, 100);    // radius=10, x=50, y=100
    Circle circle2(&directxRenderer, 15, 200, 300);   // radius=15, x=200, y=300
    
    Rectangle rect1(&openglRenderer,10,20 );   // Rectangle with OpenGL
    Rectangle rect2(&directxRenderer,20,30);  // Rectangle with DirectX
    
    // Step 3: Test the Bridge Pattern magic!
    circle1.draw();   // Circle + OpenGL
    circle2.draw();   // Circle + DirectX
    rect1.draw();     // Rectangle + OpenGL  
    rect2.draw();     // Rectangle + DirectX
    
    return 0;
}
