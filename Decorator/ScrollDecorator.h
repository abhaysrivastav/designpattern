class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(VisualComponent* comp) : Decorator(comp) {}

    void draw() override {
        Decorator::draw();  // Call the base component's draw method
        drawScrollBar();    // Add scrollbar-related functionality
    }

    void drawScrollBar() {
        std::cout << "Drawing scrollbar.\n";
    }
};
