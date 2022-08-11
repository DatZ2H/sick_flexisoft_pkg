#include <sick_flexisoft_pkg/flexisoft_library.h>
#include <sick_flexisoft_pkg/flexisoft_define.h>
#include <sick_flexisoft_pkg/FlexSetStopOperationalSrv.h>
#include <sick_flexisoft_pkg/FlexSetZoneSrv.h>
#include <sick_flexisoft_pkg/FlexSetMuteReleaseSrv.h>
#include <sick_flexisoft_pkg/FlexSetPayloadSrv.h>
#include <sick_flexisoft_pkg/FlexSetMappingSrv.h>
#include <sick_flexisoft_pkg/MuteCameraSafetySrv.h>

#include <sick_flexisoft_pkg/fx3_saf_protective_fault.h>
#include <sick_flexisoft_pkg/fx3_saf_stop_states.h>
#include <sick_flexisoft_pkg/fx3_saf_stop_operational.h>
#include <sick_flexisoft_pkg/fx3_saf_stop_protective.h>
#include <sick_flexisoft_pkg/fx3_saf_stop_emergency.h>
#include <sick_flexisoft_pkg/fx3_saf_stop_resume.h>
#include <sick_flexisoft_pkg/fx3_saf_status_states.h>
#include <sick_flexisoft_pkg/fx3_saf_protective_field.h>
#include <sick_flexisoft_pkg/fx3_saf_mode_switch.h>
#include <sick_flexisoft_pkg/fx3_saf_safety_system.h>
#include <sick_flexisoft_pkg/m5_out_enc_enable_id.h>

#include "detect_obstacle/fields_safety.h"

 clientSock *Flexisoft = new clientSock("192.168.1.11", 9100);
//clientSock *Flexisoft = new clientSock("192.168.1.100", 1101, true);
ros::Publisher fx3_saf_protective_fault_pub;
ros::Publisher fx3_saf_stop_states_pub;
ros::Publisher fx3_saf_stop_operational_pub;
ros::Publisher fx3_saf_stop_protective_pub;
ros::Publisher fx3_saf_stop_emergency_pub;
ros::Publisher fx3_saf_stop_resume_pub;
ros::Publisher fx3_saf_status_states_pub;
ros::Publisher fx3_saf_protective_field_pub;
ros::Publisher fx3_saf_mode_switch_pub;
ros::Publisher fx3_saf_safety_system_pub;
ros::Publisher m5_out_enc_enable_id_pub;
ros::Publisher use_safety_camera_pub;

sick_flexisoft_pkg::fx3_saf_protective_fault fx3_saf_protective_fault;
sick_flexisoft_pkg::fx3_saf_stop_states fx3_saf_stop_states;
sick_flexisoft_pkg::fx3_saf_stop_operational fx3_saf_stop_operational;
sick_flexisoft_pkg::fx3_saf_stop_protective fx3_saf_stop_protective;
sick_flexisoft_pkg::fx3_saf_stop_emergency fx3_saf_stop_emergency;
sick_flexisoft_pkg::fx3_saf_stop_resume fx3_saf_stop_resume;
sick_flexisoft_pkg::fx3_saf_status_states fx3_saf_status_states;
sick_flexisoft_pkg::fx3_saf_protective_field fx3_saf_protective_field;
sick_flexisoft_pkg::fx3_saf_mode_switch fx3_saf_mode_switch;
sick_flexisoft_pkg::fx3_saf_safety_system fx3_saf_safety_system;
sick_flexisoft_pkg::m5_out_enc_enable_id m5_out_enc_enable_id;
// sick_flexisoft_pkg::MuteCameraSafety MuteCameraSafety;

detect_obstacle::fields_safety fields_safety;

std_msgs::Bool safety_camera;

