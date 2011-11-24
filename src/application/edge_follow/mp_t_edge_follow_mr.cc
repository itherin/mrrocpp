/*!
 * @file
 * @brief File contains edge_follow_mr mp_task class definition of unknown contour following application.
 * @author twiniars <twiniars@ia.pw.edu.pl>, Warsaw University of Technology
 *
 * @ingroup edge_follow
 */

#include <iostream>
#include <sstream>

#include "base/mp/mp_task.h"

#include "mp_t_edge_follow_mr.h"
#include "base/lib/mrmath/mrmath.h"

#include "robot/irp6_tfg/dp_tfg.h"

#include "application/edge_follow/ecp_mp_st_edge_follow.h"
#include "subtask/ecp_mp_st_bias_edp_force.h"
#include "subtask/ecp_mp_st_tff_nose_run.h"
#include "generator/ecp/ecp_mp_g_tfg.h"

#include "robot/irp6ot_m/mp_r_irp6ot_m.h"
#include "robot/irp6p_m/mp_r_irp6p_m.h"
#include "robot/irp6ot_tfg/mp_r_irp6ot_tfg.h"
#include "robot/irp6p_tfg/mp_r_irp6p_tfg.h"

namespace mrrocpp {
namespace mp {
namespace task {

task* return_created_mp_task(lib::configurator &_config)
{
	return new edge_follow_mr(_config);
}

edge_follow_mr::edge_follow_mr(lib::configurator &_config) :
	task(_config)
{
}

// powolanie robotow w zaleznosci od zawartosci pliku konfiguracyjnego
void edge_follow_mr::create_robots()
{
	ACTIVATE_MP_ROBOT(irp6ot_tfg);
	ACTIVATE_MP_ROBOT(irp6ot_m);
	ACTIVATE_MP_ROBOT(irp6p_tfg);
	ACTIVATE_MP_ROBOT(irp6p_m);

}

void edge_follow_mr::main_task_algorithm(void)
{

	sr_ecp_msg->message("New edge_follow_mr series");

	std::stringstream ss(std::stringstream::in | std::stringstream::out);

	lib::Xyz_Euler_Zyz_vector rel_eu(0, 0, 0, -1.57, 1.57, 1.57);
	lib::Homog_matrix tmp_hm(rel_eu);
	lib::Xyz_Angle_Axis_vector rel_aa;
	tmp_hm.get_xyz_angle_axis(rel_aa);

	ss << rel_aa;

	sr_ecp_msg->message(ss.str().c_str());

	// wybor manipulatora do sterowania na podstawie konfiguracji

	lib::robot_name_t manipulator_name;
	lib::robot_name_t gripper_name;

	// ROBOT IRP6_ON_TRACK
	if (config.exists_and_true("is_active", "[edp_irp6ot_m]")) {
		manipulator_name = lib::irp6ot_m::ROBOT_NAME;
		if (config.exists_and_true("is_active", "[edp_irp6ot_tfg]")) {
			gripper_name = lib::irp6ot_tfg::ROBOT_NAME;
		} else {
			// TODO: throw
		}
	} else if (config.exists_and_true("is_active", "[edp_irp6p_m]")) {
		manipulator_name = lib::irp6p_m::ROBOT_NAME;
		if (config.exists_and_true("is_active", "[edp_irp6p_tfg]")) {
			gripper_name = lib::irp6p_tfg::ROBOT_NAME;
		} else {
			// TODO: throw
		}
	} else {
		// TODO: throw
	}

	// sekwencja generator na wybranym chwytaku

	char tmp_string[lib::MP_2_ECP_NEXT_STATE_STRING_SIZE];

	lib::irp6_tfg::mp_to_ecp_parameters mp_ecp_command;

	mp_ecp_command.desired_position = 0.078;

	memcpy(tmp_string, &mp_ecp_command, sizeof(mp_ecp_command));
	/*

	 set_next_ecp_state(ecp_mp::generator::ECP_GEN_TFG, (int) 5, tmp_string, sizeof(mp_ecp_command), gripper_name);

	 wait_for_task_termination(false, 1, gripper_name.c_str());

	 */

	// sekwencja generator na wybranym manipulatorze

	set_next_ecp_state(ecp_mp::sub_task::ECP_ST_BIAS_EDP_FORCE, (int) 5, "", 0, manipulator_name);

	wait_for_task_termination(false, 1, manipulator_name.c_str());

	set_next_ecp_state(ecp_mp::sub_task::ECP_ST_TFF_NOSE_RUN, (int) 5, "", 0, manipulator_name);

	wait_for_task_termination(false, 1, manipulator_name.c_str());

	set_next_ecp_state(ecp_mp::sub_task::EDGE_FOLLOW, (int) 5, "", 0, manipulator_name);

	wait_for_task_termination(false, 1, manipulator_name.c_str());

	sr_ecp_msg->message("END");

}

} // namespace task
} // namespace mp
} // namespace mrrocpp
