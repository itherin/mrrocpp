// -------------------------------------------------------------------------
//                              task/mp_t_haptic.cc
//
// MP task for two robot haptic device
//
// -------------------------------------------------------------------------

#include "lib/typedefs.h"
#include "lib/impconst.h"
#include "lib/com_buf.h"

#include "lib/srlib.h"
#include "base/mp/mp.h"
#include "ecp_mp_t_bird_hand_test.h"
#include "mp_t_bird_hand_test.h"
#include "lib/single_thread_port.h"
#include "lib/mrmath/mrmath.h"
#include "lib/data_port_headers/bird_hand.h"
#include "robot/bird_hand/bird_hand_const.h"
#include "generator/ecp/ecp_mp_g_transparent.h"
#include "ecp_mp_g_bird_hand_test.h"

#include <iostream>
#include <string>
#include <sstream>

namespace mrrocpp {
namespace mp {
namespace task {

task* return_created_mp_task(lib::configurator &_config)
{
	return new bird_hand_test(_config);
}

bird_hand_test::bird_hand_test(lib::configurator &_config) :
	task(_config)
{
}

void bird_hand_test::main_task_algorithm(void)
{

	sr_ecp_msg->message("New bird_hand_test series");

	// wlaczenie generatora transparentnego w obu robotach
	set_next_ecps_state(ecp_mp::common::generator::ECP_GEN_TRANSPARENT, (int) 0, "", 0, 1, lib::ROBOT_BIRD_HAND.c_str());

	send_end_motion_to_ecps(1, lib::ROBOT_BIRD_HAND.c_str());

	sr_ecp_msg->message("4");

	set_next_ecps_state(ecp_mp::bird_hand::generator::ECP_GEN_BIRD_HAND_TEST, (int) 5, "", 0, 1, lib::ROBOT_BIRD_HAND.c_str());
	sr_ecp_msg->message("5");
	run_extended_empty_generator_for_set_of_robots_and_wait_for_task_termination_message_of_another_set_of_robots(1, 1, lib::ROBOT_BIRD_HAND.c_str(), lib::ROBOT_BIRD_HAND.c_str());

	sr_ecp_msg->message("END");

}

} // namespace task
} // namespace mp
} // namespace mrrocpp
