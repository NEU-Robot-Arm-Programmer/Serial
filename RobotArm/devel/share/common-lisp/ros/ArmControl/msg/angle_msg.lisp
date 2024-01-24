; Auto-generated. Do not edit!


(cl:in-package ArmControl-msg)


;//! \htmlinclude angle_msg.msg.html

(cl:defclass <angle_msg> (roslisp-msg-protocol:ros-message)
  ((angles
    :reader angles
    :initarg :angles
    :type cl:float
    :initform 0.0))
)

(cl:defclass angle_msg (<angle_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <angle_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'angle_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ArmControl-msg:<angle_msg> is deprecated: use ArmControl-msg:angle_msg instead.")))

(cl:ensure-generic-function 'angles-val :lambda-list '(m))
(cl:defmethod angles-val ((m <angle_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ArmControl-msg:angles-val is deprecated.  Use ArmControl-msg:angles instead.")
  (angles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <angle_msg>) ostream)
  "Serializes a message object of type '<angle_msg>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <angle_msg>) istream)
  "Deserializes a message object of type '<angle_msg>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angles) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<angle_msg>)))
  "Returns string type for a message object of type '<angle_msg>"
  "ArmControl/angle_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'angle_msg)))
  "Returns string type for a message object of type 'angle_msg"
  "ArmControl/angle_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<angle_msg>)))
  "Returns md5sum for a message object of type '<angle_msg>"
  "22b07857a56aae829de3d30b31b536a0")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'angle_msg)))
  "Returns md5sum for a message object of type 'angle_msg"
  "22b07857a56aae829de3d30b31b536a0")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<angle_msg>)))
  "Returns full string definition for message of type '<angle_msg>"
  (cl:format cl:nil "float64 angles~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'angle_msg)))
  "Returns full string definition for message of type 'angle_msg"
  (cl:format cl:nil "float64 angles~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <angle_msg>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <angle_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'angle_msg
    (cl:cons ':angles (angles msg))
))
