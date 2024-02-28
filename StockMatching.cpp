#include<bits/stdc++.h>
using namespace std;

class Stock{
    public:
        string name;
        string symbol;
        double currentPrice;
        Stock(string name,string symbol,double currentPrice):
        name(name),symbol(symbol),currentPrice(currentPrice){}
};

class Order{
    public:
        string userId;
        int quantity;
        double price;
        bool isBuy;
        Order(string userId,int quantity,double price, bool isBuy):
        userId(userId),quantity(quantity),price(price),isBuy(isBuy){}
        
        bool operator <(const Order& order)const{
            return this->quantity<order.quantity;
        }
        
        bool operator >(const Order& order)const{
            return this->quantity>=order.quantity;
        }
};

class StockOrderBook{
    public:
        Stock stock;
        map<double,deque<Order>>buyOrders;
        map<double,deque<Order>>sellOrders;
        
        StockOrderBook(Stock stock):stock(stock){}
        
        void putOrder(Order order){
            if(order.isBuy)buyOrders[order.price].push_back(order);
            else sellOrders[order.price].push_back(order);
            processOrder();
        }
        
        void processOrder(){
            if(buyOrders.empty() && sellOrders.empty()){
                cout<<"All orders have been processed.\n";
                return;
            }
            if(buyOrders.empty()){
                cout<<"No buyer available.\n";
                return;
            }
            if(sellOrders.empty()){
                cout<<"No seller avaialble.\n";
                return;
            }
            
            auto buyOrderIterator = buyOrders.begin();
            auto sellOrderIterator = sellOrders.begin();
            while(buyOrderIterator!=buyOrders.end() && sellOrderIterator!=sellOrders.end()){
                auto buyQueue = buyOrderIterator->second;
                auto sellQueue = sellOrderIterator->second;
                while(buyQueue.size() && sellQueue.size()){
                    auto buyOrder = buyQueue.front();
                    buyQueue.pop_front();
                    auto sellOrder = sellQueue.front();
                    sellQueue.pop_front();
                    int tradedQuantity = min(buyOrder.quantity,sellOrder.quantity);
                    buyOrder.quantity-=tradedQuantity;
                    sellOrder.quantity-=tradedQuantity;
                    
                    cout<<"Trade happened: "<<tradedQuantity<<" stocks "<<"User: "<<buyOrder.userId<<", bought from "<<"User: "<<sellOrder.userId<<"\n";
                    if(buyOrder.quantity>0){
                        buyQueue.push_front(buyOrder);
                    }
                    if(sellOrder.quantity>0){
                        sellQueue.push_front(sellOrder);
                    }
                }
                if(buyQueue.empty()){
                    buyOrders.erase(buyOrderIterator);
                }
                if(sellQueue.empty()){
                    sellOrders.erase(sellOrderIterator);
                }
                
                buyOrderIterator = buyOrders.begin();
                sellOrderIterator = sellOrders.begin();
            }
        }
};

int main()
{
    Stock stock =  Stock("Uber","Uber",70.00);
    Order order1 = Order("1",2,60.3,true);
    Order order2 = Order("2",3,65.6,true);
    Order order3 = Order("3",6,71.1,false);
    
    StockOrderBook orderBook(stock);
    
    orderBook.putOrder(order1);
    orderBook.putOrder(order2);
    orderBook.putOrder(order3);
    //orderBook.processOrder();

    return 0;
}
