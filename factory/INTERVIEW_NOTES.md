# Factory Design Pattern - Interview Guide

## 🎯 Definition
The Factory Pattern is a **creational design pattern** that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.

## 🔑 Key Components

1. **Product (Shape)**: Abstract interface defining what objects the factory creates
2. **Concrete Products (Circle, Rectangle, Triangle)**: Actual implementations
3. **Factory (ShapeFactory)**: Contains the creation logic
4. **Client (main)**: Uses factory to get objects without knowing concrete classes

## 💡 When to Use

✅ **Use Factory Pattern When:**
- Object creation logic is complex
- You want to decouple object creation from usage
- The exact types aren't known until runtime
- You need centralized object creation
- You want to follow Open/Closed Principle

❌ **Avoid When:**
- Simple object creation (use `new` directly)
- Only one type of object
- No variation in creation logic

## 🎤 Common Interview Questions & Answers

### Q1: What problem does Factory Pattern solve?
**Answer:** It solves the tight coupling between client code and concrete classes. Instead of using `new Circle()`, clients use `factory.createShape("circle")`, making code more flexible and maintainable.

### Q2: Factory vs Abstract Factory?
**Answer:** 
- **Factory**: Creates objects of ONE product family (e.g., shapes)
- **Abstract Factory**: Creates objects of MULTIPLE related families (e.g., Windows UI + Mac UI)

### Q3: Advantages?
**Answer:**
1. **Loose Coupling**: Client doesn't depend on concrete classes
2. **Single Responsibility**: Creation logic in one place
3. **Open/Closed**: Easy to add new types
4. **Code Reusability**: Centralized creation logic

### Q4: Disadvantages?
**Answer:**
1. Can introduce unnecessary complexity for simple cases
2. Need to create new classes for each product type
3. Factory class can become complex with many products

### Q5: Real-world examples?
**Answer:**
- Database connection factories (MySQL, PostgreSQL, MongoDB)
- GUI toolkit factories (Button, TextField for different OS)
- Document creation (PDF, Word, Excel)
- Payment processors (PayPal, Stripe, Credit Card)

## 🔄 Variations

### 1. Simple Factory (Used in our example)
- Single factory class with static method
- Not a true design pattern, but common idiom

### 2. Factory Method Pattern
- Abstract creator class with factory method
- Subclasses override to create specific products

### 3. Abstract Factory Pattern
- Creates families of related objects
- Multiple factory methods

## 💻 Code Flow

```
Client → ShapeFactory::createShape("circle") → new Circle() → Shape*
```

## 🎓 Design Principles Applied

1. **Dependency Inversion**: Depend on abstractions (Shape), not concrete classes
2. **Open/Closed**: Open for extension, closed for modification
3. **Single Responsibility**: Factory handles creation, shapes handle behavior

## 🚀 How to Extend

To add a new shape (e.g., Pentagon):

1. Create Pentagon.h implementing Shape interface
2. Add case in ShapeFactory::createShape()
3. Client code remains unchanged! ✨

## ⚡ Quick Implementation Checklist

- [ ] Abstract product interface
- [ ] Concrete product classes
- [ ] Factory class with creation method
- [ ] Client uses factory, not `new`
- [ ] Handle unknown types gracefully
- [ ] Use smart pointers for memory safety

## 🎯 What Interviewers Look For

1. ✅ Understanding of decoupling
2. ✅ Knowledge of when to use/not use
3. ✅ Ability to implement from scratch
4. ✅ Awareness of trade-offs
5. ✅ Understanding relationship with other patterns
6. ✅ Real-world application examples
