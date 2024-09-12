class BorderDecorator : public Decorator
{
private:
  int borderWidth; 
public:
  BorderDecorator(VisualComponent* comp, int width):  Decorator(comp), borderWidth(width) {}
  void draw() override
  {  
    Decorator::draw();
    drawBorder(); 
  }
  void drawBorder()
  {
    std::cout << "Drawing Border" << borderWidth << std::endl;
  }  
};
