#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
using namespace std;
string furniture_name[4] = { "Comode", "Wardrobe", "Armchair", "Mini-bar" };
string equipment_name[4] = { "TV", "Fridge", "Air conditioner", "Laptop" };
string services_name[7] = { "Morning meal", "Laundry", "Additional cleaning", "Gym", "Guide", "Transport renting", "Taxi from airport to hotel" };
float eq_rent_price[4] = { 15.59, 10.25, 20.85, 45.0 }, fur_rent_price[4] = { 9.85, 16.60, 12.20, 45.50 }, serv_price[7] = { 13.45, 14.50, 11.5, 21.5, 35.50, 49.99, 15.85 };
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
	void set_service_price(string name, float price){
		for (int i = 0; i < 7; i++){
			if (services[i] == name){
				serv_price[i] = price;
				break;
			}
			else{ continue; }
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
};
ofstream outfile;
time_t rawtime;
struct tm *timeinfo;
void show_advanced_avalability(Rooms r[50]){
	int advanced_avalability = 0;
	for (int i = 0; i < 50; i++){
		if (r[i].get_availability() == true && r[i].get_room_type() == "Advanced"){
			advanced_avalability++;
		}
	}
	cout << "We have " << advanced_avalability << " Advanced rooms available" << endl;
}
void show_lux_availability(Rooms r[50]){
	int lux_avalability = 0;
	for (int i = 0; i < 50; i++){
		if (r[i].get_availability() == true && r[i].get_room_type() == "Lux"){
			lux_avalability++;
		}
	}
	cout << "We have " << lux_avalability << " Lux rooms available" << endl;
}
void show_adv_lux_availability(Rooms r[50]){
	int advancedlux_avalability = 0;
	for (int i = 0; i < 50; i++){
		if (r[i].get_availability() == true && r[i].get_room_type() == "Advanced lux"){
			advancedlux_avalability++;
		}
	}
	cout << "We have " << advancedlux_avalability << " Advanced Lux rooms available" << endl;
}
void show_ordinal_availability(Rooms r[50]){
	int ordinal_avalability = 0;
	for (int i = 0; i < 50; i++){
		if (r[i].get_availability() == true && r[i].get_room_type() == "Ordinal"){
			ordinal_avalability++;
		}
	}
	cout << "We have " << ordinal_avalability << " Ordinal rooms available" << endl;
}
void initialize(Rooms r[50]){
	for (int i = 0; i < 50; i++){
		r[i].set_defaults_conv();
		r[i].set_defaults_serv();
		if (i >= 0 && i < 10){
			r[i].set_roomlevel_and_number(1, i + 1);
			r[i].set_room_type("Ordinal");
			r[i].set_room_price(12.50);
			r[i].set_capacity(1);
			r[i].set_availability(true);
		}
		if (i < 20 && i >= 10){
			r[i].set_roomlevel_and_number(1, i + 1);
			r[i].set_room_type("Ordinal");
			r[i].set_room_price(25.00);
			r[i].set_capacity(2);
			r[i].set_availability(true);
		}
		else if (i >= 20 && i < 30){
			r[i].set_roomlevel_and_number(2, i + 1);
			r[i].set_room_type("Advanced");
			r[i].set_room_price(65.00);
			r[i].set_availability(true);
			r[i].set_capacity(3);
		}
		else if (i >= 30 && i < 40){
			r[i].set_roomlevel_and_number(3, i + 1);
			r[i].set_room_type("Lux");
			r[i].set_room_price(150.00);
			r[i].set_availability(true);
			r[i].set_capacity(4);
		}
		else if (i >= 40 && i < 50){
			r[i].set_roomlevel_and_number(4, i + 1);
			r[i].set_room_type("Advanced lux");
			r[i].set_room_price(300);
			r[i].set_capacity(6);
			r[i].set_availability(true);
		}
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
							  outfile.open("Data.txt", ios::app);
							  outfile << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(2) : {
							  r[i].add_furniture(furniture_name[furnutire_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(3) : {
							  r[i].add_furniture(furniture_name[furnutire_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(4) : {
							  r[i].add_furniture(furniture_name[furnutire_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << furniture_name[furnutire_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
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
							  outfile.open("Data.txt", ios::app);
							  outfile << equipment_name[equipment_choice- 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(2) : {
							  r[i].add_equipment(equipment_name[equipment_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << equipment_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(3) : {
							  r[i].add_equipment(equipment_name[equipment_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << equipment_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(4) : {
							  r[i].add_equipment(equipment_name[equipment_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << equipment_name[equipment_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
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
	bool found;
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
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice- 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(2) : {
							  r[i].add_service(services_name[feature_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(3) : {
							  r[i].add_service(services_name[feature_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(4) : {
							  r[i].add_service(services_name[feature_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(5) : {
							  r[i].add_service(services_name[feature_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(6) : {
							  r[i].add_service(services_name[feature_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
							  break;
				}
				case(7) : {
							  r[i].add_service(services_name[feature_choice - 1]);
							  outfile.open("Data.txt", ios::app);
							  outfile << services_name[feature_choice - 1] << " is added for " << r[i].get_guest_name() << " in room number " << r[i].get_room_number() << endl;
							  outfile.close();
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
	if (found == false){
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
							  outfile.open("Data.txt", ios::app);
							  outfile << ctime(&rawtime);
							  add_furniture(r, id);
							  outfile.close();
							  break;
				}
				case(2) : {
							  outfile.open("Data.txt", ios::app);
							  outfile << ctime(&rawtime);
							  add_equipment(r, id);
							  outfile.close();
							  break;
				}
				case(3) : {
							  outfile.open("Data.txt", ios::app);
							  outfile << ctime(&rawtime);
							  add_services(r, id);
							  outfile.close();
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
