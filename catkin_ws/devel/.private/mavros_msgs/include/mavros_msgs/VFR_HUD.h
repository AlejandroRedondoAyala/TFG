// Generated by gencpp from file mavros_msgs/VFR_HUD.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_VFR_HUD_H
#define MAVROS_MSGS_MESSAGE_VFR_HUD_H


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
struct VFR_HUD_
{
  typedef VFR_HUD_<ContainerAllocator> Type;

  VFR_HUD_()
    : header()
    , airspeed(0.0)
    , groundspeed(0.0)
    , heading(0)
    , throttle(0.0)
    , altitude(0.0)
    , climb(0.0)  {
    }
  VFR_HUD_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , airspeed(0.0)
    , groundspeed(0.0)
    , heading(0)
    , throttle(0.0)
    , altitude(0.0)
    , climb(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _airspeed_type;
  _airspeed_type airspeed;

   typedef float _groundspeed_type;
  _groundspeed_type groundspeed;

   typedef int16_t _heading_type;
  _heading_type heading;

   typedef float _throttle_type;
  _throttle_type throttle;

   typedef float _altitude_type;
  _altitude_type altitude;

   typedef float _climb_type;
  _climb_type climb;





  typedef boost::shared_ptr< ::mavros_msgs::VFR_HUD_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::VFR_HUD_<ContainerAllocator> const> ConstPtr;

}; // struct VFR_HUD_

typedef ::mavros_msgs::VFR_HUD_<std::allocator<void> > VFR_HUD;

typedef boost::shared_ptr< ::mavros_msgs::VFR_HUD > VFR_HUDPtr;
typedef boost::shared_ptr< ::mavros_msgs::VFR_HUD const> VFR_HUDConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::VFR_HUD_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::VFR_HUD_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::VFR_HUD_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::VFR_HUD_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1f55e210c3d39fe105d44d8dc963655f";
  }

  static const char* value(const ::mavros_msgs::VFR_HUD_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1f55e210c3d39fe1ULL;
  static const uint64_t static_value2 = 0x05d44d8dc963655fULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/VFR_HUD";
  }

  static const char* value(const ::mavros_msgs::VFR_HUD_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Metrics typically displayed on a HUD for fixed wing aircraft\n\
#\n\
# VFR_HUD message\n\
\n\
std_msgs/Header header\n\
float32 airspeed	# m/s\n\
float32 groundspeed	# m/s\n\
int16 heading		# degrees 0..360\n\
float32 throttle		# normalized to 0.0..1.0\n\
float32 altitude		# MSL\n\
float32 climb		# current climb rate m/s\n\
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

  static const char* value(const ::mavros_msgs::VFR_HUD_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.airspeed);
      stream.next(m.groundspeed);
      stream.next(m.heading);
      stream.next(m.throttle);
      stream.next(m.altitude);
      stream.next(m.climb);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VFR_HUD_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::VFR_HUD_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::VFR_HUD_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "airspeed: ";
    Printer<float>::stream(s, indent + "  ", v.airspeed);
    s << indent << "groundspeed: ";
    Printer<float>::stream(s, indent + "  ", v.groundspeed);
    s << indent << "heading: ";
    Printer<int16_t>::stream(s, indent + "  ", v.heading);
    s << indent << "throttle: ";
    Printer<float>::stream(s, indent + "  ", v.throttle);
    s << indent << "altitude: ";
    Printer<float>::stream(s, indent + "  ", v.altitude);
    s << indent << "climb: ";
    Printer<float>::stream(s, indent + "  ", v.climb);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_VFR_HUD_H
