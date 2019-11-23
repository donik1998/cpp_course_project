#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<process.h>

using namespace std;

//variables
fstream loging, receipt, roomDatabasefile, featuresDatabaseFile;
time_t rawtime;
struct tm *timeinfo;
char accepted; int stayDays;
string id, first_name, last_name, full_name;
bool GlobalBill = false;
string fur_name[4] = { "Comode", "Wardrobe", "Armchair", "Mini-bar" };
string eq_name[4] = { "TV", "Fridge", "Air conditioner", "Laptop" };
string serv_name[7] = { "Morning meal", "Laundry", "Additional cleaning", "Gym", "Guide", "Transport renting", "Taxi from airport to hotel" };
float eq_rent_price[4] = { 15.59, 10.25, 20.85, 45.0 };
float fur_rent_price[4] = { 9.85, 16.60, 12.20, 45.50 };
float serv_price[7] = { 13.45, 14.50, 11.5, 21.5, 35.50, 49.99, 15.85 };
string roomsDatabase[51][20];
bool featuresDatabase[50][16];
int checkInTime[50];
//variables

/*
	******************HINTS**************************
	featuresArray[0][1] = furniture_name[0]; featuresArray[0][2] = furniture_name[1];
	featuresArray[0][3] = furniture_name[2]; featuresArray[0][4] = furniture_name[3];
	featuresArray[0][5] = equipment_name[0]; featuresArray[0][6] = equipment_name[1];
	featuresArray[0][7] = equipment_name[2]; featuresArray[0][8] = equipment_name[3];
	featuresArray[0][9] = services_name[0]; featuresArray[0][10] = services_name[1];
	featuresArray[0][11] = services_name[2]; featuresArray[0][12] = services_name[3];
	featuresArray[0][13] = services_name[4]; featuresArray[0][14] = services_name[5];
	featuresArray[0][15] = services_name[6];
	*/
//classes

class Stack {
private:
	int top;
	#define MAX 1000
	int a[MAX];
public:
	Stack() { top = -1; }
	bool push(int entry) {
		if (top >= (MAX - 1)) {
			cout << "Stack overflow\n";
			return false;
		}
		else {
			a[++top] = entry;
			//cout statement to make sure wright character has been pusehed to stack
			//cout << "Element " << entry << " " << "A.K.A " << char(entry) << " is pushed to stack\n";
			return true;
		}
	}
	int pop() {
		if (top < 0) {
			cout << "Stack Underflow" << endl;
			return 0;
		}
		else {
			int x = a[top--];
			return x;
		}
	}
	bool isEmpty() {
		if (top < 0) {
			return true;
		}
		else { return false; }
	}
	void getStack() {
		for (int i = 0; i < MAX; i++) {
			cout << i + 1 << ". " << a[i] << endl;
		}
	}
};
class Guest{
private:
	string guest_name, guest_identification_number;
public:
	void set_guest_name(string name){
		guest_name = name;
	}
	void set_guest_identification(string id){
		guest_identification_number = id;
	}
	string get_guest_name(){
		return guest_name;
	}
	string get_guest_identification(){
		return guest_identification_number;
	}
};
class Conveniences{
private:
	string equipment_name[4], furniture_name[4];
	bool eq_rent_status[4], fur_rent_status[4];
public:
	void set_equipment_status(string name, bool value) {
		for (int i = 0; i < 4; i++) {
			if (this->equipment_name[i] == name) {
				eq_rent_status[i] = value;
			}
		}
	}
	void set_conveniences_names() {
		for(int i = 0; i < 4; i++) {
			this->equipment_name[i] = eq_name[i];
			this->furniture_name[i] = fur_name[i];
		}
	}
	void set_furniture_status(string name, bool value) {
		for (int i = 0; i < 4; i++) {
			if (this->furniture_name[i] == name) {
				fur_rent_status[i] = value;
			}
		}
	}
	void add_furniture(string name){
		for (int i = 0; i < 4; i++){
			if (furniture_name[i] == name){
				cout << "Furniture is added to your bill" << endl;
				fur_rent_status[i] = true;
				break;
			}
			else{ continue; }
		}
	}
	bool get_furniture_status(string name){
		for (int i = 0; i < 4; i++){
			if (furniture_name[i] == name){
				return fur_rent_status[i];
				break;
			}
			else{ continue; }
		}
	}
	void add_equipment(string name){
		for (int i = 0; i < 4; i++){
			if (equipment_name[i] == name){
				cout << "Equipment is added to your bill" << endl;
				eq_rent_status[i] = true;
				break;
			}
			else{ continue; }
		}
	}
	bool get_equipment_status(string name){
		for (int i = 0; i < 4; i++){
			if (equipment_name[i] == name){
				return eq_rent_status[i]; break;
			}
			else
			{
				continue;
			}
		}
	}
};
class Additional_Services{
private:
	string services[7];
	bool service_status[7];
public:
	void set_services_names() {
		for (int i = 0; i < 7; i++) {
			services[i] = serv_name[i];
		}
	}
	void set_services_status(string name, bool value) {
		for (int i = 0; i < 7; i++) {
			if (services[i] == name) {
				services[i] = value;
			}
		}
	}
	float get_service_price(string name){
		for (int i = 0; i < 7; i++){
			if (services[i] == name && service_status[i] == true){
				return serv_price[i];
				break;
			}
			else{ continue; }
		}
	}
	void add_service(string name){
		for (int i = 0; i < 7; i++){
			if (services[i] == name){
				service_status[i] = true;
				break;
			}
			else{ continue; }
		}
	}
	bool get_service_status(string name){
		for (int i = 0; i < 7; i++){
			if (services[i] == name){
				return service_status[i]; break;
			}
			else{ continue; }
		}
	}
};
class Rooms : public virtual Guest, public virtual Conveniences, public virtual Additional_Services{
private:
	int room_level, room_number, capacity, rent_days, room_price;
	string room_type;
	bool availability;
public:
	void addDaysStayed(int add_days) {
		rent_days += add_days;
	}
	void set_roomlevel(int lvl){
		room_level = lvl;
	}
	void set_roomNumber(int num) {
		room_number = num;
	}
	void set_capacity(int numberofguests){
		capacity = numberofguests;
	}
	int get_capacity(){
		return capacity;
	}
	int get_roomlvl(){
		return room_level;
	}
	int get_room_number(){
		return room_number;
	}
	void set_room_type(string type){
		room_type = type;
	}
	void set_rent_days(int days){
		rent_days = days;
	}
	int get_rent_days(){
		return rent_days;
	}
	string get_room_type(){
		return room_type;
	}
	void set_availability(bool av){
		availability = av;
	}
	bool get_availability(){
		return availability;
	}
	void set_room_price(int price){
		room_price = price;
	}
	int get_room_price(){
		return room_price;
	}
	~Rooms(){
		cout << "Room is freed for other guests\n";
		set_availability(true);
	}
};
//classes

