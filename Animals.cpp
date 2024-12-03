#include <iostream>
#include <vector>
#include <typeinfo>

class Animal {
public:
  Animal (const std::string& name) : name(name) {}
  virtual ~Animal() {}

  virtual void speak() const = 0;

  const std::string& getName() const {
    return name;
  }

private:
  std::string name;
};

class Cat : public Animal {
public:
  Cat (const std::string& name) : Animal(name) {}

  void speak() const override {
    std::cout << "Meow" << '\n';
  }
};

class Dog : public Animal {
public:
  Dog (const std::string& name) : Animal(name) {}

  void speak() const override {
    std::cout << "Woof" << '\n';
  }
};

int countAnimals(const std::vector<Animal*>& animals, const std::type_info& typeInfo) {
  int count = 0;
  for (const Animal* animal : animals) {
    if (typeid(*animal) == typeInfo) {
      count++;
    }
  }
  return count;
}

int main() {
  std::vector<Animal*> animals;
  animals.push_back(new Cat("A"));
  animals.push_back(new Dog("B"));
  animals.push_back(new Cat("C"));

  for (const Animal* animal : animals) {
    animal->speak();
  }

  int numCats = countAnimals(animals, typeid(Cat));
  int numDogs = countAnimals(animals, typeid(Dog));

  std::cout << "number of cats: " << numCats << '\n';
  std::cout << "number of dogs: " << numDogs << '\n';

  for (const Animal* animal : animals) {
    delete animal;
  }

  return 0;
}