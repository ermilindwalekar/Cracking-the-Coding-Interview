#include <iostream>
#include <queue>

using namespace std;

class Animal {
public:
    virtual string getClassName() = 0;

    inline int getOrder() {
        return _order;
    }

    void setOrder(int order) {
        _order = order;
    }

    int setType(string type) {
        _type = type;
    }

    inline string getType() {
        return _type;
    }

    bool Compare(Animal* animal) {
        if (this->_order > animal->_order)
            return true;
        return false;
    }
private:
    int _order;
    string _type;
};

class Cat : public Animal {
public:
    Cat(string name) : _name(name) {
    }

    inline string getClassName() {
        return "Cat";
    }

    inline string getName() {
        return _name;
    }

private:
    string _name;
};

class Dog : public Animal {
public:
    Dog(string name) : _name(name) {
    }

    inline string getClassName() {
        return "Dog";
    }

    inline string getName() {
        return _name;
    }

private:
    string _name;
};

class AnimalQueue {
public:
    void enqueue(Animal* animal) {
        if (animal->getClassName() == "Cat") {
            Cat* d = dynamic_cast<Cat*>(animal);
            if (!d) {
                cout << "\nCasting Error";
            }
            else {
                cout << "\nEnqueued Cat";
                d->setOrder(++queueOrder);
                d->setType(animal->getClassName());
                catQueue.push(d);
            }
        }
        else{

            Dog* d = dynamic_cast<Dog*>(animal);
            if (!d) {
                cout << "\nCasting Error";
            }
            else {
                cout << "\nEnqueued Dog";
                d->setOrder(++queueOrder);
                d->setType(animal->getClassName());
                dogQueue.push(d);
            }
        }
    }
    void dequeue() {
        if (catQueue.empty()) {
            dogQueue.pop();
        }
        if (dogQueue.empty())
        {
            catQueue.pop();
        }
        //Pop with smaller timestamp
        if (catQueue.front()->Compare(dogQueue.front())) {
            dogQueue.pop();
        }
        else {
            catQueue.pop();
        }
    }

    void printQueue() {
        queue<Cat*> cQueue = this->catQueue;
        queue<Dog*> dQueue = this->dogQueue;

        cout << "\nCat Queue\n";
        while (!cQueue.empty()) {
            cout << cQueue.front()->getName() << " ";
            cout << cQueue.front()->getOrder();

            cout << endl;
            cQueue.pop();
        }

        cout << "\nDog Queue\n";
        while (!dQueue.empty()) {
            cout << dQueue.front()->getName() << " ";
            cout << dQueue.front()->getOrder();

            cout << endl;
            dQueue.pop();
        }

    }

    queue<Dog*> getDogQueue() {
        return dogQueue;
    }

    queue<Cat*> getCatQueue() {
        return catQueue;
    }

private:
    queue<Cat*> catQueue;
    queue<Dog*> dogQueue;
    int queueOrder = -1;
};

int main()
{   
    Animal* d1 = new Dog("Max"),*d2 = new Dog ("Shaun"), *d3 = new Dog("Tiger");
    Animal* c1 = new Cat("Trace"), *c2 = new Cat("Han"), *c3 = new Cat("Meow");

    AnimalQueue queue;
    queue.enqueue(d1);
    queue.enqueue(c1);
    queue.enqueue(c2);
    queue.enqueue(d2);
    queue.enqueue(d3);
    queue.enqueue(c3);

    cout << endl;
    queue.printQueue();

    cout << endl;

    queue.dequeue();
    queue.printQueue();
}
