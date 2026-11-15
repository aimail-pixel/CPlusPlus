#include <iostream>
#include <memory>

// 1. Abstract Products (The Family Members)
class Button {
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void toggle() const = 0;
};

// 2. Concrete Products for Windows
class WinButton : public Button {
public:
    void render() const override { std::cout << "Rendering Windows Button.\n"; }
};

class WinCheckbox : public Checkbox {
public:
    void toggle() const override { std::cout << "Toggling Windows Checkbox.\n"; }
};

// 3. Concrete Products for macOS
class MacButton : public Button {
public:
    void render() const override { std::cout << "Rendering macOS Button.\n"; }
};

class MacCheckbox : public Checkbox {
public:
    void toggle() const override { std::cout << "Toggling macOS Checkbox.\n"; }
};

// 4. Abstract Factory Interface
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// 5. Concrete Factories (Guarantee matching families)
class WinFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WinButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WinCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

// 6. Client Code (Works with any factory via composition)
void renderUI(const GUIFactory& factory) {
    auto btn = factory.createButton();
    auto chk = factory.createCheckbox();
    btn->render();
    chk->toggle();
}

// Usage
int main() {
    WinFactory win_factory;
    renderUI(win_factory); 
    // Output: Rendering Windows Button. / Toggling Windows Checkbox.

    MacFactory mac_factory;
    renderUI(mac_factory); 
    // Output: Rendering macOS Button. / Toggling macOS Checkbox.

    return 0;
}
