class Decorator : public VisualComponent
{
protected:
  VisualComponent* component; 

public:
  Decorator(VisualComponent* comp) : component(comp) {}
  void draw() override{
    component->draw();
  }
};


