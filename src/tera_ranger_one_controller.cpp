
#include "tera_ranger_one_controller.h"

#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//--------------------------------------------------------------
t_teraranger_one_controller::t_teraranger_one_controller(void)
{
	strcpy(version, "2016.05.24.0"); // year.month.day.build number
	current_buffer[0] = 0;

	sensor_state = COMMAND_DONE;
}
//--------------------------------------------------------------
t_teraranger_one_controller::~t_teraranger_one_controller(void)
{

}
//--------------------------------------------------------------
const char* t_teraranger_one_controller::get_version(void)
{
	return version;
}
//--------------------------------------------------------------
bool t_teraranger_one_controller::connect(int port, int baud_rate)
{
	char mode[] = { '8', 'N', '1', 0 };

	port_number = port;
	current_buffer[0] = 0;

	return RS232_OpenComport(port, baud_rate, mode) == 0;
}
//--------------------------------------------------------------
void t_teraranger_one_controller::close_connection(void)
{
	RS232_CloseComport(port_number);
	current_buffer[0] = 0;
}
//--------------------------------------------------------------
int t_teraranger_one_controller::parse_and_queue_commands(char* tmp_str, int str_length)
{
	int i = 0;
	while (i < str_length) {
		// can be more than 1 command in a string, so I have to check again for a letter
		if (tmp_str[i] == 'T' && i + 3 <= str_length) {
			int *distance = new int;
			*distance = tmp_str[i + 1] * 255 + tmp_str[i + 2];
			if (*distance >= 200 && *distance <= 14000)
  			  received_distances.Add(distance);
			i += 4;
		}
		else
			i++;
	}
	return i;
}
//--------------------------------------------------------------
bool t_teraranger_one_controller::update_commands_from_serial(void)
{
	// the same code as in firmware
	char tmp_buffer[4096];
	int received_size = get_data_from_serial(tmp_buffer, 4096);
	tmp_buffer[received_size] = 0;
	if (received_size) {
		strcpy(current_buffer + strlen(current_buffer), tmp_buffer);
		//	printf("%s\n", current_buffer);

		size_t buffer_length = strlen(current_buffer);
		for (size_t i = 0; i < buffer_length; i++)
			if (current_buffer[i] == 'T') {// a distance
				size_t j = buffer_length - 1;
				if (j >= i + 3) {

#ifdef DEBUG
					char tmp_str[64];
					strncpy(tmp_str, current_buffer + i, j - i);
					tmp_str[j - i] = 0;
					printf("current command is= %s", tmp_str);
#endif

					int new_index = parse_and_queue_commands(current_buffer + i, (int)(j - i + 1));

					// remove the current executed command
					strcpy(current_buffer, current_buffer + new_index);// not sure if this is good due to overlaps

#ifdef DEBUG
					Serial.write("buffer left=");
					Serial.write(current_buffer);
					Serial.write("\n----------------\n");
					//Serial.println(strlen(current_buffer)); // buffer length
#endif

					break; //for i
				}
				else {// the string is not completed ... so I must wait for more...
					break; // for i
				}
			}
		return true;
	}
	else
		return false;
}
//--------------------------------------------------------------
int t_teraranger_one_controller::get_data_from_serial(char *buffer, int buffer_size)
{
	return RS232_PollComport(port_number, (unsigned char*)buffer, buffer_size);
}
//--------------------------------------------------------------
void t_teraranger_one_controller::send_request_distance(void)
{
	// must clear the received distances
	node_double_linked *node_p = received_distances.head;
	while (received_distances.head) {
		int* d = (int*)received_distances.GetHeadInfo();
		delete d;
		received_distances.DeleteHead();
	}

	// must clear the serial
	char tmp_buffer[4096];
	int received_size = get_data_from_serial(tmp_buffer, 4096);
}
//--------------------------------------------------------------
bool t_teraranger_one_controller::query_for_distance(int &distance)
{
	for (node_double_linked *node_p = received_distances.head; node_p; node_p = node_p->next) {
		int* d = (int*)received_distances.GetCurrentInfo(node_p);
		distance = *d;
		delete d;
		received_distances.DeleteCurrent(node_p);
		return true;
	}
	return false;
}
//--------------------------------------------------------------
int t_teraranger_one_controller::get_state(void)
{
	return sensor_state;
}
//--------------------------------------------------------------
void t_teraranger_one_controller::set_state(int new_state)
{
	sensor_state = new_state;
}
//--------------------------------------------------------------