// Generated by gencpp from file mavros_msgs/TimesyncStatus.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_TIMESYNCSTATUS_H
#define MAVROS_MSGS_MESSAGE_TIMESYNCSTATUS_H


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
struct TimesyncStatus_
{
  typedef TimesyncStatus_<ContainerAllocator> Type;

  TimesyncStatus_()
    : header()
    , remote_timestamp_ns(0)
    , observed_offset_ns(0)
    , estimated_offset_ns(0)
    , round_trip_time_ms(0.0)  {
    }
  TimesyncStatus_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , remote_timestamp_ns(0)
    , observed_offset_ns(0)
    , estimated_offset_ns(0)
    , round_trip_time_ms(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint64_t _remote_timestamp_ns_type;
  _remote_timestamp_ns_type remote_timestamp_ns;

   typedef int64_t _observed_offset_ns_type;
  _observed_offset_ns_type observed_offset_ns;

   typedef int64_t _estimated_offset_ns_type;
  _estimated_offset_ns_type estimated_offset_ns;

   typedef float _round_trip_time_ms_type;
  _round_trip_time_ms_type round_trip_time_ms;





  typedef boost::shared_ptr< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> const> ConstPtr;

}; // struct TimesyncStatus_

typedef ::mavros_msgs::TimesyncStatus_<std::allocator<void> > TimesyncStatus;

typedef boost::shared_ptr< ::mavros_msgs::TimesyncStatus > TimesyncStatusPtr;
typedef boost::shared_ptr< ::mavros_msgs::TimesyncStatus const> TimesyncStatusConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::TimesyncStatus_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "021ec8044e747bea518b441f374ba64b";
  }

  static const char* value(const ::mavros_msgs::TimesyncStatus_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x021ec8044e747beaULL;
  static const uint64_t static_value2 = 0x518b441f374ba64bULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/TimesyncStatus";
  }

  static const char* value(const ::mavros_msgs::TimesyncStatus_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Status of the MAVLink time synchroniser\n\
\n\
std_msgs/Header header\n\
uint64 remote_timestamp_ns		# remote system timestamp (nanoseconds)\n\
int64 observed_offset_ns		# raw time offset directly observed from this timesync packet (nanoseconds)\n\
int64 estimated_offset_ns		# smoothed time offset between companion system and Mavros (nanoseconds)\n\
float32 round_trip_time_ms		# round trip time of this timesync packet (milliseconds)\n\
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

  static const char* value(const ::mavros_msgs::TimesyncStatus_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.remote_timestamp_ns);
      stream.next(m.observed_offset_ns);
      stream.next(m.estimated_offset_ns);
      stream.next(m.round_trip_time_ms);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TimesyncStatus_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::TimesyncStatus_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::TimesyncStatus_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "remote_timestamp_ns: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.remote_timestamp_ns);
    s << indent << "observed_offset_ns: ";
    Printer<int64_t>::stream(s, indent + "  ", v.observed_offset_ns);
    s << indent << "estimated_offset_ns: ";
    Printer<int64_t>::stream(s, indent + "  ", v.estimated_offset_ns);
    s << indent << "round_trip_time_ms: ";
    Printer<float>::stream(s, indent + "  ", v.round_trip_time_ms);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_TIMESYNCSTATUS_H
