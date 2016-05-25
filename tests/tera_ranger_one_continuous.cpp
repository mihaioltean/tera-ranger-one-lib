
#include "tera_ranger_one_controller.h"
//-----------------------------------------------------------------------
int main(void)
{
	t_teraranger_one_controller tera_ranger_one;

	if (!tera_ranger_one.connect(11, 115200)) {
		printf("Error attaching to Tera Ranger One! Make sure that port number is correct! On Windows port number supplied as parameter must be with 1 less than the real one (eg. enter 7 if your Device Manager shows 8).");
		printf("Press Enter...");
		getchar();
		return 1;
	}

	while (1){        // starting infinit loop
		if (!tera_ranger_one.update_commands_from_serial())
			Sleep(5); // no new data from serial ... we take a small break so that we don't kill the processor

		// read to see if there is any distance received from sonar
			int distance;
			while (tera_ranger_one.query_for_distance(distance)) // have we received the event from Serial ?
				// print all distances that we have in buffer
				printf("distance = %d cm\n", distance);
		
//		if (GetAsyncKeyState(VK_ESCAPE))  // breaks the infinite loop; for Windows only
//			break;
	}

	tera_ranger_one.close_connection();

	return 0;
}
//-----------------------------------------------------------------------