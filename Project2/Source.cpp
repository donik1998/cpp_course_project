#include<iostream>
#include<string>
#include"Header.h"
#include<fstream>
#include<ctime>

using namespace std;
Rooms rooms[50];
int main() {
	initialize(rooms);
	time(&rawtime);
	loging.open("Data.txt", ios::ate);
	receipt.open("Receipt.txt", ios::trunc|ios::out);
	int addDays, main_menu_choice = 1, guestChoice = 1, room_choice = 1, ord_numofguest, rent_days, adv_numofguest, lux_numofguest, adv_lux_numofguest, info_choice = 1;
	char accepted;
	string id, first_name, last_name, full_name;
	while (main_menu_choice != 0) {
		cout << "Choose the option\n1. Book a room\n2. Price list and services availability\n3. Checkout\n4. Login to see more\n\n 0 - Exit";
		cout << "\nYour choice: "; cin >> main_menu_choice;
		switch (main_menu_choice) {
		case(1): {system("cls");

			break;
		}//room booking
		case(2): {system("cls");
			cout << "So here is freshest peices for service we are providing" << endl;
			cout << "\t\t\tRooms" << endl;
			bool ordinalPricePrint = false, advPricePrint = false, luxPricePrint = false, advLuxPricePrint = false;
			for (int i = 0; i < 50; i++) {
				if (rooms[i].get_room_type() == "Ordinal" && ordinalPricePrint == false) {
					cout << rooms[i].get_room_type() << " room for one person: " << rooms[i].get_room_price() << "$ per day" << endl;
					cout << rooms[i].get_room_type() << " room for two person: " << rooms[i].get_room_price() * 2 << "$ per day" << endl;
					ordinalPricePrint = true;
				}
				if (rooms[i].get_room_type() == "Advanced" && advPricePrint == false) {
					cout << rooms[i].get_room_type() << " room: " << rooms[i].get_room_price() << "$ per day" << endl;
					advPricePrint = true;
				}if (rooms[i].get_room_type() == "Lux" && luxPricePrint == false) {
					cout << rooms[i].get_room_type() << " room: " << rooms[i].get_room_price() << "$ per day" << endl;
					luxPricePrint = true;
				}
				if (rooms[i].get_room_type() == "Advanced lux" && advLuxPricePrint == false) {
					cout << rooms[i].get_room_type() << " room: " << rooms[i].get_room_price() << "$ per day" << endl;
					advLuxPricePrint = true;
				}
			}
			cout << "\t\t\tFurniture" << endl;
			for (int i = 0; i < 4; i++) {
				cout << furniture_name[i] << ": " << fur_rent_price[i] << "$" << endl;
			}
			cout << "\t\t\tEquipment" << endl;
			for (int i = 0; i < 4; i++) {
				cout << equipment_name[i] << ": " << eq_rent_price[i] << "$" << endl;
			}
			cout << "\t\t\tServices" << endl;
			for (int i = 0; i < 7; i++) {
				cout << services_name[i] << ": " << serv_price[i] << "$" << endl;
			}
			cout << "Note: payment for each extra services or gear is charged once only" << endl;
			break;
		}//price list and available services
		case(3): {system("cls");

			break;
		}//billing system
		case(4): {system("cls");
			cout << "Type your passport ID: "; cin >> id;
			for (int i = 0; i < 50; i++) {
				if (id == rooms[i].get_guest_identification()) {
					while (guestChoice != 0) {
						cout << "Alright! " << rooms[i].get_guest_name() << " what are you going to do" << endl;
						cout << "1. Add services\n2. Add equipment\n3. Extend period of living in hotel";
						cout << "\n4. Add furniture\n5. See current bill\n\n 0 - Back" << endl;
						cout << "Your coice: "; cin >> guestChoice;
						switch (guestChoice) {
						case(1): {
							cout << "OK! Which service are you going to add\n";
							add_services(rooms, id);
							break;
						}
						case(2): {
							cout << "OK! Which equipment are you going to choose\n";
							add_equipment(rooms, id);
							break;
						}
						case(3): {
							cout << "How many days would you like to add? "; cin >> addDays;
							rooms[i].addDaysStayed(addDays);
							break;
						}
						case(4): {
							cout << "OK! Which furniture adre you giong to add?" << endl;
							add_furniture(rooms, id);
							break;
						}
						case(5): {
							cout << "OK! For now you have to pay for" << endl;
							bill(rooms, id);
							break;
						}
						}
					}
				}
				else if ((i + 1) == 50) {
					cout << "We dont have a guest with such ID passport\nTry again or ";
				}
				else {
					continue;
				}
			}
		}//login system with additional possibilities
		}
	}
	system("pause");
	return 0;
}