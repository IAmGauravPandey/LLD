#include<bits/stdc++.h>
using namespace std;

class User{
    private:
        string username;
        string userId;
        string password;
    public:
        User(string userName,string userId,string password){
            this->userName = userName;
            this->userId = userId;
            this->password = password;
        }
};

class Message{
    private:
        string messageId;
        User sender;
        vector<User> recievers;
        string content;
        string timeStamp;
        bool isEncrypted;
        bool isDelivered;
        bool isRead;
    public:
        Message(string messageId,
        User sender,
        vector<User> recievers,
        string content,
        string timeStamp):messageId(messageId), sender(sender), recievers(recievers),content(content),
        timeStamp(timeStamp),isEncrypted(false),isDelivered(false),isRead(false){}
        
        void marRead(){
            this->isRead = true;
        }
        
        void markDelivered(){
            this->isDelivered = true;
        }
        
        void encryptMessage(){
            this->isEncrypted = true;
        }
};

class MessageManager{
    private:
        vector<Message> sentMessages;
        vector<Message> recievedMessages;
    public:
        MessageManager(){
            this->sentMessages={};
            this->recievedMessages={};
        }
        void sendMessage(Message message){
            // Simulate messange sending
            cout<<"Message: "<<message.messageId<<" Sent\n";
            sentMessages.push_back(message);
        }
        void recieveMessage(Message message){
            cout<<"Message: "<<messageId<<" recieved from user: "<<message.sender.userId<<"\n";
            recievedMessages.push_back(message);
        }
}

int main()
{
    

    return 0;
}
