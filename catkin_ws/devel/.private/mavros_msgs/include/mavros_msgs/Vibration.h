// Generated by gencpp from file mavros_msgs/Vibration.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_VIBRATION_H
#define MAVROS_MSGS_MESSAGE_VIBRATION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/Vector3.h>

namespace mavros_msgs
{
template <class ContainerAllocator>
struct Vibration_
{
  typedef Vibration_<ContainerAllocator> Type;

  Vibration_()
    : header()
    , vibration()
    , clipping()  {
      clipping.assign(0.0);
  }
  Vibration_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , vibration(_alloc)
    , clipping()  {
  (void)_alloc;
      clipping.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::geometry_msgs::Vector3_<ContainerAllocator>  _vibration_type;
  _vibration_type vibration;

   typedef boost::array<float, 3>  _clipping_type;
  _clipping_type clipping;





  typedef boost::shared_ptr< ::mavros_msgs::Vibration_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::Vibration_<ContainerAllocator> const> ConstPtr;

}; // struct Vibration_

typedef ::mavros_msgs::Vibration_<std::allocator<void> > Vibration;

typedef boost::shared_ptr< ::mavros_msgs::Vibration > VibrationPtr;
typedef boost::shared_ptr< ::mavros_msgs::Vibration const> VibrationConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::Vibration_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::Vibration_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::mavros_msgs::Vibration_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::Vibration_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::Vibration_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::Vibration_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::Vibration_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::Vibration_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::Vibration_<ContainerAllocator> >
{
  static const char* value()
  {
    return "eb92bf9b7aa735dfcd06b3ede5027d02";
  }

  static const char* value(const ::mavros_msgs::Vibration_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xeb92bf9b7aa735dfULL;
  static const uint64_t static_value2 = 0xcd06b3ede5027d02ULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::Vibration_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/Vibration";
  }

  static const char* value(const ::mavros_msgs::Vibration_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::Vibration_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# VIBRATION message data\n\
# @description: Vibration levels and accelerometer clipping\n\
\n\
std_msgs/Header header\n\
\n\
geometry_msgs/Vector3 vibration		# 3-axis vibration levels\n\
float32[3] clipping				# Accelerometers clipping\n\
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

  static const char* value(const ::mavros_msgs::Vibration_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::Vibration_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.vibration);
      stream.next(m.clipping);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Vibration_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::Vibration_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::Vibration_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "vibration: ";
    s << std::endl;
    Printer< ::geometry_msgs::Vector3_<ContainerAllocator> >::stream(s, indent + "  ", v.vibration);
    s << indent << "clipping[]" << std::endl;
    for (size_t i = 0; i < v.clipping.size(); ++i)
    {
      s << indent << "  clipping[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.clipping[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_VIBRATION_H
