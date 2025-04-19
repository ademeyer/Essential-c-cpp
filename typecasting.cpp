#include <bits/stdc++.h>
using namespace std;

class Animal
{
public:
	virtual void speak(){ cout << "Animal speaks" << endl; }

};

class Dog : public Animal
{
public:
	void speak() override { cout << "Dog barks" << endl; }
};

class Cat : public Animal
{
public:
	void speak() override { cout << "Cat meows" << endl; }
};

int main(int argv, char* argc[])
{
	// Static Typecasting - conventional types casting
	int n = 12;
	void* ptr = &n;
	auto d = static_cast<double>(n);
	auto pt = static_cast<int*>(ptr);
	cout << "typeid: " << typeid(n).name() << endl;
	cout << "typeid: " << typeid(ptr).name() << endl;
	cout << "typeid: " << typeid(d).name() << endl;
	cout << "typeid: " << typeid(pt).name() << endl;
	
	// Dynamic Typecasting - converting downcasting of pointer
	// 			 or reference of a base class to derive class
	// 			 in polymorphisms or inheritance
	Animal* animalPtr = new Dog();	
	// Downcasting
	Dog* dogPtr = dynamic_cast<Dog*>(animalPtr);
	if(!dogPtr)
		cout << "Failed to cast to Dog.\n";
	else
		dogPtr->speak();

	// Typecasting to other derived class
	Cat* catPtr = dynamic_cast<Cat*>(animalPtr);
	if(!catPtr)
		cout << "Failed to cast to Cat.\n";
	else
		catPtr->speak();

	// Free dogPtr
	delete(animalPtr);
	animalPtr = nullptr;

	// Try again with Cat
	animalPtr = new Cat();
        catPtr = dynamic_cast<Cat*>(animalPtr);
        if(!catPtr)
                cout << "Failed to cast to Cat.\n";
        else
                catPtr->speak();
	
	// Free catPtr
	delete(animalPtr);

	// const_cast - use to modify the const or volatile qualifier of 
	// 		a variable. Caution should be exercise while using
	// 		const_cast
	const int p = 5;
	const int* nptr = &p;
	// *nptr = 20; // will likely cause error
	// Remove constancy
	auto nonConstPtr = const_cast<int*>(&p);
	*nonConstPtr = 20;
	cout << "*nonConstPtr = " << *nonConstPtr << endl; // expect 20
	cout << "p = " << p << endl; // expect 5?
	
	// reinterpret_cast -  	it is use to convert a pointer to any other
	// 			type of pointer without performing any check
	// 			whether the pointer converter is of same type
	// 			or not
	int val = 4;
	int* vPtr = &val;

	// Reinterpreting the pointer as a char pointer
	auto charPtr = reinterpret_cast<float*>(vPtr);
	// Printing typeid and memory address
	cout << "typeid: " << typeid(vPtr).name() << " Integer Address: " << vPtr <<  endl;
	cout << "typeid: " << typeid(charPtr).name() << " Float Address: " << charPtr << endl;
	
	return 0;
}
