# Flyweight Design Pattern - Conceptual Notes

## 📋 **What is Flyweight Pattern?**

**Definition:** A structural design pattern that minimizes memory usage by sharing common data (intrinsic state) among multiple objects, while keeping unique data (extrinsic state) separate.

**Core Principle:** Instead of storing all data in each object, share common data and pass unique data as parameters.

**Key Insight:** "Share what you can, parameterize what you can't!"

---

## 🎯 **When to Use Flyweight Pattern?**

### **Use When:**
- ✅ Large number of objects need to be created (thousands/millions)
- ✅ Objects have significant common/shared data
- ✅ Memory is constrained (embedded systems, mobile apps, games)
- ✅ Object creation/storage is expensive
- ✅ Application doesn't depend on object identity

### **Don't Use When:**
- ❌ Objects have mostly unique data
- ❌ Small number of objects (< 100)
- ❌ Memory is not a concern
- ❌ Extrinsic state would be too complex to manage

---

## 🔑 **Key Components & Concepts**

### **1. Intrinsic State (Shared Data)**
- Data that can be shared among multiple objects
- Stored **inside** flyweight object
- **Immutable** - never changes after creation
- **Context-independent** - same regardless of where flyweight is used
- Examples: font properties, textures, colors, templates

### **2. Extrinsic State (Unique Data)** 
- Data that is unique to each object instance
- **NOT stored** in flyweight object
- Passed as **parameters** to flyweight methods
- **Context-dependent** - varies based on usage
- Examples: position coordinates, character content, object ID

### **3. Flyweight Factory**
- Manages flyweight pool/cache using map or hash table
- Ensures no duplicate flyweights are created
- Returns existing flyweight or creates new one
- Acts as central registry for all flyweights

### **4. Context/Client**
- Maintains references to flyweights
- Stores or computes extrinsic state
- Passes extrinsic state to flyweight operations

---

## 📊 **With vs Without Flyweight Comparison**

### **Without Flyweight Pattern:**

```cpp
// Each object stores ALL data (intrinsic + extrinsic)
class Character {
    char content;          // Extrinsic (unique per character)
    int x, y;             // Extrinsic (unique position)
    string fontName;      // Intrinsic (could be shared!)
    int fontSize;         // Intrinsic (could be shared!)
    string fontStyle;     // Intrinsic (could be shared!)
    string fontColor;     // Intrinsic (could be shared!)
    
    void display() { /* render character */ }
};

// Problem: 10,000 characters = 10,000 duplicate font properties!
vector<Character> document;  // Each stores complete data
```

### **With Flyweight Pattern:**

```cpp
// Flyweight stores only intrinsic state
class FontFlyweight {
    string fontName;      // Intrinsic only
    int fontSize;         // Intrinsic only  
    string fontStyle;     // Intrinsic only
    string fontColor;     // Intrinsic only
    
    void display(char content, int x, int y);  // Extrinsic passed as parameters
};

// Context stores extrinsic state + flyweight reference
class Character {
    char content;         // Extrinsic (unique)
    int x, y;            // Extrinsic (unique)
    FontFlyweight* font; // Reference to shared flyweight
};

// Result: 10,000 characters share maybe 5-10 font flyweights!
```

---

## 💾 **Memory Impact Analysis**

### **Text Editor Example:**

| Scenario | Objects | Memory Usage | Calculation |
|----------|---------|--------------|-------------|
| **Without Flyweight** | 10,000 characters | ~500KB | 10,000 × 50 bytes each |
| **With Flyweight** | 10 flyweights + 10,000 contexts | ~85KB | (10 × 50) + (10,000 × 8) bytes |
| **Memory Saved** | - | **83% reduction** | 415KB saved |

### **Game Example (Forest with Trees):**

| Scenario | Objects | Memory Usage | Calculation |
|----------|---------|--------------|-------------|
| **Without Flyweight** | 100,000 trees | ~10MB | 100,000 × 100 bytes each |
| **With Flyweight** | 5 tree types + 100,000 contexts | ~1.3MB | (5 × 100) + (100,000 × 12) bytes |
| **Memory Saved** | - | **87% reduction** | 8.7MB saved |

---

## 🔄 **Pattern Comparisons**

### **Flyweight vs Factory Pattern**
| Aspect | Flyweight | Factory |
|--------|-----------|---------|
| **Purpose** | Memory optimization | Object creation abstraction |
| **Object Reuse** | **Reuses** existing objects | **Creates** new objects each time |
| **Cache/Pool** | Maintains object pool | No caching mechanism |
| **Identity** | Same object for same key | Different objects each time |
| **Focus** | Sharing intrinsic state | Hiding creation complexity |

### **Flyweight vs Singleton**  
| Aspect | Flyweight | Singleton |
|--------|-----------|-----------|
| **Instance Count** | **Multiple** (per unique key) | **One** total instance |
| **Key-based** | Uses keys for different instances | No key concept |
| **Scope** | Per flyweight type | Global single instance |
| **Use Case** | Many similar objects | Single shared resource |

