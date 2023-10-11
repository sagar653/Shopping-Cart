#include<bits/stdc++. h>
using namespace std;


class Item;
class Cart;

class Product{
	int id;
	string name;
	int price;

public:
	Product(){

	}
	Product(int u_id, string name,int price){
		id = u_id;
		this->name = name;
		this->price = price;
	}
	string getDisplayName(){
		return name + " : Rs " + to_string(price) + "\n";
	}
	string getShortName(){
		return name.substr(0,1);
	}
	friend class Item;
	friend class Cart;
};

class Item{
	Product product;
	int quantity;

public:
	//Constructor using a Init List
	Item(){}
	Item(Product p, int q):product(p), quantity(q){}

	int getItemPrice(){
		return quantity * product.price;
	}
	string getItemInfo(){
		return to_string(quantity) + " x " + product.name + " Rs. " + to_string(quantity * product.price) + "\n";
	}

	friend class Cart;
};	


class Cart{
	unordered_map<int,Item>  items;

public:

	void addProduct(Product product){
		if(items.count(product.id)==0){
			Item newItem(product,1);
			items[product.id] = newItem;
		}
		else{
			items[product.id].quantity += 1;
		}
	}

	int getTotal(){
		//Todo
		int total = 0;
		for(auto itemPair : items){
			auto item = itemPair.second;
			total += item.getItemPrice();
		}
		return total;

	}

	string viewCart(){
		if(items.empty()){
			return "Cart is empty";	
		}

		string itemizedList;
		int cart_total = getTotal();

		for(auto itemPair : items){
			auto item = itemPair.second;
			itemizedList.append(item.getItemInfo());
		}

		return itemizedList + "\n Total Amount : Rs. " + to_string(cart_total) + '\n';
	}
	//later on
	bool isEmpty(){
		return items.empty();
	}

};

//Product, Item, Cart
vector<Product> allProducts = {
	Product(1,"apple",26),
	Product(3,"mango",16),
	Product(2,"guava",36),
	Product(5,"banana",56),
	Product(4,"strawberry",29),
	Product(6,"pineapple",20),
};

Product* chooseProduct(){

	//Display the list of products
	string productList;
	cout<<"Available Products "<<endl;

	for(auto product : allProducts){
		productList.append(product.getDisplayName());
	}
	cout << productList <<endl;

	cout<<"----------------"<<endl;
	string choice;
	cin>>choice;

	for(int i=0; i< allProducts.size(); i++){
		if(allProducts[i].getShortName()==choice){
			return &allProducts[i];
		}
	}
	cout<<"Product not found!" <<endl;
	return NULL;
}

bool checkout(Cart &cart){
	if(cart.isEmpty()){
		return false;
	}

	int total = cart.getTotal();
	cout<<"Pay in Cash";

	int paid;
	cin>> paid;

	if(paid>=total){
		cout<<"Change " <<paid - total << endl;
		cout<<"Thank you for shopping!";
		return true;
	}

	else{
		cout<<"Not enough cash!";
		return false;
	}

}

int main(){

	char action;
	Cart cart;

	while(true){
		cout<<"Select an action -  (a)dd item, (v)iew cart, (c)heckout" <<endl;
		cin>> action;

		if(action=='a'){
			//Todo: Add to Cart 
			// View All Products + Choose Product + Add to the Cart 
			Product * product = chooseProduct();
			if(product!=NULL){
				cout<<"Added to the Cart "<<product->getDisplayName() <<endl;
				cart.addProduct(*product);
			}

		}
		else if(action=='v'){
			// View the Cart
			cout<<"------------------" <<endl;
			cout << cart.viewCart();
			cout<<"------------------"<<endl;
		}
		else{
			// Checkout 
			cart.viewCart();
			if(checkout(cart)){
				break;
			}
		}
	}

	return 0;
}
