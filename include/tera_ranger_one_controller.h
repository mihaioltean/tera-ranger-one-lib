// MIT License
// contact: Mihai Oltean, www.tcreate.org, mihai.oltean@gmail.com

#ifndef tera_ranger_one_H
#define tera_ranger_one_H

#include "rs232.h"
#include "lista_voidp.h"

#include <iostream>
#include <time.h>

#define COMMAND_NOT_SENT 0
#define COMMAND_SENT 1
#define COMMAND_DONE 2

class t_teraranger_one_controller {
private:
	// version number of the library
	char version[20];

	// port number of the serial connection
	int port_number;

	// status
	int sensor_state;

	// current buffer of characters received from sensor
	char current_buffer[4096]; // I should not need so much

	// a list with received events from sensor
	TLista received_distances;

	// parse the string for events
	int parse_and_queue_commands(char* tmp_str, int str_length);

public:
	t_teraranger_one_controller(void);
	~t_teraranger_one_controller(void);

	// connects to given serial port
	bool connect(int port, int baud_rate);

	// close serial connection
	void close_connection(void);

	// returns a string containing the version number of this library
	const char* get_version(void);

	// reads data from serial and updates the list of received events from Tera Ranger One
	// this should be called frequently from the main loop of the program in order to read the data received from Tera Ranger One
	bool update_commands_from_serial(void);

	// gets an unformated string of chars from serial
	// should be used only in extreme cases
	// normally an application must call update_commands_from_serial
	int get_data_from_serial(char *buffer, int buffer_size);

	// send request
	void send_request_distance(void);

	// query for distance
	bool query_for_distance(int & distance);

	int get_state(void);
	void set_state(int new_state);
};

#endif