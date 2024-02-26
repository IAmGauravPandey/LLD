#include<bits/stdc++.h>
using namespace std;

enum class LogLevel{
    INFO,
    WARN,
    ERROR,
    DEBUG
};

struct LogRecord{
    LogLevel level;
    string message;
};

class Logger{
    public:
        Logger* nextLogger;
        Logger(Logger* logger){
            this->nextLogger = logger;
        }
        virtual void handleLog(const LogRecord& record) = 0;
        
        void log_(const LogRecord& record){
            if(nextLogger){
                nextLogger->handleLog(record);
            }
        }
};

class InfoLogger: public Logger{
    public:
        InfoLogger(Logger* nextLogger): Logger(nextLogger){}
        
        void handleLog(const LogRecord& record) override{
            if(record.level == LogLevel::INFO){
                cout<<"INFO: "<<record.message<<"\n";
            }
            else{
                log_(record);
            }
        }
};

class WarnLogger: public Logger{
    public:
        WarnLogger(Logger* nextLogger): Logger(nextLogger){}
        
        void handleLog(const LogRecord& record) override{
            if(record.level == LogLevel::WARN){
                cout<<"WARN: "<<record.message<<"\n";
            }
            else{
                log_(record);
            }
        }
};

class ErrorLogger: public Logger{
    public:
        ErrorLogger(Logger* nextLogger): Logger(nextLogger){}
        
        void handleLog(const LogRecord& record) override{
            if(record.level == LogLevel::ERROR){
                cout<<"ERROR: "<<record.message<<"\n";
            }
            else{
                log_(record);
            }
        }
};

int main()
{
    ErrorLogger errorProcessor(nullptr);
    WarnLogger debugProcessor(&errorProcessor);
    InfoLogger infoProcessor(&debugProcessor);

    // Log some messages
    infoProcessor.handleLog({LogLevel::INFO, "Application started"});
    infoProcessor.handleLog({LogLevel::WARN, "Debug information"});
    infoProcessor.handleLog({LogLevel::ERROR, "An error occurred"});

    return 0;
}
