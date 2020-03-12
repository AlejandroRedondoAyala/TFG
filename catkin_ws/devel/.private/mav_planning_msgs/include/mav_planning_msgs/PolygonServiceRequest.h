// Generated by gencpp from file mav_planning_msgs/PolygonServiceRequest.msg
// DO NOT EDIT!


#ifndef MAV_PLANNING_MSGS_MESSAGE_POLYGONSERVICEREQUEST_H
#define MAV_PLANNING_MSGS_MESSAGE_POLYGONSERVICEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <mav_planning_msgs/PolygonWithHolesStamped.h>

namespace mav_planning_msgs
{
template <class ContainerAllocator>
struct PolygonServiceRequest_
{
  typedef PolygonServiceRequest_<ContainerAllocator> Type;

  PolygonServiceRequest_()
    : polygon()  {
    }
  PolygonServiceRequest_(const ContainerAllocator& _alloc)
    : polygon(_alloc)  {
  (void)_alloc;
    }



   typedef  ::mav_planning_msgs::PolygonWithHolesStamped_<ContainerAllocator>  _polygon_type;
  _polygon_type polygon;





  typedef boost::shared_ptr< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> const> ConstPtr;

}; // struct PolygonServiceRequest_

typedef ::mav_planning_msgs::PolygonServiceRequest_<std::allocator<void> > PolygonServiceRequest;

typedef boost::shared_ptr< ::mav_planning_msgs::PolygonServiceRequest > PolygonServiceRequestPtr;
typedef boost::shared_ptr< ::mav_planning_msgs::PolygonServiceRequest const> PolygonServiceRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mav_planning_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'mav_msgs': ['/home/alejandro/TFG/catkin_ws/src/mav_comm/mav_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'mav_planning_msgs': ['/home/alejandro/TFG/catkin_ws/src/mav_comm/mav_planning_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b72bf7542ebf0f998ff6de9ed6f90873";
  }

  static const char* value(const ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb72bf7542ebf0f99ULL;
  static const uint64_t static_value2 = 0x8ff6de9ed6f90873ULL;
};

template<class ContainerAllocator>
struct DataType< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mav_planning_msgs/PolygonServiceRequest";
  }

  static const char* value(const ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
\n\
mav_planning_msgs/PolygonWithHolesStamped polygon\n\
\n\
================================================================================\n\
MSG: mav_planning_msgs/PolygonWithHolesStamped\n\
# A message to define a 2D polygon with holes, stamp, and altitude above ground.\n\
Header header\n\
float64 altitude\n\
mav_planning_msgs/PolygonWithHoles polygon\n\
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
MSG: mav_planning_msgs/PolygonWithHoles\n\
# A message to define a 2D polygon with holes.\n\
mav_planning_msgs/Polygon2D hull\n\
mav_planning_msgs/Polygon2D[] holes\n\
\n\
================================================================================\n\
MSG: mav_planning_msgs/Polygon2D\n\
# A specification of a 2D polygon where the first and last points are assumed to be connected.\n\
mav_planning_msgs/Point2D[] points\n\
\n\
================================================================================\n\
MSG: mav_planning_msgs/Point2D\n\
# This contains the position of a 2D point.\n\
float64 x\n\
float64 y\n\
";
  }

  static const char* value(const ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.polygon);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PolygonServiceRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mav_planning_msgs::PolygonServiceRequest_<ContainerAllocator>& v)
  {
    s << indent << "polygon: ";
    s << std::endl;
    Printer< ::mav_planning_msgs::PolygonWithHolesStamped_<ContainerAllocator> >::stream(s, indent + "  ", v.polygon);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAV_PLANNING_MSGS_MESSAGE_POLYGONSERVICEREQUEST_H
