#include <cstdio>

#include "base/lib/typedefs.h"
#include "base/lib/impconst.h"
#include "base/lib/com_buf.h"
#include "base/lib/mrmath/mrmath.h"

// Klasa edp_irp6ot_effector.
#include "edp_e_sbench.h"
#include "base/edp/reader.h"
// Kinematyki.
#include "robot/sbench/kinematic_model_sbench.h"
#include "base/edp/manip_trans_t.h"
#include "base/edp/vis_server.h"

#include "base/lib/exception.h"
using namespace mrrocpp::lib::exception;

namespace mrrocpp {
namespace edp {
namespace sbench {

void effector::master_order(common::MT_ORDER nm_task, int nm_tryb)
{
	motor_driven_effector::single_thread_master_order(nm_task, nm_tryb);
}

// Konstruktor.
effector::effector(common::shell &_shell) :
		motor_driven_effector(_shell, lib::sbench::ROBOT_NAME, instruction, reply), dev_name("/dev/comedi0")
{

	number_of_servos = lib::sbench::NUM_OF_SERVOS;
	//  Stworzenie listy dostepnych kinematyk.
	create_kinematic_models_for_given_robot();

	reset_variables();

	if (!robot_test_mode) {

		// initiate hardware
		device = comedi_open(dev_name.c_str());

		if (!device) {

			throw std::runtime_error("Could not open device");
		}

	} else {
		current_pins_buf.set_zeros();
	}

}

void effector::get_controller_state(lib::c_buffer &instruction)
{

	if (robot_test_mode) {
		controller_state_edp_buf.is_synchronised = true;
	} else {
		controller_state_edp_buf.is_synchronised = true;
	}

	//printf("get_controller_state: %d\n", controller_state_edp_buf.is_synchronised); fflush(stdout);
	reply.controller_state = controller_state_edp_buf;

	/*
	 // aktualizacja pozycji robota
	 // Uformowanie rozkazu odczytu dla SERVO_GROUP
	 sb->servo_command.instruction_code = lib::READ;
	 // Wyslanie rozkazu do SERVO_GROUP
	 // Pobranie z SERVO_GROUP aktualnej pozycji silnikow
	 //	printf("get_arm_position read_hardware\n");

	 sb->send_to_SERVO_GROUP();
	 */
	// dla pierwszego wypelnienia current_joints
	get_current_kinematic_model()->mp2i_transform(current_motor_pos, current_joints);

	{
		boost::mutex::scoped_lock lock(effector_mutex);

		// Ustawienie poprzedniej wartosci zadanej na obecnie odczytane polozenie walow silnikow
		for (int i = 0; i < number_of_servos; i++) {
			servo_current_motor_pos[i] = desired_motor_pos_new[i] = desired_motor_pos_old[i] = current_motor_pos[i];
			desired_joints[i] = current_joints[i];
		}
	}
}

/*--------------------------------------------------------------------------*/
void effector::move_arm(const lib::c_buffer &instruction)
{

	lib::sbench::c_buffer & local_instruction = (lib::sbench::c_buffer&) instruction;

	msg->message("move_arm");

	std::stringstream ss(std::stringstream::in | std::stringstream::out);

	lib::sbench::pins_buffer pins_buf;

	memcpy(&pins_buf, &(local_instruction.sbench.pins_buf), sizeof(pins_buf));

	if (robot_test_mode) {
		for (int i = 0; i < lib::sbench::NUM_OF_PINS; i++) {
			if (pins_buf.pins_state[i]) {
				ss << "1";
			} else {
				ss << "0";
			}
		}
		current_pins_buf = pins_buf;
		ss << std::endl;
		msg->message(ss.str());
	} else {

		for (int i = 0; i < lib::sbench::NUM_OF_PINS; i++) {
			comedi_dio_write(device, (int) (i / 32), (i%32), pins_buf.pins_state[i]);
			//	current_pins_state[i] = pins_state[i];
		} // send command to hardware
	}

}

			/*--------------------------------------------------------------------------*/

			/*--------------------------------------------------------------------------*/
void effector::get_arm_position(bool read_hardware, lib::c_buffer &instruction)
{
	msg->message("get_arm");

	//lib::JointArray desired_joints_tmp(lib::MAX_SERVOS_NR); // Wspolrzedne wewnetrzne -
	//	printf(" GET ARM\n");
	//	flushall();
	static int licznikaaa = (-11);

	std::stringstream ss(std::stringstream::in | std::stringstream::out);
	ss << "get_arm_position: " << licznikaaa;
	msg->message(ss.str().c_str());
	//	printf("%s\n", ss.str().c_str());

	if (!robot_test_mode) {

		// read pin_state from hardware

		for (int i = 0; i < lib::sbench::NUM_OF_PINS; i++) {
			unsigned int current_read;
			comedi_dio_read(device, (int) (i / 32), (i%32), &current_read);
			current_pins_buf.pins_state[i] = current_read;
		} // send command to hardware

	}
	reply.sbench.pins_buf = current_pins_buf;

	reply.servo_step = step_counter;
}
/*--------------------------------------------------------------------------*/

// Stworzenie modeli kinematyki dla robota IRp-6 na postumencie.
void effector::create_kinematic_models_for_given_robot(void)
{
	// Stworzenie wszystkich modeli kinematyki.
	add_kinematic_model(new kinematics::sbench::model());
	// Ustawienie aktywnego modelu.
	set_kinematic_model(0);
}

/*--------------------------------------------------------------------------*/
void effector::create_threads()
{
	rb_obj = (boost::shared_ptr <common::reader_buffer>) new common::reader_buffer(*this);
	vis_obj = (boost::shared_ptr <common::vis_server>) new common::vis_server(*this);
}

lib::INSTRUCTION_TYPE effector::variant_receive_instruction()
{
	return receive_instruction(instruction);
}

void effector::variant_reply_to_instruction()
{
	reply_to_instruction(reply);
}

} // namespace smb

namespace common {

effector* return_created_efector(common::shell &_shell)
{
	return new sbench::effector(_shell);
}
}

} // namespace edp
} // namespace mrrocpp

