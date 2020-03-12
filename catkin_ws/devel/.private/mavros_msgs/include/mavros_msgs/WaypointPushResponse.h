// Generated by gencpp from file mavros_msgs/WaypointPushResponse.msg
// DO NOT EDIT!


#ifndef MAVROS_MSGS_MESSAGE_WAYPOINTPUSHRESPONSE_H
#define MAVROS_MSGS_MESSAGE_WAYPOINTPUSHRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mavros_msgs
{
template <class ContainerAllocator>
struct WaypointPushResponse_
{
  typedef WaypointPushResponse_<ContainerAllocator> Type;

  WaypointPushResponse_()
    : success(false)
    , wp_transfered(0)  {
    }
  WaypointPushResponse_(const ContainerAllocator& _alloc)
    : success(false)
    , wp_transfered(0)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;

   typedef uint32_t _wp_transfered_type;
  _wp_transfered_type wp_transfered;





  typedef boost::shared_ptr< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> const> ConstPtr;

}; // struct WaypointPushResponse_

typedef ::mavros_msgs::WaypointPushResponse_<std::allocator<void> > WaypointPushResponse;

typedef boost::shared_ptr< ::mavros_msgs::WaypointPushResponse > WaypointPushResponsePtr;
typedef boost::shared_ptr< ::mavros_msgs::WaypointPushResponse const> WaypointPushResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mavros_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geographic_msgs': ['/opt/ros/kinetic/share/geographic_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'mavros_msgs': ['/home/alejandro/TFG/catkin_ws/src/mavros/mavros_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'uuid_msgs': ['/opt/ros/kinetic/share/uuid_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "90e0074a42480231d34eed864d14365e";
  }

  static const char* value(const ::mavros_msgs::WaypointPushResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x90e0074a42480231ULL;
  static const uint64_t static_value2 = 0xd34eed864d14365eULL;
};

template<class ContainerAllocator>
struct DataType< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mavros_msgs/WaypointPushResponse";
  }

  static const char* value(const ::mavros_msgs::WaypointPushResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n\
uint32 wp_transfered\n\
\n\
";
  }

  static const char* value(const ::mavros_msgs::WaypointPushResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
      stream.next(m.wp_transfered);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct WaypointPushResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mavros_msgs::WaypointPushResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mavros_msgs::WaypointPushResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "wp_transfered: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.wp_transfered);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAVROS_MSGS_MESSAGE_WAYPOINTPUSHRESPONSE_H
