/*
 * generator/ecp_g_bird_hand.cc
 *
 *Author: yoyek
 */

#include "ecp_g_birdhand_graspit.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace generator {

//constructor with parameters: task and time to sleep [s]
bird_hand::bird_hand(common::task::task& _ecp_task) :
	generator(_ecp_task) {
	bird_hand_command_data_port = the_robot->port_manager.get_port<
			lib::bird_hand_command> (BIRD_HAND_COMMAND_DATA_PORT);

	bird_hand_configuration_command_data_port
			= the_robot->port_manager.get_port<lib::bird_hand_configuration> (
					BIRD_HAND_CONFIGURATION_DATA_PORT);

	bird_hand_status_reply_data_request_port
			= the_robot->port_manager.get_request_port<lib::bird_hand_status> (
					BIRD_HAND_STATUS_DATA_REQUEST_PORT);

	bird_hand_configuration_reply_data_request_port
			= the_robot->port_manager.get_request_port<
					lib::bird_hand_configuration> (
					BIRD_HAND_CONFIGURATION_DATA_REQUEST_PORT);

	max_v = 8000.0 / 275.0 / 7.826 / 60.0;
}

void bird_hand::create_ecp_mp_reply() {

}

void bird_hand::get_mp_ecp_command() {

	memcpy(&bird_hand_command_structure,
			ecp_t.mp_command.ecp_next_state.mp_2_ecp_next_state_string,
			sizeof(bird_hand_command_structure));
}

bool bird_hand::first_step() {

	// parameters copying
	get_mp_ecp_command();

	//bird_hand_configuration_command_data_port->set(bird_hand_configuration_command_structure);

	bird_hand_command_structure.thumb_f[0].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.thumb_f[1].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.index_f[0].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.index_f[1].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.index_f[2].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.ring_f[0].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.ring_f[1].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;
	bird_hand_command_structure.ring_f[2].profile_type = mrrocpp::lib::BIRD_HAND_MACROSTEP_POSITION_INCREMENT;

	bird_hand_command_structure.thumb_f[0].desired_torque = 0;
	bird_hand_command_structure.thumb_f[1].desired_torque = 0;
	bird_hand_command_structure.index_f[0].desired_torque = 0;
	bird_hand_command_structure.index_f[1].desired_torque = 0;
	bird_hand_command_structure.index_f[2].desired_torque = 0;
	bird_hand_command_structure.ring_f[0].desired_torque = 0;
	bird_hand_command_structure.ring_f[1].desired_torque = 0;
	bird_hand_command_structure.ring_f[2].desired_torque = 0;

	bird_hand_command_structure.thumb_f[0].reciprocal_of_damping = 0;
	bird_hand_command_structure.thumb_f[1].reciprocal_of_damping = 0;
	bird_hand_command_structure.index_f[0].reciprocal_of_damping = 0;
	bird_hand_command_structure.index_f[1].reciprocal_of_damping = 0;
	bird_hand_command_structure.index_f[2].reciprocal_of_damping = 0;
	bird_hand_command_structure.ring_f[0].reciprocal_of_damping = 0;
	bird_hand_command_structure.ring_f[1].reciprocal_of_damping = 0;
	bird_hand_command_structure.ring_f[2].reciprocal_of_damping = 0;

	bird_hand_command_structure.motion_steps = 1000; //1 step = 1ms
	bird_hand_command_structure.ecp_query_step = bird_hand_command_structure.motion_steps - 2;

	bird_hand_command_data_port->set(bird_hand_command_structure);
	bird_hand_status_reply_data_request_port->set_request();

	return true;
}

bool bird_hand::next_step() {

	if (bird_hand_status_reply_data_request_port->get(
			bird_hand_status_reply_structure) == mrrocpp::lib::NewData) {

		std::stringstream ss(std::stringstream::in | std::stringstream::out);
		ss << "\n thumb_f[0].meassured_position: " << bird_hand_status_reply_structure.thumb_f[0].meassured_position;
		ss << "\n thumb_f[1].meassured_position: " << bird_hand_status_reply_structure.thumb_f[1].meassured_position;
		ss << "\n index_f[0].meassured_position: " << bird_hand_status_reply_structure.index_f[0].meassured_position;
		ss << "\n index_f[1].meassured_position: " << bird_hand_status_reply_structure.index_f[1].meassured_position;
		ss << "\n index_f[2].meassured_position: " << bird_hand_status_reply_structure.index_f[2].meassured_position;
		ss << "\n ring_f[0].meassured_position: " << bird_hand_status_reply_structure.ring_f[0].meassured_position;
		ss << "\n ring_f[1].meassured_position: " << bird_hand_status_reply_structure.ring_f[1].meassured_position;
		ss << "\n ring_f[2].meassured_position: " << bird_hand_status_reply_structure.ring_f[2].meassured_position;
		ecp_t.sr_ecp_msg->message(ss.str().c_str());
	}

	bird_hand_configuration_reply_data_request_port->get(
			bird_hand_configuration_reply_structure);

	bird_hand_command_data_port->set(bird_hand_command_structure);
	bird_hand_status_reply_data_request_port->set_request();
	bird_hand_configuration_reply_data_request_port->set_request();
	if (node_counter<10)
		return true;
	return false;

}

} // namespace generator
} // namespace common
} // namespace ecp
} // namespace mrrocpp