//functions declaration
int stringToInt(string entry);
void initialize(string roomsdataArray[51][20], bool featuresArray[50][16]);
void add_furniture(Rooms r[50], string id);
void add_equipment(Rooms r[50], string id);
void add_services(Rooms r[50], string id);
void add_features(Rooms r[50], string id);
void bill(Rooms r[50], string id);
string CheckMyString(string entry);
void GuestRegister(Rooms r[50], int NumberOfGuests, string RoomType);
string getColumnInfo(string allColumns, int startingPoint);
bool stringToBoolean(char entry);
int resizeRate(int currentCol, string entry);
void initializeRoomDatabaseFromFile(string roomData[51][20]);
void initializeFeaturesDatabaseFromFile(bool featuresData[50][16]);
char getBooleanColumnInfo(string allColumns, int columnnumber);
string getCleanBooleans(string entry);
void addToDatabase(Rooms r[50], string roomDatabase[51][20], int indexOfObject);
string booleanToString(bool entry);
void pushToRoomsDatabase(string roomData[51][20]);
void pushToFeaturesDatabase(bool featuresData[50][16]);
void removeFromRoomsDatabase(Rooms r[50], string roomData[51][20], int indexOfObjects);
void calculateDaysLeft(int indexOfObject, int timeStamps[50]);
//functions declaration

//functions

