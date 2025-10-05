#include <iostream>
#include <map>
#include <memory>
#include <string>

struct FontProperties
{
    std::string fontName;
    int fontSize;
    std::string fontStyle;
    std::string color;

    bool operator<(const FontProperties& other) const
    {
        if(fontName!=other.fontName) return fontName<other.fontName;
        if(fontSize!=other.fontSize) return fontSize<other.fontSize;
        if(fontStyle!=other.fontStyle) return fontStyle<other.fontStyle;

        return color<other.color;
    }
};

class Font
{
    FontProperties fontProperties;
public:
    Font(const FontProperties& props):fontProperties(props){}

    void display(char c, int x, int y)
    {
        std::cout << "Char" << c 
                  << " x: " << x << "y: " << y  
                  << "with fontname" <<  fontProperties.fontName
                  << "with fontsize" <<  fontProperties.fontSize
                  << "with fontstyle" <<  fontProperties.fontStyle
                  << "with fontcolor" <<  fontProperties.color
                  << std::endl;
    }
};

class FontFactory
{
    std::map<FontProperties, std::shared_ptr<Font>> fonts;
public:
    std::shared_ptr<Font> getFont(const FontProperties& props)
    {
        if(fonts.find(props) == fonts.end())
        {
            fonts[props]=std::make_shared<Font>(props);
        }
        return fonts[props];
    }

    int getFlyweightCount(){
        return fonts.size();
    }
};

int main()
{
    FontFactory factory;

    FontProperties arial12Bold{"Arial", 12, "Bold","Black"};

    auto font1=factory.getFont(arial12Bold);
    auto font2=factory.getFont(arial12Bold);

    font1->display('A', 10, 20);
    font2->display('B', 30, 40);

   // Different font properties - new flyweight
    FontProperties times14Italic{"Times", 14, "Italic", "Red"};
    auto font3 = factory.getFont(times14Italic);
    font3->display('C', 50, 60);
    
    std::cout << "Same flyweight reused: " << (font1 == font2) << std::endl;
    std::cout << "Total flyweights created: " << factory.getFlyweightCount() << std::endl;
    
    return 0;
}