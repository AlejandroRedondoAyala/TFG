// Generated by gencpp from file mav_msgs/TorqueThrust.msg
// DO NOT EDIT!


#ifndef MAV_MSGS_MESSAGE_TORQUETHRUST_H
#define MAV_MSGS_MESSAGE_TORQUETHRUST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Vector3.h>

namespace mav_msgs
{
template <class ContainerAllocator>
struct TorqueThrust_
{
  typedef TorqueThrust_<ContainerAllocator> Type;

  TorqueThrust_()
    : header()
    , torque()
    , thrust()  {
    }
  TorqueThrust_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , torque(_alloc)
    , thrust(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _torque_type;
  _torque_type torque;

   typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _thrust_type;
  _thrust_type thrust;





  typedef boost::shared_ptr< ::mav_msgs::TorqueThrust_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mav_msgs::TorqueThrust_<ContainerAllocator> const> ConstPtr;

}; // struct TorqueThrust_

typedef ::mav_msgs::TorqueThrust_<std::allocator<void> > TorqueThrust;

typedef boost::shared_ptr< ::mav_msgs::TorqueThrust > TorqueThrustPtr;
typedef boost::shared_ptr< ::mav_msgs::TorqueThrust const> TorqueThrustConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mav_msgs::TorqueThrust_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mav_msgs::TorqueThrust_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mav_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'mav_msgs': ['/home/alejandro/catkin_ws/src/mav_comm/mav_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mav_msgs::TorqueThrust_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mav_msgs::TorqueThrust_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mav_msgs::TorqueThrust_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
{
  static const char* value()
  {
    return "81293743ae52683b61e39c21bc0b30db";
  }

  static const char* value(const ::mav_msgs::TorqueThrust_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x81293743ae52683bULL;
  static const uint64_t static_value2 = 0x61e39c21bc0b30dbULL;
};

template<class ContainerAllocator>
struct DataType< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mav_msgs/TorqueThrust";
  }

  static const char* value(const ::mav_msgs::TorqueThrust_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
\n\
# We use the coordinate frames with the following convention:\n\
#   x: forward\n\
#   y: left\n\
#   z: up\n\
\n\
geometry_msgs/Vector3 torque  # Torque expressed in the body frame [Nm].\n\
geometry_msgs/Vector3 thrust  # Thrust [N] expressed in the body frame. \n\
                              # For a fixed-wing, usually the x-component is used.\n\
                              # For a multi-rotor, usually the z-component is used. \n\
                              # Set all un-used components to 0.  \n\
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
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
# It is only meant to represent a direction. Therefore, it does not\n\
# make sense to apply a translation to it (e.g., when applying a \n\
# generic rigid transformation to a Vector3, tf2 will only apply the\n\
# rotation). If you want your data to be translatable too, use the\n\
# geometry_msgs/Point message instead.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::mav_msgs::TorqueThrust_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.torque);
      stream.next(m.thrust);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TorqueThrust_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mav_msgs::TorqueThrust_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mav_msgs::TorqueThrust_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "torque: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.torque);
    s << indent << "thrust: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.thrust);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAV_MSGS_MESSAGE_TORQUETHRUST_H
