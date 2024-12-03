#include <bits/stdc++.h>

using namespace std;

class Product{
public:
  Product(string name, int singlePrice, bool hasDiscount, int discountQuantity, int discountPrice) {
    this->name = name;
    this->singlePrice = singlePrice;
    this->hasDiscount = hasDiscount;
    this->discountQuantity = discountQuantity;
    this->discountPrice = discountPrice;
  }

  string getName() {
    return name;
  }

  int getPrice(int numberOfPurchase) {
    if (!hasDiscount) {
      return singlePrice;
    }
    if (numberOfPurchase % discountQuantity == 0) {
      return discountPrice - (discountQuantity - 1) * singlePrice;
    }
    return singlePrice;
  }

private:  
  string name;
  int singlePrice;
  bool hasDiscount;
  int discountQuantity;
  int discountPrice;
};

class Cashier{
public:
  Cashier() {
    currentTotal = 0;
  }

  int getCurrentTotal() {
    return currentTotal;
  }

  void checkout(Product product) {
    int countCheckedOut = countProducts(product);
    int price = product.getPrice(countCheckedOut + 1);
    addToCurrentTotal(price);
    addToProductsList(product);
  }

private:
  int currentTotal;
  vector<Product> productsCheckedOut;

  void addToCurrentTotal(int price) {
    currentTotal += price;
    return;
  }

  void addToProductsList(Product product) {
    productsCheckedOut.push_back(product);
    return;
  }

  int countProducts(Product product) {
    int count = 0;
    for (int i = 0; i < productsCheckedOut.size(); i++) {
      if (product.getName() == productsCheckedOut[i].getName()) {
        count++;
      }
    }
    return count;
  }
};

int main() {
  Product A = Product("A", 5, true, 3, 13);
  Product B = Product("B", 4, true, 2, 7);
  Product C = Product("C", 3, false, 0, 0);
  
  Cashier cashier = Cashier();
  cashier.checkout(A);
  cout << cashier.getCurrentTotal() << '\n';
  cashier.checkout(A);
  cout << cashier.getCurrentTotal() << '\n';
  cashier.checkout(B);
  cout << cashier.getCurrentTotal() << '\n';
  cashier.checkout(C);
  cout << cashier.getCurrentTotal() << '\n';
  cashier.checkout(A);
  cout << cashier.getCurrentTotal() << '\n';
  cashier.checkout(B);
  cout << cashier.getCurrentTotal() << '\n';
  return 0;
}

// Product  |Single Price |Discount Quantity |Discount Price
// A            5              3               13
// B            4              2               7
// C            3              -               -
// Implement a cashier checkout system, scan items 1 by 1 and print current total
// Test Case [A,A,B,C,A,B] -> [5,10,14,17,20,23]
