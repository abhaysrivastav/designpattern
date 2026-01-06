#ifndef CHECKBOX_H
#define CHECKBOX_H

// Abstract Product 2: Checkbox interface
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() const = 0;
    virtual void toggle() const = 0;
};

#endif // CHECKBOX_H