#include <vector>

#include "base/lib/typedefs.h"
#include "base/lib/impconst.h"
#include "base/lib/com_buf.h"

#include "base/lib/sr/srlib.h"
#include "application/generator_tester/ecp_st_spline_gen_test.h"
#include "generator/ecp/ecp_g_spline.h"

#include "robot/irp6ot_m/const_irp6ot_m.h"
#include "robot/irp6p_m/const_irp6p_m.h"
#include "robot/polycrank/const_polycrank.h"
#include "robot/conveyor/const_conveyor.h"

#include "base/ecp/ecp_task.h"

namespace mrrocpp {
namespace ecp {
namespace common {
namespace sub_task {

sub_task_spline_gen_test::sub_task_spline_gen_test(task::task & _ecp_t) :
        sub_task(_ecp_t)
{

        if (_ecp_t.ecp_m_robot->robot_name == lib::irp6p_m::ROBOT_NAME) {
                cvgenjoint = new generator::spline(ecp_t, lib::ECP_JOINT, 6);
                cvgenjoint->set_debug(true);
                //cvgenjoint->setType(cubic);

                cvgenmotor = new generator::spline(ecp_t, lib::ECP_MOTOR, 6);
                cvgenmotor->set_debug(true);

                track = false;
                postument = true;
                poly = false;
                conv = false;

                cvgeneuler = new generator::spline(ecp_t, lib::ECP_XYZ_EULER_ZYZ, 6);
                cvgeneuler->set_debug(true);

                cvgenangle = new generator::spline(ecp_t, lib::ECP_XYZ_ANGLE_AXIS, 6);
                cvgenangle->set_debug(true);

        } else if (_ecp_t.ecp_m_robot->robot_name == lib::irp6ot_m::ROBOT_NAME) {
                cvgenjoint = new generator::spline(ecp_t, lib::ECP_JOINT, 7);
                cvgenjoint->set_debug(true);

                cvgenmotor = new generator::spline(ecp_t, lib::ECP_MOTOR, 7);
                cvgenmotor->set_debug(true);

                track = true;
                postument = false;
                poly = false;
                conv = false;

                cvgeneuler = new generator::spline(ecp_t, lib::ECP_XYZ_EULER_ZYZ, 6);
                cvgeneuler->set_debug(true);

                cvgenangle = new generator::spline(ecp_t, lib::ECP_XYZ_ANGLE_AXIS, 6);
                cvgenangle->set_debug(true);

        } else if (_ecp_t.ecp_m_robot->robot_name == lib::polycrank::ROBOT_NAME) {
                cvgenjoint = new generator::spline(ecp_t, lib::ECP_JOINT, 7);
                cvgenjoint->set_debug(true);

                cvgenmotor = new generator::spline(ecp_t, lib::ECP_MOTOR, 7);
                cvgenmotor->set_debug(true);

                track = false;
                postument = false;
                poly = true;
                conv = false;

                cvgeneuler = new generator::spline(ecp_t, lib::ECP_XYZ_EULER_ZYZ, 6);
                cvgeneuler->set_debug(true);

                cvgenangle = new generator::spline(ecp_t, lib::ECP_XYZ_ANGLE_AXIS, 6);
                cvgenangle->set_debug(true);

        } else if (_ecp_t.ecp_m_robot->robot_name == lib::conveyor::ROBOT_NAME) {
                cvgenjoint = new generator::spline(ecp_t, lib::ECP_JOINT, 1);
                cvgenjoint->set_debug(true);

                cvgenmotor = new generator::spline(ecp_t, lib::ECP_MOTOR, 1);
                cvgenmotor->set_debug(true);

                track = false;
                postument = false;
                poly = false;
                conv = true;

                cvgeneuler = new generator::spline(ecp_t, lib::ECP_XYZ_EULER_ZYZ, 1);
                cvgeneuler->set_debug(true);

                cvgenangle = new generator::spline(ecp_t, lib::ECP_XYZ_ANGLE_AXIS, 1);
                cvgenangle->set_debug(true);
        }


}

void sub_task_spline_gen_test::conditional_execution()
{

        std::vector <double> coordinates1(6);//postument
        std::vector <double> coordinates2(7);//track
        std::vector <double> coordinates3(7);//polycrank
        std::vector <double> coordinates4(1);//conveyor

        // JOINT ABSOLUTE
        sr_ecp_msg.message("Joint absolute");

        cvgenjoint->reset();
        cvgenjoint->set_absolute();

        if (track) {
                coordinates2[0] = 0.1;
                coordinates2[1] = -0.067;
                coordinates2[2] = -1.342;
                coordinates2[3] = -0.064;
                coordinates2[4] = 1.109;
                coordinates2[5] = 1.573;
                coordinates2[6] = -2.664;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = -0.104;
                coordinates1[1] = -1.542;
                coordinates1[2] = 0.020;
                coordinates1[3] = 1.404;
                coordinates1[4] = 3.358;
                coordinates1[5] = -2.538;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates1);
        } else if (poly) {
                coordinates3[0] = 1.500;
                coordinates3[1] = 1.500;
                coordinates3[2] = 1.500;
                coordinates3[3] = 1.500;
                coordinates3[4] = 1.500;
                coordinates3[5] = 1.500;
                coordinates3[6] = 1.500;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates3);
        } else if (conv) {
                coordinates4[0] = 1.500;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates4);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = -0.087;
                coordinates2[2] = -1.542;
                coordinates2[3] = -0.044;
                coordinates2[4] = 1.119;
                coordinates2[5] = 4.173;
                coordinates2[6] = -2.664;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = -0.104;
                coordinates1[1] = -1.342;
                coordinates1[2] = 0.020;
                coordinates1[3] = 1.034;
                coordinates1[4] = 3.458;
                coordinates1[5] = -2.738;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates1);
        } else if (poly) {
                coordinates3[0] = 1.000;
                coordinates3[1] = 1.000;
                coordinates3[2] = 1.000;
                coordinates3[3] = 1.000;
                coordinates3[4] = 1.000;
                coordinates3[5] = 1.000;
                coordinates3[6] = 1.000;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates3);
        } else if (conv) {
                coordinates4[0] = 1.000;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates4);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = -0.087;
                coordinates2[2] = -1.542;
                coordinates2[3] = 0.024;
                coordinates2[4] = 1.219;
                coordinates2[5] = 4.173;
                coordinates2[6] = -2.664;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = -0.104;
                coordinates1[1] = -1.542;
                coordinates1[2] = 0.020;
                coordinates1[3] = 1.134;
                coordinates1[4] = 3.658;
                coordinates1[5] = -2.738;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates1);
        } else if (poly) {
                coordinates3[0] = 0.500;
                coordinates3[1] = 0.500;
                coordinates3[2] = 0.500;
                coordinates3[3] = 0.500;
                coordinates3[4] = 0.500;
                coordinates3[5] = 0.500;
                coordinates3[6] = 0.500;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates3);
        } else if (conv) {
                coordinates4[0] = 0.500;
                cvgenjoint->load_absolute_joint_trajectory_pose(coordinates4);
        }

        if (cvgenjoint->calculate_interpolate()) {
                cvgenjoint->Move();
        }
        // JOINT ABSOLUTE END

        /*// JOINT RELATIVE
        sr_ecp_msg.message("Joint relative");
        cvgenjoint->reset();
        cvgenjoint->set_relative();

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = 0.1;
                coordinates2[2] = 0.0;
                coordinates2[3] = -0.2;
                coordinates2[4] = 0.0;
                coordinates2[5] = 0.0;
                coordinates2[6] = 0.0;
                cvgenjoint->load_relative_joint_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.1;
                coordinates1[1] = 0.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.0;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
                cvgenjoint->load_relative_joint_trajectory_pose(coordinates1);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = -0.2;
                coordinates2[2] = 0.0;
                coordinates2[3] = 0.1;
                coordinates2[4] = 0.0;
                coordinates2[5] = 0.1;
                coordinates2[6] = 0.0;
                cvgenjoint->load_relative_joint_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.2;
                coordinates1[1] = 0.1;
                coordinates1[2] = -0.1;
                coordinates1[3] = 0.0;
                coordinates1[4] = 0.6;
                coordinates1[5] = 0.0;
                cvgenjoint->load_relative_joint_trajectory_pose(coordinates1);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = 0.1;
                coordinates2[2] = 0.0;
                coordinates2[3] = 0.1;
                coordinates2[4] = 0.0;
                coordinates2[5] = -0.1;
                coordinates2[6] = 0.0;
                cvgenjoint->load_relative_joint_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = -0.3;
                coordinates1[1] = -0.1;
                coordinates1[2] = 0.1;
                coordinates1[3] = 0.0;
                coordinates1[4] = -0.6;
                coordinates1[5] = 0.0;
                cvgenjoint->load_relative_joint_trajectory_pose(coordinates1);
        }

        if (cvgenjoint->calculate_interpolate()) {
                cvgenjoint->Move();
        }
        // JOINT RELATIVE END


        // MOTOR ABSOLUTE
        sr_ecp_msg.message("Motor absolute");
        cvgenmotor->reset();
        cvgenmotor->set_absolute();

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = 20.0;
                coordinates2[2] = 5.0;
                coordinates2[3] = 0.0;
                coordinates2[4] = 20.0;
                coordinates2[5] = 0.0;
                coordinates2[6] = 0.0;
                cvgenmotor->load_absolute_motor_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 20.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.0;
                coordinates1[4] = 20.0;
                coordinates1[5] = 0.0;
                cvgenmotor->load_absolute_motor_trajectory_pose(coordinates1);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = 10.0;
                coordinates2[2] = 10.0;
                coordinates2[3] = 0.0;
                coordinates2[4] = 0.0;
                coordinates2[5] = 20.0;
                coordinates2[6] = 0.0;
                cvgenmotor->load_absolute_motor_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = 50.0;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
                cvgenmotor->load_absolute_motor_trajectory_pose(coordinates1);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = 0.0;
                coordinates2[2] = 0.0;
                coordinates2[3] = 0.0;
                coordinates2[4] = 0.0;
                coordinates2[5] = 0.0;
                coordinates2[6] = 0.0;
                cvgenmotor->load_absolute_motor_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -10.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.0;
                coordinates1[4] = 15.0;
                coordinates1[5] = 0.0;
                cvgenmotor->load_absolute_motor_trajectory_pose(coordinates1);
        }

        if (cvgenmotor->calculate_interpolate()) {
                cvgenmotor->Move();
        }
        // MOTOR ABSOLUTE END


        // MOTOR RELATIVE
        sr_ecp_msg.message("Motor relative");
        cvgenmotor->reset();
        cvgenmotor->set_relative();

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = 20.0;
                coordinates2[2] = 0.0;
                coordinates2[3] = 0.0;
                coordinates2[4] = 20.0;
                coordinates2[5] = 0.0;
                coordinates2[6] = 0.0;
                cvgenmotor->load_relative_motor_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 20.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.0;
                coordinates1[4] = 20.0;
                coordinates1[5] = 0.0;
                cvgenmotor->load_relative_motor_trajectory_pose(coordinates1);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = -10.0;
                coordinates2[2] = 0.0;
                coordinates2[3] = 50.0;
                coordinates2[4] = -20.0;
                coordinates2[5] = 0.0;
                coordinates2[6] = 0.0;
                cvgenjoint->load_relative_motor_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -10.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = 50.0;
                coordinates1[4] = -20.0;
                coordinates1[5] = 0.0;
                cvgenmotor->load_relative_motor_trajectory_pose(coordinates1);
        }

        if (track) {
                coordinates2[0] = 0.0;
                coordinates2[1] = -10.0;
                coordinates2[2] = 0.0;
                coordinates2[3] = -50.0;
                coordinates2[4] = -0.0;
                coordinates2[5] = 0.0;
                coordinates2[6] = 0.0;
                cvgenmotor->load_relative_motor_trajectory_pose(coordinates2);
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -10.0;
                coordinates1[2] = 0.0;
                coordinates1[3] = -50.0;
                coordinates1[4] = -0.0;
                coordinates1[5] = 0.0;
                cvgenmotor->load_relative_motor_trajectory_pose(coordinates1);
        }

        if (cvgenmotor->calculate_interpolate()) {
                cvgenmotor->Move();
        }
        // MOTOR RELATIVE END


        // EULER ABSOLUTE
        sr_ecp_msg.message("Euler absolute");
        cvgeneuler->reset();
        cvgeneuler->set_absolute();

        if (track) {
                coordinates1[0] = 0.534991;
                coordinates1[1] = -0.136314;
                coordinates1[2] = 0.186314;
                coordinates1[3] = -2.602063;
                coordinates1[4] = 1.871544;
                coordinates1[5] = 2.204729;
        } else if (postument) {
                coordinates1[0] = 0.529991;
                coordinates1[1] = 1.706314;
                coordinates1[2] = 0.178314;
                coordinates1[3] = -2.185063;
                coordinates1[4] = 1.666544;
                coordinates1[5] = 2.328729;
        }
        cvgeneuler->load_absolute_euler_zyz_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.534991;
                coordinates1[1] = -0.156314;
                coordinates1[2] = 0.186314;
                coordinates1[3] = -2.662063;
                coordinates1[4] = 1.871544;
                coordinates1[5] = 2.234729;
        } else if (postument) {
                coordinates1[0] = 0.529991;
                coordinates1[1] = 1.7506314;
                coordinates1[2] = 0.178314;
                coordinates1[3] = -2.185063;
                coordinates1[4] = 1.566544;
                coordinates1[5] = 2.328729;
        }
        cvgeneuler->load_absolute_euler_zyz_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.534991;
                coordinates1[1] = -0.176314;
                coordinates1[2] = 0.186314;
                coordinates1[3] = -2.662063;
                coordinates1[4] = 1.871544;
                coordinates1[5] = 2.234729;
        } else if (postument) {
                coordinates1[0] = 0.529991;
                coordinates1[1] = 1.806314;
                coordinates1[2] = 0.178314;
                coordinates1[3] = -2.185063;
                coordinates1[4] = 1.766544;
                coordinates1[5] = 2.328729;
        }
        cvgeneuler->load_absolute_euler_zyz_trajectory_pose(coordinates1);

        if (cvgeneuler->calculate_interpolate()) {
                cvgeneuler->Move();
        }
        // EULER ABSOLUTE END


        // EULER RELATIVE
        sr_ecp_msg.message("Euler relative");
        cvgeneuler->reset();
        cvgeneuler->set_relative();

        if (track) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.1;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.15;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.1;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.15;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        }
        cvgeneuler->load_relative_euler_zyz_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -0.1;
                coordinates1[2] = 0.1;
                coordinates1[3] = -0.15;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -0.1;
                coordinates1[2] = 0.1;
                coordinates1[3] = -0.15;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        }
        cvgeneuler->load_relative_euler_zyz_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.0;
                coordinates1[2] = -0.1;
                coordinates1[3] = 0.0;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.0;
                coordinates1[2] = -0.1;
                coordinates1[3] = 0.0;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        }
        cvgeneuler->load_relative_euler_zyz_trajectory_pose(coordinates1);

        if (cvgeneuler->calculate_interpolate()) {
                cvgeneuler->Move();
        }
        // EULER RELATIVE END


        // ANGLE AXIS ABSOLUTE
        sr_ecp_msg.message("Angle axis absolute");
        cvgenangle->reset();
        cvgenangle->set_absolute();

        if (track) {
                coordinates1[0] = 0.534987;
                coordinates1[1] = -0.176317;
                coordinates1[2] = 0.180306;
                coordinates1[3] = 1.000713;
                coordinates1[4] = -1.447889;
                coordinates1[5] = -0.264191;
        } else if (postument) {
                coordinates1[0] = 0.529987;
                coordinates1[1] = 1.606317;
                coordinates1[2] = 0.178306;
                coordinates1[3] = 1.267713;
                coordinates1[4] = -1.219889;
                coordinates1[5] = 0.114191;
        }
        cvgenangle->load_absolute_angle_axis_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.504987;
                coordinates1[1] = -0.146317;
                coordinates1[2] = 0.106306;
                coordinates1[3] = 1.103713;
                coordinates1[4] = -1.407889;
                coordinates1[5] = -0.294191;
        } else if (postument) {
                coordinates1[0] = 0.509987;
                coordinates1[1] = 1.806317;
                coordinates1[2] = 0.148306;
                coordinates1[3] = 1.367713;
                coordinates1[4] = -1.119889;
                coordinates1[5] = 0.114191;
        }
        cvgenangle->load_absolute_angle_axis_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.534987;
                coordinates1[1] = -0.176317;
                coordinates1[2] = 0.186306;
                coordinates1[3] = 1.203713;
                coordinates1[4] = -1.447889;
                coordinates1[5] = -0.294191;
        } else if (postument) {
                coordinates1[0] = 0.529987;
                coordinates1[1] = 1.806317;
                coordinates1[2] = 0.178306;
                coordinates1[3] = 1.367713;
                coordinates1[4] = -1.119889;
                coordinates1[5] = 0.104191;
        }
        cvgenangle->load_absolute_angle_axis_trajectory_pose(coordinates1);

        if (cvgenangle->calculate_interpolate()) {
                cvgenangle->Move();
        }
        // ANGLE AXIS ABSOLUTE END


        // ANGLE AXIS RELATIVE
        sr_ecp_msg.message("Angle axis relative");
        cvgenangle->reset();
        cvgenangle->set_relative();

        if (track) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.1;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.05;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.1;
                coordinates1[2] = 0.0;
                coordinates1[3] = 0.05;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        }
        cvgenangle->load_relative_angle_axis_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -0.1;
                coordinates1[2] = 0.1;
                coordinates1[3] = -0.05;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = -0.1;
                coordinates1[2] = 0.1;
                coordinates1[3] = -0.05;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        }
        cvgenangle->load_relative_angle_axis_trajectory_pose(coordinates1);

        if (track) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.0;
                coordinates1[2] = -0.1;
                coordinates1[3] = 0.0;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        } else if (postument) {
                coordinates1[0] = 0.0;
                coordinates1[1] = 0.0;
                coordinates1[2] = -0.1;
                coordinates1[3] = 0.0;
                coordinates1[4] = 0.0;
                coordinates1[5] = 0.0;
        }
        cvgenangle->load_relative_angle_axis_trajectory_pose(coordinates1);

        if (cvgenangle->calculate_interpolate()) {
                cvgenangle->Move();
        }
        // ANGLE AXIS RELATIVE END*/
        sr_ecp_msg.message("Spline test END");
}

sub_task_spline_gen_test::~sub_task_spline_gen_test()
{
        delete cvgenjoint;
        delete cvgenmotor;
        delete cvgeneuler;
        delete cvgenangle;
}

} // namespace task
} // namespace common
} // namespace ecp
} // namespace mrrocpp

