/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 2.01  */

#include "ui_r_irp6p_tfg.h"
#include "../base/ui_ecp_robot/ui_ecp_r_common.h"
#include "robot/irp6p_tfg/const_irp6p_tfg.h"
#include "../base/interface.h"

#include "../base/mainwindow.h"
#include "ui_mainwindow.h"

#include "../base/wgt_single_motor_move.h"

namespace mrrocpp {
namespace ui {
namespace irp6p_tfg {
const std::string WGT_IRP6P_TFG_MOVE = "WGT_IRP6P_TFG_MOVE";
//
//
// KLASA UiRobot
//
//

int UiRobot::ui_get_edp_pid()
{
	return ui_ecp_robot->ecp->get_EDP_pid();
}

void UiRobot::ui_get_controler_state(lib::controller_state_t & robot_controller_initial_state_l)
{
	ui_ecp_robot->get_controller_state(robot_controller_initial_state_l);

}

int UiRobot::create_ui_ecp_robot()
{
	ui_ecp_robot = new ui::common::EcpRobot(*this);
	return 1;

}

int UiRobot::edp_create_int_extra_operations()
{
	wgt_move->synchro_depended_init();
	return 1;
}

int UiRobot::synchronise()

{

	eb.command(boost::bind(&ui::irp6p_tfg::UiRobot::synchronise_int, &(*this)));

	return 1;

}

int UiRobot::move_to_preset_position(int variant)
{

	for (int i = 0; i < number_of_servos; i++) {
		desired_pos[i] = state.edp.preset_position[variant][i];
	}
	eb.command(boost::bind(&ui::irp6p_tfg::UiRobot::execute_joint_motion, &(*this)));

	return 1;
}

int UiRobot::move_to_synchro_position()
{

	for (int i = 0; i < number_of_servos; i++) {
		desired_pos[i] = 0.0;
	}
	eb.command(boost::bind(&ui::irp6p_tfg::UiRobot::execute_motor_motion, &(*this)));

	return 1;
}

int UiRobot::execute_motor_motion()
{
	try {

		ui_ecp_robot->move_motors(desired_pos);

	} // end try
	CATCH_SECTION_IN_ROBOT

	return 1;
}

int UiRobot::execute_joint_motion()
{
	try {

		ui_ecp_robot->move_joints(desired_pos);

	} // end try
	CATCH_SECTION_IN_ROBOT

	return 1;
}

int UiRobot::synchronise_int()

{

	interface.set_ui_state_notification(UI_N_SYNCHRONISATION);

	// wychwytania ew. bledow ECP::robot
	try {
		// dla robota irp6_on_track

		if ((state.edp.state > 0) && (state.edp.is_synchronised == false)) {
			ui_ecp_robot->ecp->synchronise();
			state.edp.is_synchronised = ui_ecp_robot->ecp->is_synchronised();
		} else {
			// 	printf("edp irp6_on_track niepowolane, synchronizacja niedozwolona\n");
		}

	} // end try
	CATCH_SECTION_IN_ROBOT

	// modyfikacje menu
	interface.manage_interface();
	wgt_move->synchro_depended_init();
	wgt_move->init_and_copy();
	return 1;

}

UiRobot::UiRobot(common::Interface& _interface) :
			single_motor::UiRobot(_interface, lib::irp6p_tfg::ROBOT_NAME, lib::irp6p_tfg::NUM_OF_SERVOS)

{

	wgt_move = new wgt_single_motor_move("Irp6p_tfg moves", interface, *this, interface.get_main_window());
	wndbase_m[WGT_IRP6P_TFG_MOVE] = wgt_move->dwgt;

}

int UiRobot::manage_interface()
{

	MainWindow *mw = interface.get_main_window();

	switch (state.edp.state)
	{
		case -1:
			mw->enable_menu_item(false, 1, mw->getMenuBar()->menuIrp6p_tfg);

			break;
		case 0:
			mw->enable_menu_item(false, 3, mw->getMenuBar()->actionirp6p_tfg_EDP_Unload, mw->getMenuBar()->actionirp6p_tfg_Synchronization, mw->getMenuBar()->actionirp6p_tfg_Move);
			mw->enable_menu_item(false, 1, mw->getMenuBar()->menuirp6p_tfg_Preset_Positions);
			mw->enable_menu_item(true, 1, mw->getMenuBar()->menuIrp6p_tfg);
			mw->enable_menu_item(true, 1, mw->getMenuBar()->actionirp6p_tfg_EDP_Load);

			break;
		case 1:
		case 2:
			mw->enable_menu_item(true, 1, mw->getMenuBar()->menuIrp6p_tfg);

			// jesli robot jest zsynchronizowany
			if (state.edp.is_synchronised) {
				mw->enable_menu_item(false, 1, mw->getMenuBar()->actionirp6p_tfg_Synchronization);
				mw->enable_menu_item(true, 1, mw->getMenuBar()->menuall_Preset_Positions);

				switch (interface.mp.state)
				{
					case common::UI_MP_NOT_PERMITED_TO_RUN:
					case common::UI_MP_PERMITED_TO_RUN:
						mw->enable_menu_item(true, 2, mw->getMenuBar()->actionirp6p_tfg_EDP_Unload, mw->getMenuBar()->actionirp6p_tfg_Move);
						mw->enable_menu_item(true, 1, mw->getMenuBar()->menuirp6p_tfg_Preset_Positions);
						mw->enable_menu_item(false, 1, mw->getMenuBar()->actionirp6p_tfg_EDP_Load);

						break;
					case common::UI_MP_WAITING_FOR_START_PULSE:
						mw->enable_menu_item(true, 1, mw->getMenuBar()->actionirp6p_tfg_Move);
						mw->enable_menu_item(true, 1, mw->getMenuBar()->menuirp6p_tfg_Preset_Positions);
						mw->enable_menu_item(false, 2, mw->getMenuBar()->actionirp6p_tfg_EDP_Load, mw->getMenuBar()->actionirp6p_tfg_EDP_Unload);

						break;
					case common::UI_MP_TASK_RUNNING:
					case common::UI_MP_TASK_PAUSED:
						mw->enable_menu_item(false, 1, mw->getMenuBar()->menuirp6p_tfg_Preset_Positions);
						mw->enable_menu_item(false, 1, mw->getMenuBar()->actionirp6p_tfg_Move);

						break;
					default:
						break;
				}
			} else // jesli robot jest niezsynchronizowany
			{
				mw->enable_menu_item(true, 3, mw->getMenuBar()->actionirp6p_tfg_EDP_Unload, mw->getMenuBar()->actionirp6p_tfg_Synchronization, mw->getMenuBar()->actionirp6p_tfg_Move);
				mw->enable_menu_item(false, 1, mw->getMenuBar()->actionirp6p_tfg_EDP_Load);

			}
			break;
		default:
			break;
	}

	return 1;
}

}
} //namespace ui
} //namespace mrrocpp

