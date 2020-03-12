// Generated by gencpp from file mavros_msgs/ActuatorControl.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_ACTUATORCONTROL_H
#define MAVROS_MSGS_MESSAGE_ACTUATORCONTROL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace mavros_msgs
{
template <class ContainerAllocator>
struct ActuatorControl_
{
  typedef ActuatorControl_<ContainerAllocator> Type;

  ActuatorControl_()
    : header()
    , group_mix(0)
    , controls()  {
      controls.assign(0.0);
  }
  ActuatorControl_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , group_mix(0)
    , controls()  {
  (void)_alloc;
      controls.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _group_mix_type;
  _group_mix_type group_mix;

   typedef boost::array<float, 8>  _controls_type;
  _controls_type controls;



  enum {
    PX4_MIX_FLIGHT_CONTROL = 0u,
    PX4_MIX_FLIGHT_CONTROL_VTOL_ALT = 1u,
    PX4_MIX_PAYLOAD = 2u,
    PX4_MIX_MANUAL_PASSTHROUGH = 3u,
  };


  typedef boost::shared_ptr< ::mavros_msgs::ActuatorControl_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::ActuatorControl_<ContainerAllocator> const> ConstPtr;

}; // struct ActuatorControl_

typedef ::mavros_msgs::ActuatorControl_<std::allocator<void> > ActuatorControl;

typedef boost::shared_ptr< ::mavros_msgs::ActuatorControl > ActuatorControlPtr;
typedef boost::shared_ptr< ::mavros_msgs::ActuatorControl const> ActuatorControlConstPtr;

// constants requiring out of line definition

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::ActuatorControl_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mavros_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'geographic_msgs': ['/opt/ros/kinetic/share/geographic_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'mavros_msgs': ['/home/alejandro/TFG/catkin_ws/src/mavros/mavros_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'uuid_msgs': ['/opt/ros/kinetic/share/uuid_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::ActuatorControl_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::ActuatorControl_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::ActuatorControl_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9eea0a80c88944fe2fb67f3b3768854b";
  }

  static const char* value(const ::mavros_msgs::ActuatorControl_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9eea0a80c88944feULL;
  static const uint64_t static_value2 = 0x2fb67f3b3768854bULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/ActuatorControl";
  }

  static const char* value(const ::mavros_msgs::ActuatorControl_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# raw servo values for direct actuator controls\n\
#\n\
# about groups, mixing and channels:\n\
# https://pixhawk.org/dev/mixing\n\
\n\
# constant for mixer group\n\
uint8 PX4_MIX_FLIGHT_CONTROL = 0\n\
uint8 PX4_MIX_FLIGHT_CONTROL_VTOL_ALT = 1\n\
uint8 PX4_MIX_PAYLOAD = 2\n\
uint8 PX4_MIX_MANUAL_PASSTHROUGH = 3\n\
#uint8 PX4_MIX_FC_MC_VIRT = 4\n\
#uint8 PX4_MIX_FC_FW_VIRT = 5\n\
\n\
std_msgs/Header header\n\
uint8 group_mix\n\
float32[8] controls\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::mavros_msgs::ActuatorControl_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.group_mix);
      stream.next(m.controls);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ActuatorControl_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::ActuatorControl_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::ActuatorControl_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "group_mix: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.group_mix);
    s << indent << "controls[]" << std::endl;
    for (size_t i = 0; i < v.controls.size(); ++i)
    {
      s << indent << "  controls[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.controls[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_ACTUATORCONTROL_H
