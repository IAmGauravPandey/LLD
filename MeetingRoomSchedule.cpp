#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>

// Meeting class to represent a meeting
class Meeting {
public:
    std::string title;
    std::tm startTime;
    std::tm endTime;

    Meeting(const std::string& title, const std::tm& startTime, const std::tm& endTime)
        : title(title), startTime(startTime), endTime(endTime) {}
};

// MeetingRoom class to represent a meeting room
class MeetingRoom {
public:
    std::string roomName;
    std::vector<Meeting> meetings;

    MeetingRoom(const std::string& roomName) : roomName(roomName) {}

    bool isAvailable(const std::tm& startTime, const std::tm& endTime) const {
        for (const auto& meeting : meetings) {
            if ((startTime >= meeting.startTime && startTime < meeting.endTime) ||
                (endTime > meeting.startTime && endTime <= meeting.endTime) ||
                (startTime <= meeting.startTime && endTime >= meeting.endTime)) {
                return false; // There is a meeting overlapping with the given time
            }
        }
        return true; // Room is available
    }

    void bookMeeting(const std::string& title, const std::tm& startTime, const std::tm& endTime) {
        if (isAvailable(startTime, endTime)) {
            meetings.emplace_back(title, startTime, endTime);
            std::cout << "Meeting booked successfully in " << roomName << " from "
                      << std::put_time(&startTime, "%c") << " to " << std::put_time(&endTime, "%c") << std::endl;
        } else {
            std::cout << "Meeting room is not available for the specified time." << std::endl;
        }
    }

    std::vector<Meeting> getMeetingHistory() const {
        return meetings;
    }
};

// MeetingScheduler class to manage meeting rooms
class MeetingScheduler {
public:
    std::map<std::string, MeetingRoom> meetingRooms;

    MeetingRoom& getMeetingRoom(const std::string& roomName) {
        return meetingRooms[roomName];
    }

    void bookMeeting(const std::string& roomName, const std::string& title, const std::tm& startTime, const std::tm& endTime) {
        MeetingRoom& room = getMeetingRoom(roomName);
        room.bookMeeting(title, startTime, endTime);
    }

    std::vector<Meeting> getMeetingHistory(const std::string& roomName) const {
        const MeetingRoom& room = meetingRooms.at(roomName);
        return room.getMeetingHistory();
    }

    bool isMeetingRoomAvailable(const std::string& roomName, const std::tm& startTime, const std::tm& endTime) const {
        const MeetingRoom& room = meetingRooms.at(roomName);
        return room.isAvailable(startTime, endTime);
    }
};

int main() {
    // Example usage
    MeetingScheduler scheduler;

    scheduler.meetingRooms["RoomA"] = MeetingRoom("RoomA");
    scheduler.meetingRooms["RoomB"] = MeetingRoom("RoomB");

    // Book a meeting in RoomA
    std::tm startTime = {};
    std::tm endTime = {};
    strptime("2023-07-01 10:00:00", "%Y-%m-%d %H:%M:%S", &startTime);
    strptime("2023-07-01 11:30:00", "%Y-%m-%d %H:%M:%S", &endTime);

    scheduler.bookMeeting("RoomA", "Team Meeting", startTime, endTime);

    // Check meeting room availability
    std::tm newStartTime = {};
    std::tm newEndTime = {};
    strptime("2023-07-01 11:00:00", "%Y-%m-%d %H:%M:%S", &newStartTime);
    strptime("2023-07-01 12:00:00", "%Y-%m-%d %H:%M:%S", &newEndTime);

    bool isAvailable = scheduler.isMeetingRoomAvailable("RoomA", newStartTime, newEndTime);
    std::cout << "Is RoomA available for a meeting? " << (isAvailable ? "Yes" : "No") << std::endl;

    // Get meeting history
    std::vector<Meeting> history = scheduler.getMeetingHistory("RoomA");
    std::cout << "Meeting History for RoomA:" << std::endl;
    for (const auto& meeting : history) {
        std::cout << "Title: " << meeting.title << ", Time: "
                  << std::put_time(&meeting.startTime, "%c") << " to " << std::put_time(&meeting.endTime, "%c") << std::endl;
    }

    return 0;
}
``
