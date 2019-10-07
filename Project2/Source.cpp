#include<iostream>
#include<string>
#include"Header.h"
#include<fstream>
#include<ctime>

using namespace std;
Rooms rooms[50];
int main(){
	time(&rawtime);
	outfile.open("Data.txt", ios::app);
	int main_menu_choice = 1, room_choice = 1, ord_numofguest, rent_days, adv_numofguest, lux_numofguest, adv_lux_numofguest, info_choice = 1;
	char accepted;
	string id, first_name, last_name, full_name;
	initialize(rooms);
	/*for (int i = 0; i < 50; i++){
	cout << "t " << rooms[i].get_room_type() << endl;
	cout << "n " << rooms[i].get_room_number() << endl;
	cout << "av " << rooms[i].get_availability() << endl;
	cout << "cap " << rooms[i].get_capacity() << endl;
	}*/
	
	while (main_menu_choice != 0){//main muenu
		cout << "Welcome to our hotel" << endl;
		cout << "Please choose the option" << endl;
		cout << "1. Book a room" << endl << "2. Check information about hotel" << endl << "3. Have a bill and leave the hotel" << endl << "4. Additional staff" << endl << endl << "0 - Exit" << endl;
		cout << "Your choice: "; cin >> main_menu_choice;
		if (main_menu_choice > 4 || main_menu_choice < 0){
			cout << "Wrong input" << endl; system("cls");
		}
		switch (main_menu_choice){//main muenu
		case(1) : {//main muenu Book a room
			 system("cls");
			 while (true){// Book a room menu
			 cout << "Which one are you going to choose" << endl;
			 cout << "1. Ordinal" << endl << "2. Advanced" << endl << "3. Lux" << endl << "4. Advanced Lux" << endl << endl << "0 - Back" << endl;
			 cout << "Your choice: "; cin >> room_choice; 
			 if (room_choice > 4 || room_choice < 0){
				cout << "Wrong input!!!" << endl; system("cls"); break;
			 }
			 if (room_choice == 0){
				break;
			 }
			 switch (room_choice){// Book a room menu
			 case(1) : {	system("cls");
			  show_ordinal_availability(rooms);
			  cout << "How many are you: "; cin >> ord_numofguest;
			  for (int i = 0; i < 50; i++){
				if (rooms[i].get_capacity() >= ord_numofguest && rooms[i].get_availability() == true && rooms[i].get_room_type() == "Ordinal"){
					  cout << "We recomend you room number " << rooms[i].get_room_number() << " on " << rooms[i].get_roomlvl() << " floor" << endl;
					  cout << "Will you take it?(y/n)" << endl;
					  cin >> accepted;
					  if (accepted == 'y' || accepted == 'Y'){
						  cout << "OK! Input following data then" << endl;
						  cout << "First name: "; cin >> first_name;
						  cout << "Last name: "; cin >> last_name;
						  full_name = first_name + " " + last_name;
						  rooms[i].set_guest_name(full_name);
						  cout << "Your identification number: "; cin >> id;
						  rooms[i].set_guest_identification(id);
						  rooms[i].set_availability(false);
						  cout << "number of days that you will stay: "; cin >> rent_days;
						  rooms[i].set_rent_days(rent_days);
						  cout << "OK! Room number " << rooms[i].get_room_number() << " is successfully booked for " << rooms[i].get_guest_name() << " for " << rooms[i].get_rent_days() << endl;
						  cout << "What are you going to do next? " << endl;
						  outfile << ctime(&rawtime);
						  outfile << "Guest " << rooms[i].get_guest_name() << " is registered to room number " << rooms[i].get_room_number() << endl;
						  outfile << "Identification number: " << rooms[i].get_guest_identification() << endl;
						  room_choice = 0;
						  break;
					  }
					  else if (accepted == 'n' || accepted == 'N'){
						  cout << "OK! Let's find something else" << endl;
						  if (rooms[i].get_room_type() != "Ordinal"){
							  cout << "We don't have any other option" << endl;
							  break;
						  }
						  else{ continue; }
					  }
					  else{
						  cout << "Wrong user input" << endl;
						  i--;
					  }
				  }
				  else if (rooms[i].get_capacity()<ord_numofguest && rooms[i].get_room_type()!="Ordinal"){
					cout << "Maximum number of guests in Ordinary room is 2\n";
				  }
				  else{
					  continue;
				  }
			  }
			  break;
			 }// Book a room menu case 1
			 case(2) : {	system("cls");
			  show_advanced_avalability(rooms);
			  cout << "How many are you: "; cin >> adv_numofguest;
			  for (int i = 0; i < 50; i++){
				  if (rooms[i].get_capacity() >= adv_numofguest && rooms[i].get_availability() == true && rooms[i].get_room_type() == "Advanced"){
					  cout << "We recomend you room number " << rooms[i].get_room_number() << " on " << rooms[i].get_roomlvl() << " floor" << endl;
					  cout << "Will you take it?(y/n)" << endl;
					  cin >> accepted;
					  if (accepted == 'y' || accepted == 'Y'){
						  cout << "OK! Provide following data" << endl;
						  cout << "First name: "; cin >> first_name;
						  cout << "Last name: "; cin >> last_name;
						  full_name = first_name + " " + last_name;
						  rooms[i].set_guest_name(full_name);
						  cout << "Your identification number: "; cin >> id;
						  rooms[i].set_guest_identification(id);
						  rooms[i].set_availability(false);
						  cout << "Number of days that you will stay: "; cin >> rent_days;
						  rooms[i].set_rent_days(rent_days);
						  cout << "OK! Room number " << rooms[i].get_room_number() << " is booked for " << rooms[i].get_guest_name() << " for " << rooms[i].get_rent_days() << endl;
						  cout << "What are you going to do next? " << endl;
						  outfile << ctime(&rawtime);
						  outfile << "Guest " << rooms[i].get_guest_name() << " is registered to room number " << rooms[i].get_room_number() << endl;
						  outfile << "Identification number: " << rooms[i].get_guest_identification() << endl;
						  room_choice = 0;
						  break;
					  }
					  else if (accepted == 'n' || accepted == 'N'){
						  cout << "OK! Let's find something else" << endl;
						  if (rooms[i].get_room_type() != "Advanced"){
							  cout << "We don't have other rooms of this type" << endl;
							  break;
						  }
						  else{ continue; }
					  }
					  else{
						  cout << "Wrong user input" << endl;
						  i--;
					  }
				  }
				  else if (rooms[i].get_capacity() < adv_numofguest){
					  continue;
				  }
				  else{
					  continue;
				  }
			  }
			  break;
			 }// Book a room menu case 2
			 case(3) : {
					system("cls");
					show_lux_availability(rooms);
					cout << "How many are you?"; cin >> lux_numofguest;
					for (int i = 0; i < 50; i++){
						if (rooms[i].get_capacity() >= lux_numofguest && rooms[i].get_availability() == true && rooms[i].get_room_type() == "Lux"){
							cout << "We recomend you room number " << rooms[i].get_room_number() << " on " << rooms[i].get_roomlvl() << " floor." << endl;
							cout << "Will you take it?(y/n)" << endl;
							cin >> accepted;
							if (accepted == 'y' || accepted == 'Y'){
								cout << "OK! Input following data" << endl;
								cout << "First name: "; cin >> first_name;
								cout << "Last name: "; cin >> last_name;
								full_name = first_name + " " + last_name;
								rooms[i].set_guest_name(full_name);
								cout << "Your identification number: "; cin >> id;
								rooms[i].set_guest_identification(id);
								cout << "How many days are you going to stay?"; cin >> rent_days;
								rooms[i].set_rent_days(rent_days);
								cout << "OK! room number " << rooms[i].get_room_number() << " is booked for " << rooms[i].get_guest_name() << " for " << rooms[i].get_rent_days() << " days." << endl;
								cout << "What are you going to do next? " << endl;
								outfile << ctime(&rawtime);
								outfile << "Guest " << rooms[i].get_guest_name() << " is registered to room number " << rooms[i].get_room_number() << endl;
								outfile << "Identification number: " << rooms[i].get_guest_identification() << endl;
								room_choice = 0;
								break;
							}
							else if (accepted == 'n' || accepted == 'Y'){
								cout << "OK! we are looking for something else" << endl;
								if (rooms[i].get_room_type() != "Lux"){
									cout << "We don't have any other lux rooms!" << endl;
									break;
								}
								else{ continue; }
							}
							else {
								cout << "Wrong user input" << endl;
								i--;
							}
						}
						else if (rooms[i].get_capacity() < lux_numofguest){
							continue;
						}
						else{
							continue;
						}
					}
						break;
			 }// Book a room menu case 3
			 case(4) : {
					system("cls");
					cout << "How namy are you?" << endl; cin >> adv_lux_numofguest;
					for (int i = 0; i < 50; i++){
						if (rooms[i].get_capacity() >= adv_lux_numofguest && rooms[i].get_availability() == true && rooms[i].get_room_type() == "Advanced lux"){
							cout << "We recomend you room number " << rooms[i].get_room_number() << " on " << rooms[i].get_roomlvl() << " floor." << endl;
							cout << "Will you take it?(y/n)" << endl;
							cin >> accepted;
							if (accepted == 'Y' || accepted == 'y'){
								cout << "OK! input following information" << endl;
								cout << "First name: "; cin >> first_name;
								cout << "Last name: "; cin >> last_name;
								full_name = first_name + " " + last_name;
								rooms[i].set_guest_name(full_name);
								cout << "Your identification number: "; cin >> id;
								rooms[i].set_guest_identification(id);
								cout << "How many days are you going to stay?"; cin >> rent_days;
								rooms[i].set_rent_days(rent_days);
								cout << "OK! Room number " << rooms[i].get_room_number() << " is booked for " << rooms[i].get_guest_name() << " for " << rooms[i].get_rent_days() << " days" << endl;
								cout << "What are you going to do next? " << endl;
								outfile << ctime(&rawtime);
								outfile << "Guest " << rooms[i].get_guest_name() << " is registered to room number " << rooms[i].get_room_number() << endl;
								outfile << "Identification number: " << rooms[i].get_guest_identification() << endl;
								room_choice = 0;
								break;
							}
							else if (accepted == 'n' || accepted == 'N'){
								cout << "OK! We are looking for another option" << endl;
								if (rooms[i].get_room_type() != "Advanced lux"){
									cout << "We don't have any other options" << endl;
									break;
								}
								else{ continue; }
							}
							else
							{
								cout << "Wrong user input" << endl;
								i--;
							}

						}
						else if (rooms[i].get_capacity() < adv_lux_numofguest){
							continue;
						}
						else{
							continue;
						}
					}
						break;
			  }// Book a room menu case 4
			  }// Book a room menu switch
		}// Book a room menu while
			room_choice = 1;
			break;
		}// Book a room ends
		case(2) : {
			 system("cls");
			 while (info_choice != 0){
			  cout << "What king of information are you going to look at?" << endl;
			  cout << "1. Rooms avalability" << endl << "2. Additional services" << endl << "3. Hotel's location" << endl << "4. Price list" << endl << endl << "0 - Back" << endl;
			  cin >> info_choice;
			  if (info_choice > 5 || info_choice < 0){
				  cout << "Wrong Input!!!" << endl; system("cls"); break;
			  }
			  switch (info_choice){
			  case(1) : {
							system("cls");
							cout << "Now we have" << endl;
							show_ordinal_availability(rooms);
							show_advanced_avalability(rooms);
							show_lux_availability(rooms);
							show_adv_lux_availability(rooms);
							break;
			  }//rooms availability
			  case(2) : {
							system("cls");
							cout << "Our hotel provides following additional services" << endl;
							for (int i = 0; i < 7; i++){
								cout << i + 1 << ". " << services_name[i] << endl;
							}
							cout << "Also you are able to rent following funiture" << endl;
							for (int i = 0; i < 4; i++){
								cout << i + 1 << ". " << furniture_name[i] << endl;
							}
							cout << "It is possible to rent following equipment as well" << endl;
							for (int i = 0; i < 4; i++){
								cout << i + 1 << ". " << equipment_name[i] << endl;
							}
							break;
			  }//Additional services
			  case(3) : {
							system("cls");
							cout << "Here is our adress Amir Temur district 110, Tashkent, Uzbekistan" << endl;
							break;
			  }//Hotel's location
			  case(4) : {
							system("cls");
							cout << "Ordinal room for 1 guest(s): 12.25$" << endl;
							cout << "Ordinal room for 2 guest(s): 25$" << endl;
							cout << "Advanced room for 3 guest(s): 65$" << endl;
							cout << "Lux room for 4 guest(s): 150$" << endl;
							cout << "Advanced lux for 6 guest(s): 300$" << endl;
							for (int i = 0; i < 7; i++){
								cout << services_name[i] << ": " << serv_price[i] << " $" << endl;
							}
							for (int i = 0; i < 4; i++){
								cout << equipment_name[i] << ": " << eq_rent_price[i] << " $" << endl;
							}
							for (int i = 0; i < 4; i++){
								cout << furniture_name[i] << ": " << fur_rent_price[i] << " $" << endl;
							}
							break;
			  }//Price list
			  }//case2 switch
		}//case2 while
			info_choice = 1;
			break;
		}//main muenu case View information
		case(3) : {
					  system("cls");
					  float bill = 0; bool found; int room_num;
					  cout << "Plese input your identification number" << endl; cin >> id;
					  for (int i = 0; i < 50; i++){
						  if (rooms[i].get_guest_identification() == id && rooms[i].get_availability() == false){
							  found = true;
							  room_num = rooms[i].get_room_number();
							  cout << "OK! you have stayed in our hotel for " << rooms[i].get_rent_days() << " days in " << rooms[i].get_room_type() << ", which costs " << rooms[i].get_room_price() << "$ per day" << endl;
							  cout << "It will be " << rooms[i].get_room_price()*rooms[i].get_rent_days() << "$ in total" << endl;
							  bill += (rooms[i].get_room_price()*rooms[i].get_rent_days());
							  for (int a = 0; a < 4; a++){
								  if (rooms[i].get_equipment_status(equipment_name[a]) == true){
									  cout << "You also rented " << equipment_name[a] << ", which costs " << eq_rent_price[a] << "$" << endl;
									  bill += eq_rent_price[a];
								  }
								  else if (rooms[i].get_equipment_status(equipment_name[a]) == false){
									  continue;
								  }
								  else{
									  cout << "You haven't rented any equipment" << endl;
								  }
							  }
							  for (int b = 0; b < 4; b++){
								  if (rooms[i].get_furniture_status(furniture_name[b]) == true){
									  cout << "You also rented " << furniture_name[b] << ", which costs " << fur_rent_price[b] << "$" << endl;
									  bill += fur_rent_price[b];
								  }
								  else if (rooms[i].get_furniture_status(furniture_name[b]) == false){
									  continue;
								  }
								  else{
									  cout << "You haven't rented any furniture" << endl;
								  }
							  }
							  for (int c = 0; c < 7; c++){
								  if (rooms[i].get_service_status(services_name[c]) == true){
									  cout << "You also asked for " << services_name[c] << ", which costs " << serv_price[c] << "$" << endl;
									  bill += serv_price[c];
								  }
								  else if (rooms[i].get_service_status(services_name[c]) == false){
									  continue;
								  }
								  else{
									  cout << "You haven't added any services" << endl;
								  }
							  }
							  break;
						  }
						  else if (rooms[i].get_guest_identification() != id || rooms[i].get_availability() == true){
							  found = false; continue;
						  }
						  else{
							  cout << "You are not registered!" << endl;
							  found = false;
						  }
					  }
					  if (found == false){
						  cout << "Not found" << endl;
					  }
					  else{
						  outfile << ctime(&rawtime);
						  outfile << "Bill is created and guset moved out from " << room_num << endl;
						  for (int i = 0; i < 50; i++){
							  if (rooms[i].get_room_number() == room_num && rooms[i].get_guest_identification() == id){
								  rooms[i].set_availability(false);
								  break;
							  }
						  }
						  cout << "In total you have to pay " << bill << " $" << endl;
						  bill = 0;
					  }
					  

					  break;
		}//main muenu case Make a bill
		case(4) : {
					  system("cls");
					  cout << "Input ID number please: "; cin >> id;
					  outfile << ctime(&rawtime);
					  add_features(rooms, id);
					  break;
		}//additional staff
		}//main muenu switch
	}//main muenu while
	outfile.close();
	system("cls");
	system("pause");
	return 0;
}