void fx3_saf_protective_fault_function_pub()
{
    fx3_saf_protective_fault.FAULT_EFI = Flexisoft->read_bit(FX3_SAF_FAULT_EFI);
    fx3_saf_protective_fault.FAULT_MS3 = Flexisoft->read_bit(FX3_SAF_FAULT_MS3);
    fx3_saf_protective_fault.FAULT_GENT = Flexisoft->read_bit(FX3_SAF_FAULT_GENT);
    fx3_saf_protective_fault.FAULT_EDM = Flexisoft->read_bit(FX3_SAF_FAULT_EDM);
    fx3_saf_protective_fault.FAULT_DRIVER = Flexisoft->read_bit(FX3_SAF_FAULT_DRIVER);
    fx3_saf_protective_fault.FAULT_ENC = Flexisoft->read_bit(FX3_SAF_FAULT_ENC);

    fx3_saf_protective_fault_pub.publish(fx3_saf_protective_fault);
}
void fx3_saf_stop_states_function_pub()
{
    fx3_saf_stop_states.STOP_STATES = Flexisoft->read_bit(FX3_SAF_STOP_STATES);
    fx3_saf_stop_states.STOP_OPERATIONAL = Flexisoft->read_bit(FX3_SAF_STOP_OPERATIONAL);
    fx3_saf_stop_states.STOP_MANUAL = Flexisoft->read_bit(FX3_SAF_STOP_MANUAL);
    fx3_saf_stop_states.STOP_PROTECTIVE = Flexisoft->read_bit(FX3_SAF_STOP_PROTECTIVE);
    fx3_saf_stop_states.STOP_EMERGENCY = Flexisoft->read_bit(FX3_SAF_STOP_EMERGENCY);
    fx3_saf_stop_states.STOP_RESUME = Flexisoft->read_bit(FX3_SAF_STOP_RESUME);
    fx3_saf_stop_states_pub.publish(fx3_saf_stop_states);
}
void fx3_saf_stop_operational_function_pub()
{
    fx3_saf_stop_operational.STOP_OPERATIONAL = Flexisoft->read_bit(FX3_SAF_STOP_OPERATIONAL);
    fx3_saf_stop_operational.OPERATIONAL_OBSTACLE = Flexisoft->read_bit(FX3_SAF_OPERATIONAL_OBSTACLE);

    fx3_saf_stop_operational_pub.publish(fx3_saf_stop_operational);
}
void fx3_saf_stop_protective_function_pub()
{
    fx3_saf_stop_protective.PROTECTIVE_FIELD = Flexisoft->read_bit(FX3_SAF_PROTECTIVE_FIELD);
    fx3_saf_stop_protective.PROTECTIVE_MODE = Flexisoft->read_bit(FX3_SAF_PROTECTIVE_MODE);
    fx3_saf_stop_protective.PROTECTIVE_FAULT = Flexisoft->read_bit(FX3_SAF_PROTECTIVE_FAULT);
    fx3_saf_stop_protective.PROTECTIVE_OVERSPEED = Flexisoft->read_bit(FX3_SAF_PROTECTIVE_OVERSPEED);
    fx3_saf_stop_protective.PROTECTIVE_STABILITY = Flexisoft->read_bit(FX3_SAF_PROTECTIVE_STABILITY);
    fx3_saf_stop_protective.PROTECTIVE_SAFEGUARDED = Flexisoft->read_bit(FX3_SAF_PROTECTIVE_SAFEGUARDED);

    fx3_saf_stop_protective_pub.publish(fx3_saf_stop_protective);
}
void fx3_saf_stop_emergency_function_pub()
{
    fx3_saf_stop_emergency.EMERGENCY_EMC = Flexisoft->read_bit(FX3_SAF_EMERGENCY_EMC);
    fx3_saf_stop_emergency.EMERGENCY_BUMPER = Flexisoft->read_bit(FX3_SAF_EMERGENCY_BUMPER);
    fx3_saf_stop_emergency.EMERGENCY_PROXIMITY = Flexisoft->read_bit(FX3_SAF_EMERGENCY_PROXIMITY);
    fx3_saf_stop_emergency.EMERGENCY_SHARED_EMC = Flexisoft->read_bit(FX3_SAF_EMERGENCY_SHARED_EMC);
    fx3_saf_stop_emergency_pub.publish(fx3_saf_stop_emergency);
}
void fx3_saf_stop_resume_function_pub()
{
    fx3_saf_stop_resume.STOP_RESUME = Flexisoft->read_bit(FX3_SAF_STOP_RESUME);
    fx3_saf_stop_resume.IO_START = Flexisoft->read_bit(M3_IN_IO_START);
    fx3_saf_stop_resume.STOP_PROTECTIVE = Flexisoft->read_bit(FX3_SAF_STOP_PROTECTIVE);
    fx3_saf_stop_resume.STOP_EMERGENCY = Flexisoft->read_bit(FX3_SAF_STOP_EMERGENCY);
    fx3_saf_stop_resume.STOP_MANUAL = Flexisoft->read_bit(FX3_SAF_STOP_MANUAL);
    fx3_saf_stop_resume.MODE_LOCK = Flexisoft->read_bit(M3_IN_IO_LOCK);
    fx3_saf_stop_resume_pub.publish(fx3_saf_stop_resume);
}
void fx3_saf_status_states_function_pub()
{
    fx3_saf_status_states.STATUS_PRE_RESUME = Flexisoft->read_bit(FX3_SAF_STATUS_PRE_RESUME);
    fx3_saf_status_states.STOP_RESUME = Flexisoft->read_bit(FX3_SAF_STOP_RESUME);
    fx3_saf_status_states.STATUS_RUNNING = Flexisoft->read_bit(FX3_SAF_STATUS_RUNNING);
    fx3_saf_status_states_pub.publish(fx3_saf_status_states);
}
void fx3_saf_protective_field_function_pub()
{
    // fx3_saf_protective_field.FIELD_POWER = Flexisoft->read_bit();
    fx3_saf_protective_field_pub.publish(fx3_saf_protective_field);
}
void fx3_saf_mode_switch_function_pub()
{

    // fx3_saf_mode_switch_pub.publish();
}
void use_safety_camera_function_pub(bool value)
{
    safety_camera.data = value;
    ROS_INFO("use_safety_camera_function_pub: [%x]", value);
    use_safety_camera_pub.publish(safety_camera);
}
void fx3_saf_safety_system_function_pub()
{
    fx3_saf_safety_system.safety_ready = Flexisoft->read_bit(FX3_SAF_STOP_RESUME);
    fx3_saf_safety_system.safety_good = Flexisoft->read_bit(FX3_SAF_STATUS_RUNNING);
    fx3_saf_safety_system.muted_safety = Flexisoft->read_bit(FX3_SAF_MUTE_RELEASE);
    fx3_saf_safety_system.operator_move = Flexisoft->read_bit(FX3_SAF_STOP_OPERATIONAL);

    fx3_saf_safety_system.device_state.FAULT_EFI = Flexisoft->read_bit(FX3_SAF_FAULT_EFI);
    fx3_saf_safety_system.device_state.FAULT_MS3 = Flexisoft->read_bit(FX3_SAF_FAULT_MS3);
    fx3_saf_safety_system.device_state.FAULT_GENT = Flexisoft->read_bit(FX3_SAF_FAULT_GENT);
    fx3_saf_safety_system.device_state.FAULT_EDM = Flexisoft->read_bit(FX3_SAF_FAULT_EDM);
    fx3_saf_safety_system.device_state.FAULT_DRIVER = Flexisoft->read_bit(FX3_SAF_FAULT_DRIVER);
    fx3_saf_safety_system.device_state.FAULT_ENC = Flexisoft->read_bit(FX3_SAF_FAULT_ENC);

    if (Flexisoft->read_bit(FX3_SAF_MODE_AUTO))
    {
        fx3_saf_safety_system.mode_switch.MODE = 0;
    }
    else if (Flexisoft->read_bit(FX3_SAF_MODE_LOCK))
    {
        fx3_saf_safety_system.mode_switch.MODE = 1;
    }
    else if (Flexisoft->read_bit(FX3_SAF_MODE_MAN))
    {
        fx3_saf_safety_system.mode_switch.MODE = 2;
    }
    else
    {
        fx3_saf_safety_system.mode_switch.MODE = 4;
    }

    if ((Flexisoft->read_bit(FX3_SAF_MS3_DETECTER)) && (Flexisoft->read_bit(FX3_SAF_MS3_WARNER)) && (Flexisoft->read_bit(FX3_SAF_MS3_BRACKER)) && (Flexisoft->read_bit(FX3_SAF_MS3_POWER)))
    {
        fx3_saf_safety_system.laser_field.FIELD = 0;
    }
    else if (!(Flexisoft->read_bit(FX3_SAF_MS3_DETECTER)) && (Flexisoft->read_bit(FX3_SAF_MS3_WARNER)) && (Flexisoft->read_bit(FX3_SAF_MS3_BRACKER)) && (Flexisoft->read_bit(FX3_SAF_MS3_POWER)))
    {
        fx3_saf_safety_system.laser_field.FIELD = 2;
    }
    else if (!(Flexisoft->read_bit(FX3_SAF_MS3_DETECTER)) && !(Flexisoft->read_bit(FX3_SAF_MS3_WARNER)) && (Flexisoft->read_bit(FX3_SAF_MS3_BRACKER)) && (Flexisoft->read_bit(FX3_SAF_MS3_POWER)))
    {
        fx3_saf_safety_system.laser_field.FIELD = 3;
    }
    else if (!(Flexisoft->read_bit(FX3_SAF_MS3_DETECTER)) && !(Flexisoft->read_bit(FX3_SAF_MS3_WARNER)) && !(Flexisoft->read_bit(FX3_SAF_MS3_BRACKER)) && (Flexisoft->read_bit(FX3_SAF_MS3_POWER)))
    {
        fx3_saf_safety_system.laser_field.FIELD = 4;
    }
    else if (!(Flexisoft->read_bit(FX3_SAF_MS3_DETECTER)) && !(Flexisoft->read_bit(FX3_SAF_MS3_WARNER)) && !(Flexisoft->read_bit(FX3_SAF_MS3_BRACKER)) && !(Flexisoft->read_bit(FX3_SAF_MS3_POWER)))
    {
        fx3_saf_safety_system.laser_field.FIELD = 5;
    }

    fx3_saf_safety_system_pub.publish(fx3_saf_safety_system);
}
void m5_out_enc_enable_id_function_pub()
{
    uint8_t speedTarget = Flexisoft->read_half_byte(M5_OUT_ENC_ENABLE_ID_00);

    switch (speedTarget)
    {
    case 1:
        m5_out_enc_enable_id.SPEED = 30;
        break;
    case 2:
        m5_out_enc_enable_id.SPEED = 70;
        break;
    case 3:
        m5_out_enc_enable_id.SPEED = 140;
        break;
    case 4:
        m5_out_enc_enable_id.SPEED = 280;
        break;
    case 5:
        m5_out_enc_enable_id.SPEED = 560;
        break;
    case 6:
        m5_out_enc_enable_id.SPEED = 880;
        break;
    case 7:
        m5_out_enc_enable_id.SPEED = 1200;
        break;
    case 8:
        m5_out_enc_enable_id.SPEED = 1520;
        break;

    default:
        m5_out_enc_enable_id.SPEED = 0;
        break;
    }

    m5_out_enc_enable_id_pub.publish(m5_out_enc_enable_id);
}

