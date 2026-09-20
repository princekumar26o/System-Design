#include <bits/stdc++.h>
using namespace std;

class product {
public:
    string name;
    double price;

    product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

// 1. shoppingcart: only responsible for cart-related business logic
class shoppingcart {
private:
    vector<product*> products;

public:
    void addproduct(product* p) {
        products.push_back(p);
    }

    // Getter for products
    const vector<product*>& getproducts() {
        return products;
    }

    double calculatetotal() {
        double total = 0;

        for (auto p : products) {
            total += p->price;
        }

        return total;
    }
};

// 2. shoppingcartprinter: only responsible for printing invoices
class shoppingcartprinter {
private:
    shoppingcart* cart;

public:
    shoppingcartprinter(shoppingcart* cart) {
        this->cart = cart;
    }

    void printinvoice() {
        cout << "Shopping cart invoice\n";

        for (auto p : cart->getproducts()) {
            cout << p->name << " " << p->price << endl;
        }

        cout << "Total : $" << cart->calculatetotal() << endl;
    }
};

// 3. shoppingcartstorage: only responsible for saving cart
// abstract class

class persistence{
    private:
    shoppingcart *cart;

    public:

    virtual void save(shoppingcart* cart)=0; //pure virtual function

};

class sqlpersistence: public persistence{
    public:

    void save(shoppingcart *cart) override {
       cout<<"saving shopping cart to sql database..."<<endl;
    }
};

class mongopersistence : public persistence{
    public:

    void save(shoppingcart* cart) override{
        cout<<"saving shopping cart to mongo database..."<<endl;
    }
};

class filepersistence : public persistence{
    public:

    void save(shoppingcart* cart) override{
        cout<<"saving shopping cart to file.."<<endl;
    }

};


int main() {

    shoppingcart* cart = new shoppingcart();

    cart->addproduct(new product("laptop", 1000));
    cart->addproduct(new product("mouse", 25));

    shoppingcartprinter* printer = new shoppingcartprinter(cart);
    printer->printinvoice();

    persistence* db=new sqlpersistence();
    persistence* mongo=new mongopersistence();
    persistence* file=new filepersistence();

    db->save(cart);
    mongo->save(cart);
    file->save(cart);


    return 0;
}