### **Flyweight vs Object Pool**
| Aspect | Flyweight | Object Pool |
|--------|-----------|-------------|
| **Object State** | Immutable flyweights | Mutable pooled objects |
| **Sharing** | Concurrent sharing | Sequential reuse |
| **Lifecycle** | Permanent existence | Created/destroyed/reused |
| **Purpose** | Memory optimization | Creation cost optimization |

---

## 🎮 **Real-World Use Cases**

### **1. Text Processing Systems**
- **Intrinsic:** Font properties, styles, formatting rules
- **Extrinsic:** Character content, position in document
- **Benefit:** Massive documents with few font variations

### **2. Game Development**
- **Particles:** Sprite/texture (intrinsic), position/velocity (extrinsic)
- **Forest Systems:** Tree species data (intrinsic), location/age (extrinsic)
- **Bullets:** Bullet type/damage (intrinsic), position/direction (extrinsic)

### **3. GUI/Graphics Systems**
- **Icons:** Image data (intrinsic), screen position (extrinsic)
- **Widgets:** Style/theme (intrinsic), content/state (extrinsic)
- **Maps:** Tile types (intrinsic), grid coordinates (extrinsic)

### **4. Embedded/IoT Systems**
- **Sensor Networks:** Sensor type/protocol (intrinsic), readings/location (extrinsic)
- **Network Protocols:** Packet structure (intrinsic), payload data (extrinsic)
- **Device Management:** Device capabilities (intrinsic), current state (extrinsic)

---

## 🏗️ **Design Decision Framework**

### **Step 1: Analyze Your Objects**
- [ ] How many objects will you create?
- [ ] What data is common across objects?
- [ ] What data is unique per object?
- [ ] Is memory a constraint?

### **Step 2: Identify States**
- [ ] **Intrinsic candidates:** Shared, immutable, context-independent
- [ ] **Extrinsic candidates:** Unique, changeable, context-dependent

### **Step 3: Evaluate Benefits**
- [ ] Will you have many objects with shared data?
- [ ] Is the memory saving significant?
- [ ] Is the complexity overhead worth it?

### **Step 4: Implementation Strategy**
- [ ] Choose key structure for flyweight identification
- [ ] Design factory with appropriate caching mechanism
- [ ] Plan extrinsic state management in client code

---

## ⚠️ **Important Considerations**

### **Advantages**
- ✅ Dramatic memory reduction with many similar objects
- ✅ Better cache performance due to shared data
- ✅ Centralized management of shared resources
- ✅ Immutable flyweights are thread-safe

### **Disadvantages**
- ❌ Increased complexity in design and code
- ❌ Runtime overhead from method calls with extrinsic parameters
- ❌ May introduce coupling between client and flyweight
- ❌ Debugging can be more difficult

### **Performance Trade-offs**
- **Memory:** Significant savings with many objects
- **CPU:** Slight overhead from parameter passing
- **Complexity:** Higher design and maintenance overhead
- **Scalability:** Excellent for large object counts

---

## 🧪 **Testing & Validation**

### **Correctness Tests**
- [ ] Same key returns identical flyweight object (`obj1 == obj2`)
- [ ] Different keys create different flyweight objects
- [ ] Factory cache prevents duplicate creation
- [ ] Extrinsic state operations work correctly

### **Performance Tests**
- [ ] Memory usage measurement (with vs without flyweight)
- [ ] Object creation time comparison
- [ ] Operation performance with extrinsic parameters
- [ ] Factory lookup performance under load

### **Scalability Tests**
- [ ] Behavior with large numbers of objects
- [ ] Factory performance with many flyweight types
- [ ] Memory usage growth patterns
- [ ] Cache hit/miss ratios

---

## 📚 **Key Takeaways**

1. **"Share what you can, parameterize what you can't"** - Core flyweight principle
2. **Memory optimization focus** - Primary benefit is reduced memory usage
3. **Immutable shared state** - Flyweights should be immutable for thread safety
4. **Factory management** - Centralized creation and caching is essential
5. **Context responsibility** - Client manages extrinsic state and flyweight references
6. **Scale-dependent benefits** - Most effective with large numbers of similar objects

---

## 🎯 **Decision Matrix**

Use Flyweight when:
- **Object Count:** Thousands or more
- **Shared Data:** Significant common properties
- **Memory Pressure:** Limited memory environment
- **Immutable State:** Shared data doesn't change
- **Performance:** Memory optimization > CPU optimization

Don't use Flyweight when:
- **Small Scale:** Few objects needed
- **Unique Data:** Mostly unique properties
- **Complexity Cost:** Overhead exceeds benefits
- **Mutable Sharing:** Shared state needs frequent changes

**Remember:** Flyweight is about intelligent memory management through strategic data sharing!
