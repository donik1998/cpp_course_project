#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<process.h>
using namespace std;
fstream loging, receipt, initializationfile;
time_t rawtime;
struct tm *timeinfo;
char accepted; int stayDays;
string id, first_name, last_name, full_name;
bool GlobalBill = false;
string furniture_name[4] = { "Comode", "Wardrobe", "Armchair", "Mini-bar" };
string equipment_name[4] = { "TV", "Fridge", "Air conditioner", "Laptop" };
string services_name[7] = { "Morning meal", "Laundry", "Additional cleaning", "Gym", "Guide", "Transport renting", "Taxi from airport to hotel" };
float eq_rent_price[4] = { 15.59, 10.25, 20.85, 45.0 };
float fur_rent_price[4] = { 9.85, 16.60, 12.20, 45.50 };
float serv_price[7] = { 13.45, 14.50, 11.5, 21.5, 35.50, 49.99, 15.85 };
//classes
class Guest{
private:
	string guest_name, guest_identification_number;
	int daysStayed = 0;
public:
	void set_days_stayed(int days) {
		daysStayed = days;
	}
	int get_days_stayed() {
		return daysStayed;
	}
	void addDaysStayed(int add_days) {
		daysStayed += add_days;
	}
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
	void set_defaults_conv(){
		equipment_name[0] = "TV";
		equipment_name[1] = "Fridge";
		equipment_name[2] = "Air conditioner";
		equipment_name[3] = "Laptop";
		furniture_name[0] = "Comode";
		furniture_name[1] = "Wardrobe";
		furniture_name[2] = "Armchair";
		furniture_name[3] = "Mini-bar";
		for (int i = 0; i < 4; i++){
			eq_rent_status[i] = false;
			fur_rent_status[i] = false;
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
	void set_defaults_serv(){
		services[0] = "Morning meal";
		services[1] = "Laundry";
		services[2] = "Additional cleaning";
		services[3] = "Gym";
		services[4] = "Guide";
		services[5] = "Transport renting";
		services[6] = "Taxi from airport to hotel";
		for (int i = 0; i < 7; i++){
			service_status[i] = false;
		}
	}
	/*void set_service_price(string name, float price){
		for (int i = 0; i < 7; i++){
			if (services[i] == name){
				serv_price[i] = price;
				break;
			}
			else{ continue; }
		}
	}*/
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
	int room_level, room_number, capacity, rent_days;
	string room_type;
	float room_price;
	bool availability;
public:
	void set_roomlevel_and_number(int lvl, int num){
		room_level = lvl;
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
	void set_room_price(float price){
		room_price = price;
	}
	float get_room_price(){
		return room_price;
	}
	~Rooms(){
		cout << "Room is freed for other guests\n";
		set_availability(true);
	}
};
//classes

//functions
void initializeFromFile(Rooms r[50]) {
	for (int i = 0; i < 50; i++) {
		
	}
}
void initialize(Rooms r[50]){
	initializationfile.open("Initialization.txt", ios::out | ios::app | ios::in);
	for (int i = 0; i < 50; i++){
		if (i >= 0 && i < 10){
			r[i].set_roomlevel_and_number(1, i + 1);
			r[i].set_room_type("Ordinal");
			r[i].set_room_price(12.50);
			r[i].set_capacity(1);
			r[i].set_availability(true);
			r[i].set_guest_name("\0");
			r[i].set_guest_identification("\0");
			initializationfile << "Room number: " << r[i].get_room_number()
				<< endl << "Room's level: " << r[i].get_roomlvl() << endl;
			initializationfile << "Room type: " << r[i].get_room_type() << endl;
			initializationfile << "Room price: " << r[i].get_room_price() << endl;
			initializationfile << "Room capacity: " << r[i].get_capacity() << endl;
			initializationfile << "Rooms availability: " << r[i].get_availability() << endl;
			initializationfile << "Guest name: " << r[i].get_guest_name() << endl;
			initializationfile << "Guest identification: " << r[i].get_guest_identification() << endl;
			initializationfile << "________________________________________________" << endl;
		}
		if (i < 20 && i >= 10){
			r[i].set_roomlevel_and_number(2, i + 1);
			r[i].set_room_type("Ordinal");
			r[i].set_room_price(25.00);
			r[i].set_capacity(2);
			r[i].set_availability(true);
			r[i].set_guest_name("\0");
			r[i].set_guest_identification("\0");
			initializationfile << "Room number: " << r[i].get_room_number()
				<< endl << "Room's level: " << r[i].get_roomlvl() << endl;
			initializationfile << "Room type: " << r[i].get_room_type() << endl;
			initializationfile << "Room price: " << r[i].get_room_price() << endl;
			initializationfile << "Room capacity: " << r[i].get_capacity() << endl;
			initializationfile << "Rooms availability: " << r[i].get_availability() << endl;
			initializationfile << "Guest name: " << r[i].get_guest_name() << endl;
			initializationfile << "Guest identification: " << r[i].get_guest_identification() << endl;
			initializationfile << "________________________________________________" << endl;
		}
		else if (i >= 20 && i < 30){
			r[i].set_roomlevel_and_number(3, i + 1);
			r[i].set_room_type("Advanced");
			r[i].set_room_price(65.00);
			r[i].set_availability(true);
			r[i].set_capacity(3);
			r[i].set_guest_name("\0");
			r[i].set_guest_identification("\0");
			initializationfile << "Room number: " << r[i].get_room_number()
				<< endl << "Room's level: " << r[i].get_roomlvl() << endl;
			initializationfile << "Room type: " << r[i].get_room_type() << endl;
			initializationfile << "Room price: " << r[i].get_room_price() << endl;
			initializationfile << "Room capacity: " << r[i].get_capacity() << endl;
			initializationfile << "Rooms availability: " << r[i].get_availability() << endl;
			initializationfile << "Guest name: " << r[i].get_guest_name() << endl;
			initializationfile << "Guest identification: " << r[i].get_guest_identification() << endl;
			initializationfile << "________________________________________________" << endl;
		}
		else if (i >= 30 && i < 40){
			r[i].set_roomlevel_and_number(4, i + 1);
			r[i].set_room_type("Lux");
			r[i].set_room_price(150.00);
			r[i].set_availability(true);
			r[i].set_capacity(4);
			r[i].set_guest_name("\0");
			r[i].set_guest_identification("\0");
			initializationfile << "Room number: " << r[i].get_room_number()
				<< endl << "Room's level: " << r[i].get_roomlvl() << endl;
			initializationfile << "Room type: " << r[i].get_room_type() << endl;
			initializationfile << "Room price: " << r[i].get_room_price() << endl;
			initializationfile << "Room capacity: " << r[i].get_capacity() << endl;
			initializationfile << "Rooms availability: " << r[i].get_availability() << endl;
			initializationfile << "Guest name: " << r[i].get_guest_name() << endl;
			initializationfile << "Guest identification: " << r[i].get_guest_identification() << endl;
			initializationfile << "________________________________________________" << endl;
		}
		else if (i >= 40 && i < 50){
			r[i].set_roomlevel_and_number(5, i + 1);
			r[i].set_room_type("Advanced lux");
			r[i].set_room_price(300);
			r[i].set_capacity(6);
			r[i].set_availability(true);
			r[i].set_guest_name("\0");
			r[i].set_guest_identification("\0");
			initializationfile << "Room number: " << r[i].get_room_number()
				<< endl << "Room's level: " << r[i].get_roomlvl() << endl;
			initializationfile << "Room type: " << r[i].get_room_type() << endl;
			initializationfile << "Room price: " << r[i].get_room_price() << endl;
			initializationfile << "Room capacity: " << r[i].get_capacity() << endl;
			initializationfile << "Rooms availability: " << r[i].get_availability() << endl;
			initializationfile << "Guest name: " << r[i].get_guest_name() << endl;
			initializationfile << "Guest identification: " << r[i].get_guest_identification() << endl;
			initializationfile << "________________________________________________" << endl;
		}
		r[i].set_defaults_conv();
		r[i].set_defaults_serv();
	}
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
					cout << counter << ". " << furniture_name[j] << endl;
					counter++;
				}counter = 1;
				cout << endl << "0 - Back" << endl << "Your choice: "; cin >> furnutire_choice;
				if (furnutire_choice>4 || furnutire_choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (furnutire_choice){
				case(1) : {
					r[i].add_furniture(furniture_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(2) : {
					r[i].add_furniture(furniture_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(3) : {
					r[i].add_furniture(furniture_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(4) : {
					r[i].add_furniture(furniture_name[furnutire_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
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
					cout << counter << ". " << equipment_name[j] << endl;
					counter++;
				}counter = 1;
				cout << endl << "0 - Back" << endl;
				cout << "So what is your choice: "; cin >> equipment_choice;
				if (equipment_choice>4 || equipment_choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (equipment_choice){
				case(1) : {
					r[i].add_equipment(equipment_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << equipment_name[equipment_choice- 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(2) : {
					r[i].add_equipment(equipment_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << equipment_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(3) : {
					r[i].add_equipment(equipment_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << equipment_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(4) : {
					r[i].add_equipment(equipment_name[equipment_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << equipment_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
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
					cout << counter << ". " << services_name[j] << endl;
					counter++;
				}counter = 1;
				cout << "0 - Back" << endl << "So your choice is: "; cin >> feature_choice;
				if (feature_choice>7 || feature_choice < 0){
					cout << "Wrong input!!!" << endl; system("cls"); break;
				}
				switch (feature_choice){
				case(1) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice- 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(2) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(3) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(4) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(5) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(6) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
					loging.close();
					break;
				}
				case(7) : {
					r[i].add_service(services_name[feature_choice - 1]);
					loging.open("Data.txt", ios::app);
					loging << ctime(&rawtime) << endl;
					loging << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
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
				cout << "You have lived in " << r[i].get_room_type() << " number " << r[i].get_room_number() << " on " << r[i].get_roomlvl() << " floor for " << r[i].get_days_stayed() << " days" << endl;
				cout << "It costs " << r[i].get_room_price() << "$ per day. So you have to pay " << r[i].get_days_stayed()*r[i].get_room_price() << "$ for room rent" << endl;
				total += (r[i].get_days_stayed()*r[i].get_room_price());
				receipt << "Room for " << r[i].get_days_stayed() << " days: " << total << "$" << endl;
				for (int j = 0; j < 4; j++) {
					if (r[i].get_furniture_status(furniture_name[j]) == true) {
						cout << "You also rented " << furniture_name[j] << " for " << fur_rent_price[j] << "$" << endl;
						receipt << furniture_name[j] << ": " << fur_rent_price[j] << "$" << endl;
						total += fur_rent_price[j];
					}
					if (r[i].get_equipment_status(equipment_name[j]) == true) {
						cout << "You also rented " << equipment_name[j] << " for " << eq_rent_price[j] << "$" << endl;
						receipt << equipment_name[j] << ": " << eq_rent_price[j] << "$" << endl;
						total += eq_rent_price[j];
					}
				}
				for (int k = 0; k < 7; k++) {
					if (r[i].get_service_status(services_name[k]) == true) {
						cout << "You also ordered " << services_name[k] << " for " << serv_price[k] << endl;
						receipt << services_name[k] << ": " << serv_price[k] << "$" << endl;
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
				r[i].set_days_stayed(stayDays);
				r[i].set_guest_identification(id);
				r[i].set_guest_name(full_name);
				loging.open("Data.txt", ios::ate | ios::out);
				loging << ctime(&rawtime) << ": " << full_name << " is registered in room number " << r[i].get_room_number() << " for " << stayDays << " days" << endl;
				loging.close();
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
//functions