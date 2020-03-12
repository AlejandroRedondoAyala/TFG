// Generated by gencpp from file rotors_comm/OctomapRequest.msg
// DO NOT EDIT!


#ifndef ROTORS_COMM_MESSAGE_OCTOMAPREQUEST_H
#define ROTORS_COMM_MESSAGE_OCTOMAPREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Point.h>

namespace rotors_comm
{
template <class ContainerAllocator>
struct OctomapRequest_
{
  typedef OctomapRequest_<ContainerAllocator> Type;

  OctomapRequest_()
    : bounding_box_origin()
    , bounding_box_lengths()
    , leaf_size(0.0)
    , publish_octomap(false)
    , filename()  {
    }
  OctomapRequest_(const ContainerAllocator& _alloc)
    : bounding_box_origin(_alloc)
    , bounding_box_lengths(_alloc)
    , leaf_size(0.0)
    , publish_octomap(false)
    , filename(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _bounding_box_origin_type;
  _bounding_box_origin_type bounding_box_origin;

   typedef  ::geometry_msgs::Point_<ContainerAllocator>  _bounding_box_lengths_type;
  _bounding_box_lengths_type bounding_box_lengths;

   typedef double _leaf_size_type;
  _leaf_size_type leaf_size;

   typedef uint8_t _publish_octomap_type;
  _publish_octomap_type publish_octomap;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _filename_type;
  _filename_type filename;





  typedef boost::shared_ptr< ::rotors_comm::OctomapRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rotors_comm::OctomapRequest_<ContainerAllocator> const> ConstPtr;

}; // struct OctomapRequest_

typedef ::rotors_comm::OctomapRequest_<std::allocator<void> > OctomapRequest;

typedef boost::shared_ptr< ::rotors_comm::OctomapRequest > OctomapRequestPtr;
typedef boost::shared_ptr< ::rotors_comm::OctomapRequest const> OctomapRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rotors_comm::OctomapRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rotors_comm::OctomapRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace rotors_comm

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'rotors_comm': ['/home/alejandro/TFG/catkin_ws/src/rotors_simulator/rotors_comm/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'octomap_msgs': ['/opt/ros/kinetic/share/octomap_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rotors_comm::OctomapRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rotors_comm::OctomapRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rotors_comm::OctomapRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "75da936d054df9de7938d7041a8a6ef2";
  }

  static const char* value(const ::rotors_comm::OctomapRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x75da936d054df9deULL;
  static const uint64_t static_value2 = 0x7938d7041a8a6ef2ULL;
};

template<class ContainerAllocator>
struct DataType< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rotors_comm/OctomapRequest";
  }

  static const char* value(const ::rotors_comm::OctomapRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n\
geometry_msgs/Point bounding_box_origin\n\
\n\
geometry_msgs/Point bounding_box_lengths\n\
\n\
float64 leaf_size\n\
\n\
bool publish_octomap\n\
\n\
string filename\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::rotors_comm::OctomapRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.bounding_box_origin);
      stream.next(m.bounding_box_lengths);
      stream.next(m.leaf_size);
      stream.next(m.publish_octomap);
      stream.next(m.filename);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct OctomapRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rotors_comm::OctomapRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rotors_comm::OctomapRequest_<ContainerAllocator>& v)
  {
    s << indent << "bounding_box_origin: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.bounding_box_origin);
    s << indent << "bounding_box_lengths: ";
    s << std::endl;
    Printer< ::geometry_msgs::Point_<ContainerAllocator> >::stream(s, indent + "  ", v.bounding_box_lengths);
    s << indent << "leaf_size: ";
    Printer<double>::stream(s, indent + "  ", v.leaf_size);
    s << indent << "publish_octomap: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.publish_octomap);
    s << indent << "filename: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.filename);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROTORS_COMM_MESSAGE_OCTOMAPREQUEST_H
