#include<iostream>
#include<vector>

using namespace std;

// product class representing any item in e-commerce

class product{
    public:
    string name;
    double price;

    product(string name,double price){
        this->name=name;
        this->price=price;
    }
};

//1. shopping cart -- only responsible for cart related to business logic

class shoppingcart{
    private:
    vector<product*>products;  // store heap-allocated products

    public:
    void addproduct(product *p){
        products.push_back(p);
    }

    const vector<product*>& getproducts(){
        return products;
    }

    //calculate total price in cart
    double calculatetotal(){
        double total=0;
        for(auto p:products){
            total+=p->price;
        }
        return total;
    }
};

//2. shoppingcart printer: only responsible for printing invoices

class shoppingcartprinter{
    private:
    shoppingcart* cart;

    public:
    shoppingcartprinter(shoppingcart *cart){
        this->cart=cart;
    }

    void printinvoice(){
        cout<<"shopping cart invoice: \n";
        for(auto p:cart->getproducts()){
            cout<<p->name<<" -$"<<p->price<<endl;
        }
    }
};

//3.shoppingcartstorage: only responsible for saving cart to database

class shoppingcartstorage{
    private:
    shoppingcart* cart;

    public:
    shoppingcartstorage( shoppingcart *cart){
        this->cart=cart;
    }
    void savetodatabase(){
        cout<<"Saving shopping cart to database...."<<endl;
    }
};


int main(){
    shoppingcart* cart=new shoppingcart();

    cart->addproduct(new product("laptop",25000));
    cart->addproduct(new product("mouse",250));

    shoppingcartprinter* printer=new shoppingcartprinter(cart);
    printer->printinvoice();

    shoppingcartstorage* db=new shoppingcartstorage(cart);
    db->savetodatabase();

    return 0;

}