void pushToRoomsDatabase(string roomData[51][20]) {
	roomDatabasefile.open("RoomsDatabase.txt", ios::out);
	if (roomDatabasefile.is_open()) {
		for (int i = 0; i <= 50; i++) {
			for (int j = 0; j < 20; j++) {
				roomDatabasefile << roomData[i][j] << "|";
			}
			roomDatabasefile << endl;
		}
	}
	else { cout << "Filestream is closed\n"; }
	roomDatabasefile.close();
}
void pushToFeaturesDatabase(bool featuresData[50][16]) {
	featuresDatabaseFile.open("FeaturesDatabase.txt", ios::out);
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 16; j++) {
			featuresDatabaseFile << featuresData[i][j] << "|";
		}
		featuresDatabaseFile << endl;
	}
	featuresDatabaseFile.close();
}
int stringToInt(string entry) {
	int temp;
	temp = stoi(entry);
	return temp;
}
bool stringToBoolean(char entry) {
	if (entry == '0') {
		return false;
	}
	else if (entry == '1') {
		return true;
	}
	else { cout << "Wrong entry value!!!\n"; }
}
string booleanToString(bool entry) {
	if (entry == true) { return "1"; }
	else { return"0"; }
}
int resizeRate(int currentCol, string entry) {
	int resizeValue = 0, currCol = currentCol;
	for (int i = 0; i < entry.length(); i++) {
		if (entry[i] != '|') {
			resizeValue++;
		}
		else {
			resizeValue = 0;
			currCol--;
		}
		if (currCol <= 0 && entry[i + 1] == '|') {
			return resizeValue;
		}
	}
	return resizeValue;
}
void initialize(string roomsdataArray[51][20], bool featuresArray[50][16]) {
	roomsdataArray[0][1] = "Availability"; roomsdataArray[0][2] = "Capacity";
	roomsdataArray[0][3] = "Number"; roomsdataArray[0][4] = "Level";
	roomsdataArray[0][5] = "Room type";	roomsdataArray[0][6] = "Rent days";
	roomsdataArray[0][7] = "Room price"; roomsdataArray[0][8] = "Guest name";
	roomsdataArray[0][9] = "Guest ID";
	//loop to initialize room's database
	for (int a = 1; a < 51; a++) {
		for (int i = 1; i <= 20; i++) {
			//ordinal rooms for a single guest
			if (a >= 1 && a <= 10) {
				if (roomsdataArray[0][i] == "Availability") {
					roomsdataArray[a][i] = to_string(true);
				}
				if (roomsdataArray[0][i] == "Capacity") {
					roomsdataArray[a][i] = to_string(1);
				}
				if (roomsdataArray[0][i] == "Number") {
					roomsdataArray[a][i] = to_string(a);
				}
				if (roomsdataArray[0][i] == "Level") {
					roomsdataArray[a][i] = to_string(1);
				}
				if (roomsdataArray[0][i] == "Room type") {
					roomsdataArray[a][i] = "Ordinal";
				}
				if (roomsdataArray[0][i] == "Rent days") {
					roomsdataArray[a][i] = to_string(0);
				}
				if (roomsdataArray[0][i] == "Room price") {
					roomsdataArray[a][i] = to_string(12);
				}
				if (roomsdataArray[0][i] == "Guest name") {
					roomsdataArray[a][i] = "blank";
				}
				if (roomsdataArray[0][i] == "Guest ID") {
					roomsdataArray[a][i] = "blank%";
				}
			}
			//ordinal rooms for two guests
			if (a > 10 && a <= 20) {
				if (roomsdataArray[0][i] == "Availability") {
					roomsdataArray[a][i] = to_string(true);
				}
				if (roomsdataArray[0][i] == "Capacity") {
					roomsdataArray[a][i] = to_string(2);
				}
				if (roomsdataArray[0][i] == "Number") {
					roomsdataArray[a][i] = to_string(a);
				}
				if (roomsdataArray[0][i] == "Level") {
					roomsdataArray[a][i] = to_string(2);
				}
				if (roomsdataArray[0][i] == "Room type") {
					roomsdataArray[a][i] = "Ordinal";
				}
				if (roomsdataArray[0][i] == "Rent days") {
					roomsdataArray[a][i] = to_string(0);
				}
				if (roomsdataArray[0][i] == "Room price") {
					roomsdataArray[a][i] = to_string(25);
				}
				if (roomsdataArray[0][i] == "Guest name") {
					roomsdataArray[a][i] = "blank";
				}
				if (roomsdataArray[0][i] == "Guest ID") {
					roomsdataArray[a][i] = "blank%";
				}
			}
			//advanced rooms for three guests
			if (a > 20 && a <= 30) {
				if (roomsdataArray[0][i] == "Availability") {
					roomsdataArray[a][i] = to_string(true);
				}
				if (roomsdataArray[0][i] == "Capacity") {
					roomsdataArray[a][i] = to_string(3);
				}
				if (roomsdataArray[0][i] == "Number") {
					roomsdataArray[a][i] = to_string(a);
				}
				if (roomsdataArray[0][i] == "Level") {
					roomsdataArray[a][i] = to_string(3);
				}
				if (roomsdataArray[0][i] == "Room type") {
					roomsdataArray[a][i] = "Advanced";
				}
				if (roomsdataArray[0][i] == "Rent days") {
					roomsdataArray[a][i] = to_string(0);
				}
				if (roomsdataArray[0][i] == "Room price") {
					roomsdataArray[a][i] = to_string(50);
				}
				if (roomsdataArray[0][i] == "Guest name") {
					roomsdataArray[a][i] = "blank";
				}
				if (roomsdataArray[0][i] == "Guest ID") {
					roomsdataArray[a][i] = "blank%";
				}
			}
			//lux rooms for four guests
			if (a > 30 && a <= 40) {
				if (roomsdataArray[0][i] == "Availability") {
					roomsdataArray[a][i] = to_string(true);
				}
				if (roomsdataArray[0][i] == "Capacity") {
					roomsdataArray[a][i] = to_string(4);
				}
				if (roomsdataArray[0][i] == "Number") {
					roomsdataArray[a][i] = to_string(a);
				}
				if (roomsdataArray[0][i] == "Level") {
					roomsdataArray[a][i] = to_string(4);
				}
				if (roomsdataArray[0][i] == "Room type") {
					roomsdataArray[a][i] = "Lux";
				}
				if (roomsdataArray[0][i] == "Rent days") {
					roomsdataArray[a][i] = to_string(0);
				}
				if (roomsdataArray[0][i] == "Room price") {
					roomsdataArray[a][i] = to_string(100);
				}
				if (roomsdataArray[0][i] == "Guest name") {
					roomsdataArray[a][i] = "blank";
				}
				if (roomsdataArray[0][i] == "Guest ID") {
					roomsdataArray[a][i] = "blank%";
				}
			}
			//advanced lux rooms for six guests
			if (a > 40 && a <= 50) {
				if (roomsdataArray[0][i] == "Availability") {
					roomsdataArray[a][i] = to_string(true);
				}
				if (roomsdataArray[0][i] == "Capacity") {
					roomsdataArray[a][i] = to_string(6);
				}
				if (roomsdataArray[0][i] == "Number") {
					roomsdataArray[a][i] = to_string(a);
				}
				if (roomsdataArray[0][i] == "Level") {
					roomsdataArray[a][i] = to_string(5);
				}
				if (roomsdataArray[0][i] == "Room type") {
					roomsdataArray[a][i] = "Advanced lux";
				}
				if (roomsdataArray[0][i] == "Rent days") {
					roomsdataArray[a][i] = to_string(0);
				}
				if (roomsdataArray[0][i] == "Room price") {
					roomsdataArray[a][i] = to_string(200);
				}
				if (roomsdataArray[0][i] == "Guest name") {
					roomsdataArray[a][i] = "blank";
				}
				if (roomsdataArray[0][i] == "Guest ID") {
					roomsdataArray[a][i] = "blank%";
				}
			}
		}
	}
	//output rooms data to file
	pushToRoomsDatabase(roomsdataArray);
	//output features data to file
	pushToFeaturesDatabase(featuresArray);
}
void add_furniture(Rooms r[50], string id){
	int counter = 1, furnutire_choice = 1;
	bool found;
	for (int i = 0; i < 50; i++){
		if (r[i].get_guest_identification() == id && r[i].get_availability() == false){
			found = true;
			while (furnutire_choice != 0){
				cout << "We can provide you with " << endl;
				for (int j = 0; j < 4; j++){
					cout << counter << ". " << fur_name[j] << endl;
					counter++;
				}counter = 1;
				cout << endl << "0 - Back" << endl << "Your choice: "; cin >> furnutire_choice;
				if (furnutire_choice>4 || furnutire_choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (furnutire_choice){
				case(1) : {
					r[i].add_furniture(fur_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << fur_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(2) : {
					r[i].add_furniture(fur_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << fur_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(3) : {
					r[i].add_furniture(fur_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << fur_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(4) : {
					r[i].add_furniture(fur_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << fur_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				}
			}
		}
		else if (r[i].get_guest_identification() != id || r[i].get_availability() == true){ found = false; continue; }
		else{
			cout << "You are not registred" << endl;
			found = false;
		}
	}
	if (found == false){
		cout << "Not found" << endl;
	}
}
void add_equipment(Rooms r[50], string id){
	int counter = 1, equipment_choice = 1;
	bool found;
	for (int i = 0; i < 50; i++){
		if (r[i].get_guest_identification() == id && r[i].get_availability() == false){
			found = true;
			while (equipment_choice != 0){
				cout << "We can provide you with" << endl;
				for (int j = 0; j < 4; j++){
					cout << counter << ". " << eq_name[j] << endl;
					counter++;
				}counter = 1;
				cout << endl << "0 - Back" << endl;
				cout << "So what is your choice: "; cin >> equipment_choice;
				if (equipment_choice>4 || equipment_choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (equipment_choice){
				case(1) : {
					r[i].add_equipment(eq_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << eq_name[equipment_choice- 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(2) : {
					r[i].add_equipment(eq_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << eq_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(3) : {
					r[i].add_equipment(eq_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << eq_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(4) : {
					r[i].add_equipment(eq_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << eq_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				}
			}
		}
		else if (r[i].get_guest_identification() != id || r[i].get_availability() == true){
			found = false; continue;
		}
		else{
			cout << "You are not registered" << endl;
			found = false;
		}
	}
	if (found == false){
		cout << "Not found" << endl;
	}
}
void add_services(Rooms r[50], string id){
	int counter = 1, feature_choice = 1;
	bool found = true;
	for (int i = 0; i < 50; i++){
		if (r[i].get_guest_identification() == id && r[i].get_availability() == false){
			found = true;
			while (feature_choice != 0){
				cout << "We can provide you with" << endl;
				for (int j = 0; j < 7; j++){
					cout << counter << ". " << serv_name[j] << endl;
					counter++;
				}counter = 1;
				cout << "0 - Back" << endl << "So your choice is: "; cin >> feature_choice;
				if (feature_choice>7 || feature_choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (feature_choice){
				case(1) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice- 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(2) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(3) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(4) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(5) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(6) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(7) : {
					r[i].add_service(serv_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << serv_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				}
			}
		}
		else if (r[i].get_guest_identification() != id || r[i].get_availability() == true){
			found = false; continue;
		}
		else{
			cout << "You are not registered" << endl;
		}
	}
	if (found == false) {
		cout << "Not found" << endl;
	}
}
void add_features(Rooms r[50], string id){
	int choice = 1;
	bool found;
	for (int i = 0; i < 50; i++){
		if (r[i].get_guest_identification() == id && r[i].get_availability() == false){
			found = true;
			while (choice != 0){
				cout << "So what kind of features are you going to add?" << endl;
				cout << "1. Furniture" << endl << "2. Equipment" << endl << "3. Services" << endl << endl << "0 - Back" << endl;
				cout << "Your choice is "; cin >> choice;
				if (choice>3 || choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (choice){
				case(1) : {
							  loging.open("Data.txt", ios::app);
							  loging << ctime(&rawtime);
							  add_furniture(r, id);
							  loging.close();
							  break;
				}
				case(2) : {
							  loging.open("Data.txt", ios::app);
							  loging << ctime(&rawtime);
							  add_equipment(r, id);
							  loging.close();
							  break;
				}
				case(3) : {
							  loging.open("Data.txt", ios::app);
							  loging << ctime(&rawtime);
							  add_services(r, id);
							  loging.close();
							  break;
				}
				}
			}
		}
		else if (r[i].get_guest_identification() != id || r[i].get_availability() == true){
			found = false;
			continue;
		}
		else{
			cout << "You are not redistered" << endl;
			found = false;
		}
	}
	if (found == false){
		cout << "Not found" << endl;
	}
}
void bill(Rooms r[50], string id) {
	float total = 0; string tempName;
	receipt << "\t\t\tPayment details\n";
	for (int i = 0; i < 50; i++) {
		if (receipt.is_open() == true) {
			if (r[i].get_availability() == false && r[i].get_guest_identification() == id) {
				GlobalBill = true;
				cout << "Alright! " << r[i].get_guest_name() << endl;
				tempName = r[i].get_guest_name();
				cout << "You have lived in " << r[i].get_room_type() << " number " << r[i].get_room_number() << " on " << r[i].get_roomlvl() << " floor for " << r[i].get_rent_days() << " days" << endl;
				cout << "It costs " << r[i].get_room_price() << "$ per day. So you have to pay " << r[i].get_rent_days()*r[i].get_room_price() << "$ for room rent" << endl;
				total += (r[i].get_rent_days()*r[i].get_room_price());
				receipt << "Room for " << r[i].get_rent_days() << " days: " << total << "$" << endl;
				for (int j = 0; j < 4; j++) {
					if (r[i].get_furniture_status(fur_name[j]) == true) {
						cout << "You also rented " << fur_name[j] << " for " << fur_rent_price[j] << "$" << endl;
						receipt << fur_name[j] << ": " << fur_rent_price[j] << "$" << endl;
						total += fur_rent_price[j];
					}
					if (r[i].get_equipment_status(eq_name[j]) == true) {
						cout << "You also rented " << eq_name[j] << " for " << eq_rent_price[j] << "$" << endl;
						receipt << eq_name[j] << ": " << eq_rent_price[j] << "$" << endl;
						total += eq_rent_price[j];
					}
				}
				for (int k = 0; k < 7; k++) {
					if (r[i].get_service_status(serv_name[k]) == true) {
						cout << "You also ordered " << serv_name[k] << " for " << serv_price[k] << endl;
						receipt << serv_name[k] << ": " << serv_price[k] << "$" << endl;
						total += serv_price[k];
					}
				}
			}
		}else {
			cout << "File is closed!!!" << endl;
		}
	}
	receipt << "Name: " << tempName << endl;
	receipt << "Amount: " << total << "$" << endl;
	receipt << "**********Thank you for choosing us**********" << endl;
}
string CheckMyString(string entry) {
	for (int a = 0; a < entry.length(); a++) {
		if ((int(entry[a] >= 65) && int(entry[a] <= 90)) || (int(entry[a]) >= 97 && int(entry[a] <= 122))) {
			continue;
		}
		else {
			cout << "You can't have such first name as " << entry;
			cout << " Re-enter your First Name: "; cin >> entry;
			a = -1;
		}
	}
	return entry;
}//function to check names for incorect symbols
void GuestRegister(Rooms r[50], int NumberOfGuests, string RoomType) {
	for (int i = 0; i < 50; i++) {
		if (r[i].get_availability() == true && r[i].get_capacity() >= NumberOfGuests && r[i].get_room_type() == RoomType) {
			cout << "We can offer you room number " << r[i].get_room_number() << " on " << r[i].get_roomlvl() << " floor" << endl;
			cout << "This room is designed for " << r[i].get_capacity() << " guest(s)" << endl << "And costs " << r[i].get_room_price() << "$ per day" << endl;
			cout << "Will you take it?(y/n)" << endl << "Your answer: "; cin >> accepted;
			if (accepted == 'y' || accepted == 'Y') {
				cout << "Great! Let's register you" << endl;
				cout << "For this we need following information\n";
				cout << "First Name: "; cin >> first_name;
				first_name = CheckMyString(first_name);
				cout << "Last Name: "; cin >> last_name;
				last_name = CheckMyString(last_name);
				full_name = first_name + " " + last_name;
				cout << "Your identification number (passport ID): "; cin >> id;
				cout << "How many days are you going to stay?" << endl; cin >> stayDays;
				cout << "OK! " << r[i].get_room_type() << " room number " << r[i].get_room_number() << " is reserved for "
					<< full_name << " for " << stayDays << " days" << endl;
				r[i].set_availability(false);
				r[i].set_rent_days(stayDays);
				r[i].set_guest_identification(id);
				r[i].set_guest_name(full_name);
				loging.open("Data.txt", ios::ate | ios::out);
				loging << ctime(&rawtime) << ": " << full_name << " is registered in room number " << r[i].get_room_number() << " for " << stayDays << " days" << endl;
				loging.close();
				checkInTime[i] = time(&rawtime);
				addToDatabase(r, roomsDatabase, i);
				break;
			}
			else if (accepted == 'n' || accepted == 'N') {
				cout << "OK! Let's see other option" << endl;
			}
			else {
				cout << "Wrong input" << endl;
				i--;
			}	
		}
	}
}
void addToDatabase(Rooms r[50], string roomDatabase[51][20], int indexOfObject) {
	for (int j = 1; j < 10; j++) {
		switch (j) {
			//Availability
		case(1): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = booleanToString(r[indexOfObject].get_availability());
			break;
		}
				 //Capacity
		case(2): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = to_string(r[indexOfObject].get_capacity());
			break;
		}
				 //Number
		case(3): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = to_string(r[indexOfObject].get_room_number());
			break;
		}
				 //level
		case(4): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = to_string(r[indexOfObject].get_roomlvl());
			break;
		}
				 //room type
		case(5): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = r[indexOfObject].get_room_type();
			break;
		}
				 //rent days
		case(6): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = to_string(r[indexOfObject].get_rent_days());
			break;
		}
				 //room price
		case(7): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = to_string(r[indexOfObject].get_room_price());
			break;
		}
				 //guest name
		case(8): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = r[indexOfObject].get_guest_name();
			break;
		}
				 //guest ID
		case(9): {
			cout << "This is case " << j << endl;
			roomDatabase[indexOfObject + 1][j] = r[indexOfObject].get_guest_identification();
			break;
		}
		}

	}
	pushToRoomsDatabase(roomDatabase);
}
string getColumnInfo(string allColumns, int columnNumber) {
	string currentCommand;
	int tempCounter = resizeRate(columnNumber, allColumns), tempCol = columnNumber;
	Stack stack;
	currentCommand.clear(); currentCommand.resize(resizeRate(columnNumber, allColumns) + 1);
	for (int i = 1; i < allColumns.length(); i++) {
		if (allColumns[i] == '|') {
			tempCol--;
			while (tempCounter > 0 && !stack.isEmpty() && tempCol == 0) {
				currentCommand[tempCounter] = char(stack.pop());
				tempCounter--;
			}
		}
		if (allColumns[i] != '|') {
			stack.push(int(allColumns[i]));
		}
	}
	reverse(currentCommand.begin(), currentCommand.end());
	for (int i = 0; i < currentCommand.length(); i++) {
		if (currentCommand[i] == '\0') { 
			currentCommand.resize(i);
		}
	}
	reverse(currentCommand.begin(), currentCommand.end());
	return currentCommand;
}
char getBooleanColumnInfo(string allColumns, int columnNumber) {
	string tempColumn; tempColumn.resize(allColumns.length() / 2);
	int tempColumnIndex = 0;
	for (int i = 0; i < allColumns.length(); i++) {
		if (tempColumnIndex + 1 == tempColumn.length()) { break; }
		if (allColumns[i] != '|') {
			tempColumn[tempColumnIndex] = allColumns[i];
			tempColumnIndex++;
		}
	}
	return tempColumn[columnNumber];
}
void initializeRoomDatabaseFromFile(string roomData[51][20]) {
	string currentEntries;
	Stack stack;
	roomDatabasefile.open("RoomsDatabase.txt", ios::in);
	if (roomDatabasefile.is_open()) {
		getline(roomDatabasefile, currentEntries);
		// set headings first
		for (int cols = 1; cols < 20; cols++) {
			roomData[0][cols] = getColumnInfo(currentEntries, cols);
		}
		for (int row = 1; row <= 50; row++) {
			getline(roomDatabasefile, currentEntries);
			for (int j = 1; j < 20; j++) {
				if (j == 10) { break; }
				roomData[row][j] = getColumnInfo(currentEntries, j);
			}
		}
	}
	else { cout << "Filestream is closed\n"; }
	roomDatabasefile.close();
}
void initializeFeaturesDatabaseFromFile(bool featuresData[50][16]) {
	featuresDatabaseFile.open("FeaturesDatabase.txt", ios::in);
	string currentEntries; Stack stack;
	for (int row = 0; row < 50; row++) {
		getline(featuresDatabaseFile, currentEntries);
		for (int col = 0; col < 16; col++) {
			featuresData[row][col] = stringToBoolean(getBooleanColumnInfo(currentEntries, 0));
		}
	}
	featuresDatabaseFile.close();
}
void initializeRoomsArray(Rooms r[50], string roomData[51][20], bool featuresData[50][16]) {
	//to initialize rooms data
	roomDatabasefile.open("RoomsDatabase.txt", ios::in);
	featuresDatabaseFile.open("FeaturesDatabase.txt", ios::in);
	int counter = 0;
	if (roomDatabasefile.is_open() && featuresDatabaseFile.is_open()) {
		for (int j = 1; j <= 50; j++) {
			for (int a = 1; a <= 9; a++) {
				if (roomData[0][a] == "Availability") {
					r[counter].set_availability(stringToBoolean(roomData[j][a][0]));
				}
				else if (roomData[0][a] == "Capacity") {
					r[counter].set_capacity(stringToInt(roomData[j][a]));
				}
				else if (roomData[0][a] == "Number") {
					r[counter].set_roomNumber(stringToInt(roomData[j][a]));
				}
				else if (roomData[0][a] == "Level") {
					r[counter].set_roomlevel(stringToInt(roomData[j][a]));
				}
				else if (roomData[0][a] == "Room type") {
					r[counter].set_room_type(roomData[j][a]);
				}
				else if (roomData[0][a] == "Rent days") {
					r[counter].set_rent_days(stringToInt(roomData[j][a]));
				}
				else if (roomData[0][a] == "Room price") {
					r[counter].set_room_price(stringToInt(roomData[j][a]));
				}
				else if (roomData[0][a] == "Guest name") {
					r[counter].set_guest_name(roomData[j][a]);
				}
				else if (roomData[0][a] == "Guest ID") {
					r[counter].set_guest_identification(roomData[j][a]);
				}
				else {
					cout << "Couldn't find corresponding information\n";
				}
			}
			counter++;
		}
		//to initialize features data
		for (int i = 0; i < 50; i++) {
			r[i].set_conveniences_names();
			r[i].set_services_names();
			for (int j = 0; j < 16; j++) {
				for (int a = 0; a < 7; a++) {
					if (a < 4) {
						r[i].set_equipment_status(eq_name[a], featuresData[i][j]);
						r[i].set_furniture_status(fur_name[a], featuresData[i][j]);
						r[i].set_services_status(serv_name[a], featuresData[i][j]);
					}
					else {
						r[i].set_services_status(serv_name[a], featuresData[i][j]);
					}
				}
			}
		}
	}
	else { cout << "Filestream is closed\n"; }
	roomDatabasefile.close();
	featuresDatabaseFile.close();
}
string getCleanBooleans(string entry) {
	int resizeValue = entry.length() / 2;
	for (int i = 0; i < entry.length(); i++) {
		for (int j = 0; j < entry.length(); j++) {
			if (entry[j] == '|') {
				swap(entry[j], entry[j + 1]);
			}
		}
	}
	entry.resize(resizeValue);
	return entry;
}
void removeFromRoomsDatabase(Rooms r[50], string roomData[51][20], int indexOfObjects) {
	r[indexOfObjects].set_availability(1);
	r[indexOfObjects].set_rent_days(0);
	r[indexOfObjects].set_guest_identification("blank%");
	r[indexOfObjects].set_guest_name("blank");
	for (int i = 1; i < 10; i++) {
		if (roomData[0][i] == "Availability") {
			roomData[indexOfObjects + 1][i] = booleanToString(r[indexOfObjects].get_availability());
		}
		else if (roomData[0][i] == "Rent days") {
			roomData[indexOfObjects + 1][i] = to_string(r[indexOfObjects].get_rent_days());
		}
		else if (roomData[0][i] == "Guest name") {
			roomData[indexOfObjects + 1][i] = r[indexOfObjects].get_guest_name();
		}
		else if (roomData[0][i] == "Guest ID") {
			roomData[indexOfObjects + 1][i] = r[indexOfObjects].get_guest_identification();
		}
		else { continue; }
	}
	pushToRoomsDatabase(roomData);
}
void removeFromFeaturesDatabase(Rooms r[50], bool featuresData[50][16], int indexOfObject) {
	for (int i = 0; i < 16; i++) {
		if (i == 0) {
			r[indexOfObject].set_furniture_status(fur_name[0], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 1) {
			r[indexOfObject].set_furniture_status(fur_name[1], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 2) {
			r[indexOfObject].set_furniture_status(fur_name[2], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 3) {
			r[indexOfObject].set_furniture_status(fur_name[3], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 4) {
			r[indexOfObject].set_equipment_status(eq_name[0], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 5) {
			r[indexOfObject].set_equipment_status(eq_name[1], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 6) {
			r[indexOfObject].set_equipment_status(eq_name[2], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 7) {
			r[indexOfObject].set_equipment_status(eq_name[3], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 8) {
			r[indexOfObject].set_services_status(serv_name[0], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 9) {
			r[indexOfObject].set_services_status(serv_name[1], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 10) {
			r[indexOfObject].set_services_status(serv_name[2], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 11) {
			r[indexOfObject].set_services_status(serv_name[3], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 12) {
			r[indexOfObject].set_services_status(serv_name[4], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 13) {
			r[indexOfObject].set_services_status(serv_name[5], false);
			featuresData[indexOfObject][i] = false;
		}
		else if (i == 14) {
			r[indexOfObject].set_services_status(serv_name[6], false);
			featuresData[indexOfObject][i] = false;
		}
		else {
			cout << "!!!\n";
		}
	}
	pushToFeaturesDatabase(featuresData);
}
void addToDatabase(Rooms r[50], bool featuresData[50][16], int indexOfObject) {
	for (int i = 0; i < 16; i++) {
		if (i == 0) {
			r[indexOfObject].set_furniture_status(fur_name[0], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 1) {
			r[indexOfObject].set_furniture_status(fur_name[1], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 2) {
			r[indexOfObject].set_furniture_status(fur_name[2], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 3) {
			r[indexOfObject].set_furniture_status(fur_name[3], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 4) {
			r[indexOfObject].set_equipment_status(eq_name[0], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 5) {
			r[indexOfObject].set_equipment_status(eq_name[1], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 6) {
			r[indexOfObject].set_equipment_status(eq_name[2], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 7) {
			r[indexOfObject].set_equipment_status(eq_name[3], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 8) {
			r[indexOfObject].set_services_status(serv_name[0],true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 9) {
			r[indexOfObject].set_services_status(serv_name[1],true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 10) {
			r[indexOfObject].set_services_status(serv_name[2], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 11) {
			r[indexOfObject].set_services_status(serv_name[3], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 12) {
			r[indexOfObject].set_services_status(serv_name[4], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 13) {
			r[indexOfObject].set_services_status(serv_name[5], true);
			featuresData[indexOfObject][i] = true;
		}
		else if (i == 14) {
			r[indexOfObject].set_services_status(serv_name[6], true);
			featuresData[indexOfObject][i] = true;
		}
		else {
			cout << "!!!\n";
		}
	}
	pushToFeaturesDatabase(featuresData);
}
void calculateDaysLeft(int indexOfObject, int timeStamps[50]) {

}
//functions