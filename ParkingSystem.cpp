#include<bits/stdc++.h>
using namespace std;

enum ParkingStatus{
  EMPTY,
  OCUUPIED
};

enum VehicleType{
    BIKE,
    COMPACT,
    LARGE
};

class Vehicle{
    public:
        virtual VehicleType getType() = 0;
        virtual ~Vehicle(){}
};

class Bike: public Vehicle{
    private:
        string bikeNumber;
    public:
        Bike(string number):bikeNumber(number){}
        
        VehicleType getType() override{
            return VehicleType::BIKE;
        }
};

class Car: public Vehicle{
    private:
        string carNumber;
    public:
        Car(string number):carNumber(number){}
        
        VehicleType getType() override{
            return VehicleType::COMPACT;
        }
};

class Slot{
    private:
        VehicleType type;
        int floorNumber;
    public:
        Slot(VehicleType type, int floorNumber):type(type),floorNumber(floorNumber){}
        
        VehicleType getType(){
            return type;
        }
};

class ParkingSlot{
    string slotId;
    string slotNumber;
    ParkingStatus status;
    Slot slot;
    Vehicle* vehicle;
    
    public:
        ParkingSlot(string id, string number, ParkingStatus st, Slot size)
        : slotId(id), slotNumber(number), status(st), slot(size), vehicle(NULL) {}
        
        void parkVehicle(Vehicle* v){
            if(v->getType()==slot.getType()){
                vehicle = v;
                status = OCUUPIED;
            }
            else{
                throw invalid_argument("Parking not possible for this vehicle type in this slot");
            }
        }
        
        void emptySlot(){
            vehicle = NULL;
            status = EMPTY;
        }
        
        VehicleType getType(){
            return slot.getType();
        }
};

class Floor{
    public:
        int floorNumber;
        vector<ParkingSlot*>parkingSlots;
        Floor(int number, string name, vector<ParkingSlot *> slots)
        : floorNumber(number), parkingSlots(slots) {}
};

class Parking{
    public:
        string parkingName;
        vector<Floor*> floors;
        int numberOfFloors;
        vector<map<VehicleType,vector<ParkingSlot*>>>parkingSlotMapping;
        Parking(string parkingName, vector<Floor*>floors){
            this->parkingName = parkingName;
            this->floors = floors;
            this->numberOfFloors = floors.size();
            parkingSlotMapping.resize(numberOfFloors+1);
            for(auto floor:floors){
                for(auto slot:floor->parkingSlots){
                    parkingSlotMapping[floor->floorNumber][slot->getType()].push_back(slot);
                }
            }
        }
        
        void park
};

int main()
{
    

    return 0;
}