void depth_camera_fields_safety_CallBack(const detect_obstacle::fields_safety::ConstPtr &msg)
{
    fields_safety = *msg;
    if (msg->system_good == true)
    {
        if (msg->enable == true)
        {
            if (msg->fields[0] == true)
            {
                fx3_saf_safety_system.camera_field.FIELD = 2;
                Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, false);
            }
            else if (msg->fields[1] == true)
            {
                fx3_saf_safety_system.camera_field.FIELD = 3;
                Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, false);
            }
            else if (msg->fields[2] == true)
            {
                fx3_saf_safety_system.camera_field.FIELD = 4;
                Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, true);
            }
            else
            {
                fx3_saf_safety_system.camera_field.FIELD = 0;
                Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, false);
            }
        }
        else
        {
            fx3_saf_safety_system.camera_field.FIELD = 0;
            Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, false);
        }
    }
    else
    {
        fx3_saf_safety_system.camera_field.FIELD = 0;
        Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, false);
    }
}
void depth_camera_field_safety_fake_muted()
{
    fx3_saf_safety_system.camera_field.FIELD = 0;
        Flexisoft->write_bit(IPC_STOP_OBSTACLE_RELEASE, false);
}

bool ServiceCbFlexSetStopOperationalSrv(sick_flexisoft_pkg::FlexSetStopOperationalSrv::Request &req,
                                        sick_flexisoft_pkg::FlexSetStopOperationalSrv::Response &res)
{
    double secs;
    bool time_out = false;
    secs = ros::Time::now().toSec();
    Flexisoft->flex_write_bit(IPC_STOP_OPERATIONAL_RELEASE, req.STOP_OPERATIONAL);
    while (!time_out)
    {
        if (ros::Time::now().toSec() - secs >= 3)
        {
            time_out = true;
        }
        if (Flexisoft->flex_read_bit(FX3_SAF_STOP_OPERATIONAL) == req.STOP_OPERATIONAL)
        {
            res.success = true;
            ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_STOP_OPERATIONAL));
            ROS_INFO(" FlexSetStopOperationalSrv done");
            return true;
        }
        //
        ros::Duration(0.1).sleep();
    }
    res.success = false;
    return false;
}
bool ServiceCbFlexSetZoneSrv(sick_flexisoft_pkg::FlexSetZoneSrv::Request &req,
                             sick_flexisoft_pkg::FlexSetZoneSrv::Response &res)
{
    double secs;
    bool time_out = false;
    secs = ros::Time::now().toSec();
    ROS_INFO(" FlexSetZoneSrv [%x]", req.ZONE);
    switch (req.ZONE)
    {
    case 0:
        ROS_ERROR(" FlexSetZoneSrv IPC_SAF_ZONE_OPEATING");
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_OPEATING, true);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_HAZARD, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_RESTRICTED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_CONFINED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_LOAD, false);
        while (!time_out)
        {
            if (ros::Time::now().toSec() - secs >= 3)
            {
                time_out = true;
            }
            
            if (Flexisoft->flex_read_bit(FX3_SAF_ZONE_OPEATING) == true)
            {
                res.success = true;
                ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_ZONE_OPEATING));
                ROS_INFO(" FX3_SAF_ZONE_OPEATING done");
                return true;
            }
            //
            ros::Duration(0.1).sleep();
        }
        res.success = false;
        return false;
        break;
    case 1:
        ROS_ERROR(" FlexSetZoneSrv IPC_SAF_ZONE_HAZARD");
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_OPEATING, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_HAZARD, true);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_RESTRICTED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_CONFINED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_LOAD, false);
        while (!time_out)
        {
            if (ros::Time::now().toSec() - secs >= 3)
            {
                time_out = true;
            }

            if (Flexisoft->flex_read_bit(FX3_SAF_ZONE_HAZARD) == true)
            {
                res.success = true;
                ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_ZONE_HAZARD));
                ROS_INFO(" FX3_SAF_ZONE_HAZARD done");
                return true;
            }

            ros::Duration(0.1).sleep();
        }
        res.success = false;
        // return false;
        break;
    case 2:
        ROS_ERROR(" FlexSetZoneSrv IPC_SAF_ZONE_RESTRICTED");
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_OPEATING, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_HAZARD, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_RESTRICTED, true);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_CONFINED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_LOAD, false);
        while (!time_out)
        {
            if (ros::Time::now().toSec() - secs >= 3)
            {
                time_out = true;
            }

            if (Flexisoft->flex_read_bit(FX3_SAF_ZONE_RESTRICTED) == true)
            {
                res.success = true;
                ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_ZONE_RESTRICTED));
                ROS_INFO(" FX3_SAF_ZONE_RESTRICTED done");
                return true;
            }
            //
            ros::Duration(0.1).sleep();
        }
        res.success = false;
        // return false;
        break;
    case 3:
        ROS_ERROR(" FlexSetZoneSrv IPC_SAF_ZONE_CONFINED");
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_OPEATING, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_HAZARD, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_RESTRICTED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_CONFINED, true);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_LOAD, false);
        while (!time_out)
        {
            if (ros::Time::now().toSec() - secs >= 3)
            {
                time_out = true;
            }

            if (Flexisoft->flex_read_bit(FX3_SAF_ZONE_CONFINED) == true)
            {
                res.success = true;
                ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_ZONE_CONFINED));
                ROS_INFO(" FX3_SAF_ZONE_CONFINED");
                return true;
            }
            //
            ros::Duration(0.1).sleep();
        }
        res.success = false;
        // return false;
        break;
    case 4:
        ROS_ERROR(" FlexSetZoneSrv IPC_SAF_ZONE_LOAD");
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_OPEATING, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_HAZARD, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_RESTRICTED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_CONFINED, false);
        Flexisoft->flex_write_bit(IPC_SAF_ZONE_LOAD, true);
        while (!time_out)
        {
            if (ros::Time::now().toSec() - secs >= 3)
            {
                time_out = true;
            }

            if (Flexisoft->flex_read_bit(FX3_SAF_ZONE_LOAD) == true)
            {
                res.success = true;
                ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_ZONE_LOAD));
                ROS_INFO(" FX3_SAF_ZONE_LOAD, done");
                return true;
            }
            //
            ros::Duration(0.1).sleep();
        }
        res.success = false;
        // return false;
        break;

    default:
        break;
    }
}
bool ServiceCbFlexSetMuteReleaseSrv(sick_flexisoft_pkg::FlexSetMuteReleaseSrv::Request &req,
                                    sick_flexisoft_pkg::FlexSetMuteReleaseSrv::Response &res)
{
    double secs;
    bool time_out = false;
    secs = ros::Time::now().toSec();
    Flexisoft->flex_write_bit(IPC_SAF_MUTE_RELEASE, req.MUTE_RELEASE);
    use_safety_camera_function_pub(req.MUTE_RELEASE);
    while (!time_out)
    {
        if (ros::Time::now().toSec() - secs >= 3)
        {
            time_out = true;
        }
        if (Flexisoft->flex_read_bit(FX3_SAF_MUTE_RELEASE) == req.MUTE_RELEASE)
        {
            res.success = true;
            ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_MUTE_RELEASE));
            ROS_INFO(" FlexSetMuteReleaseSrv done");
            return true;
        }
        //
        ros::Duration(0.1).sleep();
    }
    res.success = false;
    return false;
}
bool ServiceCbMuteCameraSafetySrv(sick_flexisoft_pkg::MuteCameraSafetySrv::Request &req,
                                  sick_flexisoft_pkg::MuteCameraSafetySrv::Response &res)
{
    double secs;
    bool time_out = false;
    secs = ros::Time::now().toSec();
    bool value;
    if (req.MUTE_RELEASE)
    {
        value = false;
    }
    else
    {
        value = true;
    }
    use_safety_camera_function_pub(value);
    ROS_INFO(" use_safety_camera_function_pub [%x] done", value);
    while (!time_out)
    {
        if (ros::Time::now().toSec() - secs >= 3)
        {
            time_out = true;
        }
        if (true)
        {
            res.success = true;
            depth_camera_field_safety_fake_muted();
            ROS_INFO(" MuteCameraSafetySrv done");
            return true;
        }
        //
        ros::Duration(0.1).sleep();
    }
    res.success = false;

    return false;
}
bool ServiceCbFlexSetPayloadSrv(sick_flexisoft_pkg::FlexSetPayloadSrv::Request &req,
                                sick_flexisoft_pkg::FlexSetPayloadSrv::Response &res)
{
    double secs;
    bool time_out = false;
    secs = ros::Time::now().toSec();
    Flexisoft->flex_write_bit(IPC_SAF_PAYLOAD_RELEASE, req.PAYLOAD_RELEASE);
    while (!time_out)
    {
        if (ros::Time::now().toSec() - secs >= 3)
        {
            time_out = true;
        }
        if (Flexisoft->flex_read_bit(FX3_SAF_PAYLOAD_RELEASE) == req.PAYLOAD_RELEASE)
        {
            res.success = true;
            ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_PAYLOAD_RELEASE));
            ROS_INFO(" FlexSetPayloadSrv done");
            return true;
        }
        //
        ros::Duration(0.1).sleep();
    }
    res.success = false;
    return false;
}
bool ServiceCbFlexSetMappingSrv(sick_flexisoft_pkg::FlexSetMappingSrv::Request &req,
                                sick_flexisoft_pkg::FlexSetMappingSrv::Response &res)
{
    double secs;
    bool time_out = false;
    secs = ros::Time::now().toSec();
    Flexisoft->flex_write_bit(IPC_SAF_MAPPING_RELEASE, req.MAPPING_RELEASE);
    while (!time_out)
    {
        if (ros::Time::now().toSec() - secs >= 3)
        {
            time_out = true;
        }
        if (Flexisoft->flex_read_bit(FX3_SAF_MAPPING_RELEASE) == req.MAPPING_RELEASE)
        {
            res.success = true;
            ROS_INFO("sending back response: [%x]", Flexisoft->flex_read_bit(FX3_SAF_MAPPING_RELEASE));
            ROS_INFO(" FlexSetMappingSrv done");
            return true;
        }
        //
        ros::Duration(0.1).sleep();
    }
    res.success = false;
    return false;
}

