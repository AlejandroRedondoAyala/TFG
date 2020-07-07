// Generated by gencpp from file mav_state_machine_msgs/RunTaskServiceResponse.msg
// DO NOT EDIT!


#ifndef MAV_STATE_MACHINE_MSGS_MESSAGE_RUNTASKSERVICERESPONSE_H
#define MAV_STATE_MACHINE_MSGS_MESSAGE_RUNTASKSERVICERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mav_state_machine_msgs
{
template <class ContainerAllocator>
struct RunTaskServiceResponse_
{
  typedef RunTaskServiceResponse_<ContainerAllocator> Type;

  RunTaskServiceResponse_()
    : success(false)  {
    }
  RunTaskServiceResponse_(const ContainerAllocator& _alloc)
    : success(false)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;





  typedef boost::shared_ptr< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> const> ConstPtr;

}; // struct RunTaskServiceResponse_

typedef ::mav_state_machine_msgs::RunTaskServiceResponse_<std::allocator<void> > RunTaskServiceResponse;

typedef boost::shared_ptr< ::mav_state_machine_msgs::RunTaskServiceResponse > RunTaskServiceResponsePtr;
typedef boost::shared_ptr< ::mav_state_machine_msgs::RunTaskServiceResponse const> RunTaskServiceResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mav_state_machine_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'mav_state_machine_msgs': ['/home/alejandro/catkin_ws/src/mav_comm/mav_state_machine_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "358e233cde0c8a8bcfea4ce193f8fc15";
  }

  static const char* value(const ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x358e233cde0c8a8bULL;
  static const uint64_t static_value2 = 0xcfea4ce193f8fc15ULL;
};

template<class ContainerAllocator>
struct DataType< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mav_state_machine_msgs/RunTaskServiceResponse";
  }

  static const char* value(const ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
bool success\n\
\n\
";
  }

  static const char* value(const ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct RunTaskServiceResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mav_state_machine_msgs::RunTaskServiceResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MAV_STATE_MACHINE_MSGS_MESSAGE_RUNTASKSERVICERESPONSE_H