int main(int argc, char **argv)
{

    ROS_INFO("FLEXISOFT CONNECTING....");
    ros::init(argc, argv, "safety_function");
    ros::NodeHandle nh;

    ros::ServiceServer Srv_FlexSetStopOperationalSrv = nh.advertiseService("FlexSetStopOperationalSrv", ServiceCbFlexSetStopOperationalSrv);
    ros::ServiceServer Srv_FlexSetZoneSrv = nh.advertiseService("FlexSetZoneSrv", ServiceCbFlexSetZoneSrv);
    ros::ServiceServer Srv_FlexSetMuteReleaseSrv = nh.advertiseService("FlexSetMuteReleaseSrv", ServiceCbFlexSetMuteReleaseSrv);
    ros::ServiceServer Srv_FlexSetPayloadSrv = nh.advertiseService("FlexSetPayloadSrv", ServiceCbFlexSetPayloadSrv);
    ros::ServiceServer Srv_FlexSetMappingSrv = nh.advertiseService("FlexSetMappingSrv", ServiceCbFlexSetMappingSrv);
    ros::ServiceServer Srv_MuteCameraSafetySrv = nh.advertiseService("MuteCameraSafetySrv", ServiceCbMuteCameraSafetySrv);

    fx3_saf_protective_fault_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_protective_fault>("/fx3_saf_protective_fault_pub", 10);
    fx3_saf_stop_states_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_stop_states>("/fx3_saf_stop_states_pub", 10);
    fx3_saf_stop_operational_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_stop_operational>("/fx3_saf_stop_operational_pub", 10);
    fx3_saf_stop_protective_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_stop_protective>("/fx3_saf_stop_protective_pub", 10);
    fx3_saf_stop_emergency_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_stop_emergency>("/fx3_saf_stop_emergency_pub", 10);
    fx3_saf_stop_resume_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_stop_resume>("/fx3_saf_stop_resume_pub", 10);
    fx3_saf_status_states_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_status_states>("/fx3_saf_status_states_pub", 10);
    fx3_saf_protective_field_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_protective_field>("/fx3_saf_protective_field_pub", 10);
    fx3_saf_mode_switch_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_mode_switch>("/fx3_saf_mode_switch_pub", 10);
    fx3_saf_safety_system_pub = nh.advertise<sick_flexisoft_pkg::fx3_saf_safety_system>("/fx3_saf_safety_system_pub", 10);
    m5_out_enc_enable_id_pub = nh.advertise<sick_flexisoft_pkg::m5_out_enc_enable_id>("/m5_out_enc_enable_id_pub", 10);
    use_safety_camera_pub = nh.advertise<std_msgs::Bool>("/use_safety_camera", 10);

    ros::Subscriber depth_camera_fields_safety_sub = nh.subscribe("/depth_camera/fields_safety", 10, depth_camera_fields_safety_CallBack);

    // sick_flexisoft_pkg::SAFE_SP_AGV SAFE_SP_AGV;

    ros::Rate loop_rate(30);
    while (ros::ok())
    {
        if (!Flexisoft->connected)
        {
            ROS_INFO("FLEXISOFT CONNECTING....");
            Flexisoft->connect();
        }
        while (ros::ok() && Flexisoft->connected)
        {
            /* code */

            Flexisoft->tcp_read(DATA_SET_01);

            fx3_saf_protective_fault_function_pub();
            fx3_saf_stop_states_function_pub();
            fx3_saf_stop_operational_function_pub();
            fx3_saf_stop_protective_function_pub();
            fx3_saf_stop_emergency_function_pub();
            fx3_saf_stop_resume_function_pub();
            fx3_saf_status_states_function_pub();
            fx3_saf_protective_field_function_pub();
            fx3_saf_mode_switch_function_pub();
            fx3_saf_safety_system_function_pub();
            m5_out_enc_enable_id_function_pub();

    

            ros::spinOnce();
            loop_rate.sleep();
        }
        loop_rate.sleep();
        ros::spinOnce();
    }
    Flexisoft->disconnect();
    ros::spin();
    delete (Flexisoft);

    return 0;
}
